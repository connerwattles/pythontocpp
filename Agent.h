#ifndef AGENT_H
#define AGENT_H
#include <iostream>
#include "Site.h"
#include "Position.h"
#include "Agent_State.h"
#include "Direction.h"
#include "Getters.h"
#include <map>
#include <sstream>
#include <numeric>

using namespace std;

class Agent
{
public:
	Position position = { 0, 0 };
	AGENT_STATE state = AGENT_STATE::REST;
	Site* assignedSite = nullptr;
    vector<Site*> possibleSites;
	Direction direction = { 0, 1 };
	int speed = 0;


	Agent(int id, Position position, vector<Site*> possibleSites)
    {
        this->id = id;
        this->position = position;
        this->possibleSites = possibleSites;
    }

    Direction getHomeDir() {
        Direction dir = {
                -1.0 * position.getX(),
                -1.0 * position.getY()
        };
//        dir.normalize();
        return dir;
    }

	void step(const vector<int>& dancerCountBySite, int numDancers);

	void goHome();

	void goSite();

	void explore();

    void advance_agent()
    {
        direction.normalize();
        position.x += speed * direction.x_component;
        position.y += speed * direction.y_component;
    }

    Direction getSiteDir() {
        Direction out = Direction::getDirection(&position, &(assignedSite->position));
//        out.normalize();
        return out;
    }

    bool isAtAssignedSite() const {    //Tested works
        if (assignedSite == nullptr) return false;

        else if (position.getDist2D((assignedSite->position)) < SITE_SIZE) return true;

        else return false;
    }

    bool isAtHub() const {
        return position.getDist2D(HUB_LOCATION) < SITE_SIZE;
    }

    pair<bool, Site*> isAtAnySite() const
    {
        for (Site* site : possibleSites)
        {
            if (site != nullptr && site->isInSite(&position))
            {
//
                return {true, site};
            }
        }
        return {false, nullptr};
    }


    tuple<AGENT_STATE, Site*> getTransition(const vector<int>& dancerCountBySite, int numDancers) {
        map<AGENT_STATE, double> transitionProbabilities;

        Site* newSite;

        if (state == AGENT_STATE::REST) {
            tuple<Site*, map<AGENT_STATE, double>> returnVal = transitionProbabilitiesRest(dancerCountBySite, numDancers);
            newSite = get<0>(returnVal);
            transitionProbabilities = get<1>(returnVal);
        }

        else if (state == AGENT_STATE::EXPLORE) {
            tuple<Site*, map<AGENT_STATE, double>> returnVal = transitionProbabilitiesExplore();
            newSite = get<0>(returnVal);
            transitionProbabilities = get<1>(returnVal);
        }

        else if (state == AGENT_STATE::ASSESS) transitionProbabilities = transitionProbabilitiesAssess();

        else if (state == AGENT_STATE::DANCE) transitionProbabilities = transitionProbabilitiesDance();

        else if (state == AGENT_STATE::TRAVEL_HOME_TO_DANCE) transitionProbabilities = transitionProbabilitiesTravelDance();

        else if (state == AGENT_STATE::TRAVEL_HOME_TO_REST) transitionProbabilities = transitionProbabilitiesTravelRest();

        else if (state == AGENT_STATE::TRAVEL_SITE) transitionProbabilities = transitionProbabilitiesTravelSite();

        else assert(false, "should not occur (getTransition)");

        vector<AGENT_STATE> states;
        vector<double> probs;

        for (auto i : transitionProbabilities) {
            states.push_back(i.first);
            probs.push_back(i.second);
        }

        mt19937 gen(random_device{}());									//Fix probability of finding new state based on list of probability
        discrete_distribution<size_t> d{probs.begin(), probs.end()};
        AGENT_STATE newState = states[d(gen)];
        return make_tuple(newState, newSite);
    }

    tuple<Site*, map<AGENT_STATE, double>> transitionProbabilitiesRest(const vector<int>& dancerCountBySite, int numDancers) {
        map<AGENT_STATE, double> transitionProbabilities;

        double sum = accumulate(dancerCountBySite.begin(), dancerCountBySite.end(), 0);

        default_random_engine gen;
        uniform_real_distribution<double> dist(0.0, sum);
        double restToAssessOrNot = dist(gen);
        uniform_real_distribution<double> newDist(0.0, 1.0);
        double restToExploreOrNot = newDist(gen);

        pair<double, Site*> getterVal = getters::restToTravelSiteProb(restToAssessOrNot, isAtHub(), dancerCountBySite, numDancers, possibleSites);

        transitionProbabilities[AGENT_STATE::TRAVEL_SITE] = get<0>(getterVal);
        Site* newSite = get<1>(getterVal);

        transitionProbabilities[AGENT_STATE::EXPLORE] = getters::restToExploreProb(restToExploreOrNot, isAtHub(), transitionProbabilities[AGENT_STATE::TRAVEL_SITE]);

        double allProbs = 0.0;
        for (auto i : transitionProbabilities) {
            allProbs += i.second;
        }
        transitionProbabilities[AGENT_STATE::REST] = 1.0 - allProbs;

        return make_tuple(newSite, transitionProbabilities);
    }

    tuple<Site*, map<AGENT_STATE, double>> transitionProbabilitiesExplore() {
        map<AGENT_STATE, double> transitionProbabilities;

        default_random_engine gen;
        uniform_real_distribution<double> dist(0.0, 1.0);	//AssertionFail here. check params file and see if there is a problem with this const
        double exploreToRestOrNot = dist(gen);

        auto curr_site_data = isAtAnySite();
        transitionProbabilities[AGENT_STATE::ASSESS] = getters::exploreToAssessProb(curr_site_data.first, curr_site_data.second);
        Site* newSite = curr_site_data.second;

        transitionProbabilities[AGENT_STATE::TRAVEL_HOME_TO_REST] = getters::exploreToTravelHomeProb(exploreToRestOrNot, isAtHub(), transitionProbabilities[AGENT_STATE::ASSESS]);

        double allProbs = 0.0;
        for (auto i : transitionProbabilities) {
            allProbs += i.second;
        }
        transitionProbabilities[AGENT_STATE::EXPLORE] = 1.0 - allProbs;
        return make_tuple(newSite, transitionProbabilities);
    }

    map<AGENT_STATE, double> transitionProbabilitiesAssess() {
        map<AGENT_STATE, double> transitionProbabilities;

        default_random_engine gen;
        uniform_real_distribution<double> dist(0.0, 1.0);
        double assessToDanceOrNot = dist(gen);

        transitionProbabilities[AGENT_STATE::TRAVEL_HOME_TO_DANCE] = getters::assesToTravelHomeProb(assessToDanceOrNot, isAtAnySite().first);

        double allProbs = 0.0;
        for (auto i : transitionProbabilities) {
            allProbs += i.second;
        }
        transitionProbabilities[AGENT_STATE::ASSESS] = 1.0 - allProbs;

        return transitionProbabilities;
    }

    map<AGENT_STATE, double> transitionProbabilitiesDance() {
        assert(assignedSite != nullptr, "assigned site should not be null (transitionProbabilitiesDance)");
        map<AGENT_STATE, double> transitionProbabilities;

        default_random_engine gen;
        uniform_real_distribution<double> dist(0.0, 1.0);
        double danceToRestOrNot = dist(gen);

        transitionProbabilities[AGENT_STATE::TRAVEL_SITE] = getters::danceToTravelSiteProb(danceToRestOrNot, isAtHub(), assignedSite->quality);

        transitionProbabilities[AGENT_STATE::REST] = getters::danceToRestProb(danceToRestOrNot, isAtHub(), assignedSite->quality);

        double allProbs = 0.0;
        for (auto i : transitionProbabilities) {
            allProbs += i.second;
        }
        transitionProbabilities[AGENT_STATE::DANCE] = 1.0 - allProbs;

        return transitionProbabilities;
    }

    map<AGENT_STATE, double> transitionProbabilitiesTravelDance() {
        map<AGENT_STATE, double> transitionProbabilities;

        transitionProbabilities[AGENT_STATE::DANCE] = getters::travelHomeToDanceProb(isAtHub());

        transitionProbabilities[AGENT_STATE::TRAVEL_HOME_TO_DANCE] = 1.0 - transitionProbabilities[AGENT_STATE::DANCE];

        return transitionProbabilities;
    }

    map<AGENT_STATE, double> transitionProbabilitiesTravelRest() {
        map<AGENT_STATE, double> transitionProbabilities;

        transitionProbabilities[AGENT_STATE::REST] = getters::travelHomeToRestProb(isAtHub());

        transitionProbabilities[AGENT_STATE::TRAVEL_HOME_TO_REST] = 1.0 - transitionProbabilities[AGENT_STATE::REST];

        return transitionProbabilities;
    }

    map<AGENT_STATE, double> transitionProbabilitiesTravelSite() {
        map<AGENT_STATE, double> transitionProbabilities;
        auto siteLocationData = this->isAtAnySite();
        transitionProbabilities[AGENT_STATE::ASSESS] = getters::travelSiteToAssesProb(siteLocationData.first, siteLocationData.second, assignedSite);

        transitionProbabilities[AGENT_STATE::TRAVEL_SITE] = 1.0 - transitionProbabilities[AGENT_STATE::ASSESS];

        return transitionProbabilities;
    }

    std::string toString()
    {
        std::stringstream out;
        out << "Id: " << id;
        out << " State: " << toString(state);
        out << " Pos: [" << position.x << "," << position.y << "]";
        out << " Dir: [" << direction.x_component << "," << direction.y_component << "]";
        out << " Speed: " << speed;
        out << " A_Site: ";
        if (assignedSite == nullptr)
            out << "NONE";
        else
            out << assignedSite->id;

        out << " At site: ";
        auto x = isAtAnySite();

        if (x.first)
            out << x.second->id;
        else
            out << "NONE";

        return out.str();
    }

    static std::string toString(const AGENT_STATE state)
    {
        switch (state)
        {
            case AGENT_STATE::REST: return "REST";
            case AGENT_STATE::TRAVEL_HOME_TO_DANCE: return "TRAVEL_HOME_TO_DANCE";
            case AGENT_STATE::TRAVEL_HOME_TO_REST: return "TRAVEL_HOME_TO_REST";
            case AGENT_STATE::TRAVEL_SITE: return "TRAVEL_SITE";
            case AGENT_STATE::EXPLORE: return "EXPLORE";
            case AGENT_STATE::DANCE: return "DANCE";
            case AGENT_STATE::ASSESS: return "ASSESS";
        }
        return "BAD STATE";
    }

    void assert(bool b, const char* msg)
    {
        if (!b)
            throw msg;
    }

    int id;
};
#endif
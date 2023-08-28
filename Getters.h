#ifndef GETTERS_H
#define GETTERS_H
#include <tuple>
#include <vector>
#include "Site.h"
#include "Params.h"

using namespace std;

class getters
{
public:
    static double travelHomeToRestProb(bool agentAtHub)
    {
        if (agentAtHub)
            return 1.0;
        else
            return 0.0;
    }

    static double travelHomeToDanceProb(bool agentAtHub)
    {
        if (agentAtHub)
            return 1.0;
        else
            return 0.0;
    }

    static double travelSiteToAssesProb(bool isAtSite, Site* currentSite, Site* assignedSite)
    {
        if (currentSite == nullptr)
            return 0.0; // TODO: ask about this case
        else if (!isAtSite)
            return 0.0;
        else if (currentSite->id == assignedSite->id)
            return 1.0;
        else
            return 0.0;
    }

    static void assert(bool b, const char *msg)
    {
        if (!b)
            throw msg;
    }

    static double danceToRestProb(double p, bool isAtHub, double assignedSiteQuality)
    {
        if (!isAtHub)
        {
            assert(false, "must be at hub for this branch (danceToRestProb)");
        }


        double stay_attach_prob_due_to_qual = 1.0 - pow(BASE_DANCE_TO_ASSESS, (PWR_DANCE_TO_ASSESS*assignedSiteQuality));
        double dance_qual_factor = 1.0 / (1.0 + exp(MULTIPLIER_DANCE_QUAL*assignedSiteQuality));
        return (1.0 - stay_attach_prob_due_to_qual) * (1.0 - p*dance_qual_factor);
    }

    static double danceToTravelSiteProb(double p, bool isAtHub, double assignedSiteQuality)
    {
        if (!isAtHub)
        {
            assert(false, "must be at hub for this branch (danceToTravelSiteProb)");
        }


        double stay_attach_prob_due_to_qual = 1.0 - pow(BASE_DANCE_TO_ASSESS, (PWR_DANCE_TO_ASSESS*assignedSiteQuality));
        double dance_qual_factor = 1.0 / (1.0 + exp(MULTIPLIER_DANCE_QUAL*assignedSiteQuality));
        return (1.0 - stay_attach_prob_due_to_qual) * (1.0 - p*dance_qual_factor);
    }

    static double assesToTravelHomeProb(double p, bool agentAtAnySite)
    {
        if (!agentAtAnySite)
        {
            assert(false, "agent must be at some site for this branch to occur (assesToTravelHomeProb)");
        }
        return p;
    }

    static double exploreToTravelHomeProb(double p, bool agentAtHub, double toAssesProb)
    {
        if (agentAtHub)
            return 0.0;
        else
            return p*(1.0 - toAssesProb);
    }

    static double exploreToAssessProb(bool agentAtAnySite, Site* site)
    {
        if (agentAtAnySite)
            return site->quality;
        else
            return 0.0;
    }

    static pair<double,Site*> restToTravelSiteProb(double p, bool agentAtHub, const vector<int>& dancerCountBySite, int numDancers, const vector<Site*>& sites)
    {
        if (!agentAtHub || p == 0)
            return {0.0, nullptr};

        double prob = 1.0 * p / numDancers;
        vector<double> probs_to_choose;
        vector<double> sumSoFar;
        double sum = 0.0;
        sumSoFar.reserve(dancerCountBySite.size());
        for (int dancerCount : dancerCountBySite)
        {
            sum += (double) dancerCount / (double) numDancers;
            sumSoFar.push_back(sum);
        }


        std::random_device rd;  // Seed generator
        std::mt19937 rng(rd()); // Mersenne Twister engine

        std::uniform_real_distribution<double> distribution(0.0, sum);

        double randomValue = distribution(rng);
        int i = 0;
        while (i < (sumSoFar.size()-1) && sumSoFar.at(i) < randomValue)
            i++;

        return {prob, sites.at(i)};
    }



    static double restToExploreProb(double p, bool isAtHub, double toTravelSiteProb)
    {
        if (isAtHub)
            return p * (1.0 - toTravelSiteProb);
        else
            return 0.0;
    }
};

#endif
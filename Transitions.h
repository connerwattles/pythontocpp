#pragma once
#include <iostream>
#include "Agent.h"
#include "params.h"
#include "World.h"
#include "Getters.h"
#include <map>
#include <random>
#include <unordered_map>
#include <numeric>

using namespace std;

extern vector<World> worlds;

//TRANSITION FUNCTIONS

vector<int> getDancersBySiteTransitions(Agent ag) {
	World world = worlds.at(ag.assignedWorld);
	vector<int> dancers;
	for (int i = 0; i < world.numSites; i++) {
		dancers.push_back(0);
	}
	for (Agent agent : world.agents) {
		if (agent.state == "DANCE") {
			dancers.at(agent.assignedSite.id) += 1;
		}
	}
	return dancers;
}

tuple<Site, map<string, double>> transitionProbabilitiesRest(Agent agent) {
	map<string, double> transitionProbabilities;

	vector<int> dancers = getDancersBySiteTransitions(agent);
	double sum = accumulate(dancers.begin(), dancers.end(), 0);

	default_random_engine gen;
	uniform_real_distribution<double> dist(0.0, sum);
	double restToAssessOrNot = dist(gen);
	uniform_real_distribution<double> newDist(0.0, 1.0);
	double restToExploreOrNot = newDist(gen);

	tuple<double, Site> getterVal = getRestToTravelSiteProb(agent, restToAssessOrNot);

	transitionProbabilities["TRAVEL SITE"] = get<0>(getterVal);
	Site newSite = get<1>(getterVal);

	transitionProbabilities["EXPLORE"] = getRestToExploreProb(agent, restToExploreOrNot, transitionProbabilities["TRAVEL SITE"]);

	double allProbs = 0.0;
	for (auto i : transitionProbabilities) {
		allProbs += i.second;
	}
	transitionProbabilities["REST"] = 1.0 - allProbs;

	return make_tuple(newSite, transitionProbabilities);
}

tuple<Site, map<string, double>> transitionProbabilitiesExplore(Agent agent) {
	map<string, double> transitionProbabilities;

	default_random_engine gen;
	uniform_real_distribution<double> dist(0.0, 1.0);	//AssertionFail here. check params file and see if there is a problem with this const
	double exploreToRestOrNot = dist(gen);

	tuple<double, Site> getterVal = getExploreToAssessProb(agent);
	transitionProbabilities["ASSESS"] = get<0>(getterVal);
	Site newSite = get<1>(getterVal);

	transitionProbabilities["TRAVEL HOME TO REST"] = getExploreToTravelHomeProb(agent, exploreToRestOrNot, transitionProbabilities["ASSESS"]);

	double allProbs = 0.0;
	for (auto i : transitionProbabilities) {
		allProbs += i.second;
	}
	transitionProbabilities["EXPLORE"] = 1.0 - allProbs;

	return make_tuple(newSite, transitionProbabilities);
}

map<string, double> transitionProbabilitiesAssess(Agent agent) {
	map<string, double> transitionProbabilities;

	default_random_engine gen;
	uniform_real_distribution<double> dist(0.0, 1.0);
	double assessToDanceOrNot = dist(gen);

	transitionProbabilities["TRAVEL HOME TO DANCE"] = getAssessToTravelHomeProb(agent, assessToDanceOrNot);

	double allProbs = 0.0;
	for (auto i : transitionProbabilities) {
		allProbs += i.second;
	}
	transitionProbabilities["ASSESS"] = 1.0 - allProbs;

	return transitionProbabilities;
}

map<string, double> transitionProbabilitiesDance(Agent agent) {
	map<string, double> transitionProbabilities;

	default_random_engine gen;
	uniform_real_distribution<double> dist(0.0, 1.0);
	double danceToRestOrNot = dist(gen);

	transitionProbabilities["TRAVEL SITE"] = getDanceToTravelSiteProb(agent, danceToRestOrNot);

	transitionProbabilities["REST"] = getDanceToRestProb(agent, danceToRestOrNot);

	double allProbs = 0.0;
	for (auto i : transitionProbabilities) {
		allProbs += i.second;
	}
	transitionProbabilities["DANCE"] = 1.0 - allProbs;

	return transitionProbabilities;
}

map<string, double> transitionProbabilitiesTravelDance(Agent agent) {
	map<string, double> transitionProbabilities;

	transitionProbabilities["DANCE"] = getTravelHomeToDanceProb(agent);

	transitionProbabilities["TRAVEL HOME TO DANCE"] = 1.0 - transitionProbabilities["DANCE"];

	return transitionProbabilities;
}

map<string, double> transitionProbabilitiesTravelRest(Agent agent) {
	map<string, double> transitionProbabilities;

	transitionProbabilities["REST"] = getTravelHomeToRestProb(agent);

	transitionProbabilities["TRAVEL HOME TO REST"] = 1.0 - transitionProbabilities["REST"];

	return transitionProbabilities;
}

map<string, double> transitionProbabilitiesTravelSite(Agent agent) {
	map<string, double> transitionProbabilities;

	transitionProbabilities["ASSESS"] = getTravelSiteToAssessProb(agent);

	transitionProbabilities["TRAVEL SITE"] = 1.0 - transitionProbabilities["ASSESS"];

	return transitionProbabilities;
}

tuple<string, Site> getTransition(Agent agent) {
	map<string, double> transitionProbabilities;

	Site newSite;
	newSite.id = -1;

	if (agent.state == "REST") {
		tuple<Site, map<string, double>> returnVal = transitionProbabilitiesRest(agent);
		newSite = get<0>(returnVal);
		transitionProbabilities = get<1>(returnVal);
	}

	else if (agent.state == "EXPLORE") {
		tuple<Site, map<string, double>> returnVal = transitionProbabilitiesExplore(agent);
		newSite = get<0>(returnVal);
		transitionProbabilities = get<1>(returnVal);
	}

	else if (agent.state == "ASSESS") transitionProbabilities = transitionProbabilitiesAssess(agent);

	else if (agent.state == "DANCE") transitionProbabilities = transitionProbabilitiesDance(agent);

	else if (agent.state == "Travel HOME TO DANCE") transitionProbabilities = transitionProbabilitiesTravelDance(agent);

	else if (agent.state == "TRAVEL HOME TO REST") transitionProbabilities = transitionProbabilitiesTravelRest(agent);

	else if (agent.state == "TRAVEL SITE") transitionProbabilities = transitionProbabilitiesTravelSite(agent);

	else abort();

	vector<string> states;
	vector<double> probs;

	for (auto i : transitionProbabilities) {
		states.push_back(get<0>(i));
		probs.push_back(get<1>(i));
	}

	mt19937 gen(random_device{}());									//Fix probability of finding new state based on list of probability
	discrete_distribution<size_t> d{probs.begin(), probs.end()};
	string newState = states[d(gen)];

	return make_tuple(newState, newSite);
}
#pragma once
#include <iostream>
#include "Agent.h"
#include "Params.h"
#include "World.h"
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
		if (agent.state == AGENT_STATE::DANCE) {
			dancers.at(agent.assignedSite.id) += 1;
		}
	}
	return dancers;
}

map<string, double> transitionProbabilitiesRest(Agent agent) {
	map<string, double> returnVal;

	vector<double> transitionProbabilities;

	vector<int> dancers = getDancersBySiteTransitions(agent);
	int sum = accumulate(dancers.begin(), dancers.end(), 0);

	random_device rd;
	mt19937 gen(rd());
	binomial_distribution<int> dist(sum, BINOMIAL_COEFF_REST_TO_ASSESS_PER_DANCE);
	double restToAssessOrNot = dist(gen);
	
	binomial_distribution<int> newDist(1, BINOMIAL_COEFF_REST_TO_EXPLORE);
	double restToExploreOrNot = newDist(gen);

	//Figure out if agent will rest or asses by choosing a random binomial up to the sum of dancers
	//figure out if agent will explore or not by choosing random binomial up to 1
	//set the transition probability for TRAVEL_SITE to getRestToTravelSiteProb(agent, restToAssessOrNot)
	//set the transition probability for EXPLORE to getRestToExploreProb(agent, restTiExploreOrNot, prob for TRAVEL_SITE)
	//set the transition probability for REST to 1 - sum(all probabilities)

	return returnVal;
}

map<string, double> transitionProbabilitiesExplore(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

map<string, double> transitionProbabilitiesAssess(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

map<string, double> transitionProbabilitiesDance(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

map<string, double> transitionProbabilitiesTravelDance(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

map<string, double> transitionProbabilitiesTravelRest(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

map<string, double> transitionProbabilitiesTravelSite(Agent agent) {
	map<string, double> returnVal;

	return returnVal;
}

AGENT_STATE getTransition(Agent agent) {
	map<string, double> transitionProbabilities;

	if (agent.state == AGENT_STATE::REST) transitionProbabilities = transitionProbabilitiesRest(agent);

	else if (agent.state == AGENT_STATE::EXPLORE) transitionProbabilities = transitionProbabilitiesExplore(agent);

	else if (agent.state == AGENT_STATE::ASSESS) transitionProbabilities = transitionProbabilitiesAssess(agent);

	else if (agent.state == AGENT_STATE::DANCE) transitionProbabilities = transitionProbabilitiesDance(agent);

	else if (agent.state ==  AGENT_STATE::TRAVEL_HOME_TO_DANCE) transitionProbabilities = transitionProbabilitiesTravelDance(agent);

	else if (agent.state == AGENT_STATE::TRAVEL_HOME_TO_REST) transitionProbabilities = transitionProbabilitiesTravelRest(agent);

	else if (agent.state == AGENT_STATE::TRAVEL_SITE) transitionProbabilities = transitionProbabilitiesTravelSite(agent);

	else abort();

	//pick a new state based from the keys that each have their own probability

	//if the new site is not none create a copy of the new site and then set it back to none
	//return the new state and the copy of the site

	//else return the new state and none as the site attached
	return AGENT_STATE::REST;
}
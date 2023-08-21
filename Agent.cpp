#include <iostream>
#include "Agent.h"
#include "Transitions.h"

using namespace std;

Agent::Agent(pair<double, double> pos, int world) {
	position = pos;
	assignedWorld = world;
}

void Agent::step() {
 	tuple<string, Site> result = getTransition(*this);
	string nextState = get<0>(result);
	Site nextSite = get<1>(result);

	state = nextState;

	if (state == "TRAVEL HOME TO DANCE" || state == "TRAVEL HOME TO REST") {
		if (!agentAtHub(*this)) goHome();
	}
	else if (state == "TRAVEL SITE") {
		if (!agentAtAssignedSite(*this)) goSite();
	}
	else if (state == "EXPLORE") {
		if (!agentAtAnySite(*this).first) explore();
	}
	else {
		speed = 0.0;

		default_random_engine gen;
		uniform_real_distribution<double> distribution(0.0, 1.0);
		double randomValue = distribution(gen);

		dir = { acos(randomValue), asin(randomValue) };
	}
	return;

	//Get the next state and new site from transitions file

	//Set the new state of the agent 
	//Set the assigned site to the new site

	//if the state of the agent is either of the travel home states call goHome function

	//else if the state of the agent is travel_site call the goSite function

	//else if the state of the agent is explore and the agent is not at any site call the explore function

	//else change the speed of the agent to 0.0 
		//create a random value and set the direction of the agent to {cos(random), sin(random)}
}

void Agent::goHome() {
	speed = AGENT_SPEED;

	if (assignedSite.id = -1) abort;

	dir = getSiteDir(position, assignedSite.position);
	position.first += speed * dir.first;
	position.second += speed * dir.second;

	return;

	//set the agent speed to AGENT_SPEED
	
	//set the direction to getHomeDir(*this.pos)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}

void Agent::goSite() {
	speed = AGENT_SPEED;

	if (assignedSite.id = -1) abort;

	dir = getSiteDir(position, assignedSite.position);
	position.first += speed * dir.first;
	position.second += speed * dir.second;

	return;

	//set the agent speed to AGENT_SPEED

	//change the direction to getSiteDir(pos, assignedSite.pos)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}

void Agent::explore() {
	speed = AGENT_SPEED;

	dir = getExploreDir(dir);
	position.first += speed * dir.first;
	position.second += speed * dir.second;

	return;

	//set the agent speed to AGENT_SPEED

	//change the direction to getExploreDir(dir)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}
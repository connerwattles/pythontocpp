#include <iostream>
#include "Agent.h"
#include "Transitions.h"

using namespace std;

Agent::Agent(Position pos, int world) {
	position = pos;
	assignedWorld = world;
}

void Agent::step() {
	cout << "position: " << position.getX() << ", " << position.getY() << endl;

	string nextState = getTransition(*this);

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
	//set the agent speed to AGENT_SPEED
	
	//set the direction to getHomeDir(*this.pos)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}

void Agent::goSite() {
	//set the agent speed to AGENT_SPEED

	//change the direction to getSiteDir(pos, assignedSite.pos)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}

void Agent::explore() {
	//set the agent speed to AGENT_SPEED

	//change the direction to getExploreDir(dir)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}
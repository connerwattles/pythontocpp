#include <iostream>
#include "Agent.h"

using namespace std;


void Agent::step(const vector<int>& dancerCountBySite, int numDancers) {
 	tuple<AGENT_STATE, Site*> result = getTransition(dancerCountBySite, numDancers);
	AGENT_STATE nextState = get<0>(result);
	Site* nextSite = get<1>(result);

    if (nextSite != nullptr)
        assignedSite = nextSite;
	state = nextState;

	if (state == AGENT_STATE::TRAVEL_HOME_TO_DANCE || state == AGENT_STATE::TRAVEL_HOME_TO_REST) {
		if (!isAtHub()) goHome();
	}
	else if (state == AGENT_STATE::TRAVEL_SITE) {
		if (!isAtAssignedSite()) goSite();
	}
	else if (state == AGENT_STATE::EXPLORE) {
		if (!isAtAnySite().first) explore();
    }
	else {
        speed = 0.0;
		default_random_engine gen;
        uniform_real_distribution<double> distribution(0.0, 1.0);
        double randomValue = distribution(gen);

        direction = { acos(randomValue), asin(randomValue) };
//        direction.normalize();
	}
}

void Agent::goHome() {
	speed = AGENT_SPEED;

//    if (assignedSite == nullptr) assert(false, "should not happen (goHome)");
// TODO:: ASK ABOUT THIS PARTICULAR LINE

	direction = getHomeDir();
    advance_agent();

	//set the agent speed to AGENT_SPEED

	//set the direction to getHomeDir(*this.pos)

	//set x value of position to the agent speed * dir.at(0)
	//set y value of position to the agent speed * dir.at(1)
}

void Agent::goSite() {
	speed = AGENT_SPEED;

    if (assignedSite == nullptr) abort();

    direction = Direction::getDirection(&position, &(assignedSite->position));
//    direction.normalize();
    advance_agent();

	return;
}

void Agent::explore() {
	speed = AGENT_SPEED;

    direction = direction.getExploreDir();
//    direction.normalize();
    advance_agent();
}



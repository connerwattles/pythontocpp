#pragma once
#include <iostream>
#include "Site.h"
#include "Position.h"
#include "Agent_State.h"
#include "Direction.h"

using namespace std;

class Agent
{
public:
	Position position = { 0, 0 };
	AGENT_STATE state = AGENT_STATE::REST;
	Site assignedSite;
	Direction direction = { 0, 1 };
	int speed = 0;

	int assignedWorld;
	//World* assignedWorld;


	Agent(Position pos, int world);

	void step();

	void goHome();

	void goSite();

	void explore();
};
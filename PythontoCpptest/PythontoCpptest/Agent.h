#pragma once
#include <iostream>
#include "Site.h"

using namespace std;

class Agent
{
public:
	pair<double, double> position = { 0, 0 };
	string state = "REST";
	Site assignedSite;
	pair<double, double> dir = { 0, 1 };
	int speed = 0;

	int assignedWorld;
	//World* assignedWorld;


	Agent(pair<double, double> pos, int world);

	void step();

	void goHome();

	void goSite();

	void explore();
};
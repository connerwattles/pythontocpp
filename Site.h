#pragma once
#include <iostream>
#include "Position.h"
using namespace std;

class Site
{
public:
	int id;
	double quality;
	int agentsAssigned;
	Position position;

	Site();

	Site(int i, double qual, Position pos);
};


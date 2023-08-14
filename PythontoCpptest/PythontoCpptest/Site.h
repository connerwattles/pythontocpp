#pragma once
#include <iostream>

using namespace std;

class Site
{
public:
	int id;
	double quality;
	int agentsAssigned;
	pair<double, double> position;

	Site();

	Site(int i, double qual, pair<double, double> pos);
};


#pragma once
#include <iostream>
#include <vector>
#include "Site.h"
#include "Agent.h"

using namespace std;

class World
{

public:
	int worldInd = -1;

	int numSites;
	int numAgents;
	vector<double> siteQualities;
	vector<pair<float, float>> sitePoses;
	double convergedToSite = 0.0;

	int time = 0;

	int iterations = 0;

	vector<Agent> agents;

	vector<Site> sites;

	World();

	World(int ind, int sites, vector<double> qualities, vector<pair<float, float>> poses, int agents);	//Update data type for siteQual and SitePos

	void saveMetaData();

	void addAgents();

	void simulate();

	void printValues();
};
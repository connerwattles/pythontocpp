#include "World.h"
#include "Agent.h"
#include "HelperFunctions.h"
#include "Params.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

World::World() {
	numSites = 0;
	numAgents = 0;
	sitePositions = { Position(0,0),Position(0,0) };
	siteQualities = {0};
}

World::World(int ind, int sites, vector<double> qualities, vector<Position> poses, int agents) {
	worldInd = ind;
	numSites = sites;
	numAgents = agents;
	siteQualities = qualities;
    sitePositions = poses;
}

void World::saveMetaData() {

}

void World::addAgents() {
	for (int agent = 0; agent < numAgents; agent++) {
		Agent newAgent({ 0, 0 }, worldInd);
		
		agents.push_back(newAgent);
	}
	return;
}

void World::simulate() {
	vector<vector<pair<double, double>>> allPoses;
	vector<vector<pair<double, double>>> allDirs;
	vector<vector<string>> allStates;
	vector<vector<Site>> allSites;

	addAgents();

	tuple<vector<pair<double, double>>, vector<pair<double, double>>, vector<string>, vector<Site>> values;
	values = getAllAgentPosesDirsStatesSites(*this);

	vector<pair<double, double>> poses = get<0>(values);
	vector<pair<double, double>> dirs = get<1>(values);
	vector<string> states = get<2>(values);
	vector<Site> sites = get<3>(values);

	//save copies of each of the values to another data structure so it can be added to a dataframe

	allPoses.push_back(poses);
	allDirs.push_back(dirs);
	allStates.push_back(states);
	allSites.push_back(sites);

	while (time < TIME_LIMIT)  {
		for (auto agent : agents) {
			agent.step();
		}

		time += 1;

		values = getAllAgentPosesDirsStatesSites(*this);

		vector<pair<double, double>> poses = get<0>(values);
		vector<pair<double, double>> dirs = get<1>(values);
		vector<string> states = get<2>(values);
		vector<Site> sites = get<3>(values);


		allPoses.push_back(poses);
		allDirs.push_back(dirs);
		allStates.push_back(states);
		allSites.push_back(sites);

		vector<int> dancers = getDancersBySiteForWorld(*this);
		if (*max_element(dancers.begin(), dancers.end()) > (COMMIT_THRESHOLD * numAgents)) {
			int max = 0;
			int index = 0;
			for (int i = 0; i < dancers.size(); i++) {
				if (dancers.at(i) > max) {
					max = dancers.at(i);
					index = i;
				}
			}
			convergedToSite = sites.at(index).quality;
			// set convergedToSite to the quality of the site with the most dancers
			break;
		}
	}

	ofstream outFile;
	outFile.open("./sim_results/" + to_string(iterations) + ".csv");
	outFile << "time, agent_position, agent_directions, agent_states, agent_sites, \n";
	outFile << "[";
	for (int i = 0; i < allPoses.size(); i++) {
		outFile << "\"[";
		for (int j = 0; j < allPoses.at(i).size(); j++) {
			outFile << to_string(allPoses.at(i).at(j).first) + ", " + to_string(allPoses.at(i).at(j).second);
		}
		outFile << "], ";
	}
	outFile << "\",";
	//something similar to this for the other three
	

	//create something similar to a dataframe that stores the list of values then save to metadata

	//write the values to a csv
}

void World::printValues() {
	cout << numSites << " " << numAgents << " ";
	for (int i = 0; i < siteQualities.size(); i++) cout << siteQualities.at(i) << " ";
	cout << " " << sitePoses.at(0).first << endl;
};
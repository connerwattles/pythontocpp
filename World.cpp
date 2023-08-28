#include "World.h"
#include "Agent.h"
#include "Params.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


World::World(int siteCount, vector<Site*> sites, int agentCount, string uniqueFileName) {
	numSites = siteCount;
	numAgents = agentCount;
	this->sites = sites;
    this->uniqueFileName = uniqueFileName;
}



void World::simulateSingleThreaded() {
//	vector<vector<Position>> allPoses;
//	vector<vector<Direction>> allDirs;
//	vector<vector<AGENT_STATE>> allStates;
//	vector<vector<Site*>> allSites;

	addAgents();



	//save copies of each of the values to another data structure so it can be added to a dataframe

//	allPoses.push_back(poses);
//	allDirs.push_back(dirs);
//	allStates.push_back(states);
//	allSites.push_back(agent_sites);

	while (time < TIME_LIMIT)  {
        vector<int> dancerCountBySize = getDancerCountBySite();
        int numDancers = accumulate(dancerCountBySize.begin(), dancerCountBySize.end(), 0);

        tuple<vector<Position>, vector<Direction>, vector<AGENT_STATE>, vector<Site*>> values;
        values = getAllAgentPosesDirsStatesSites();

        vector<Position> poses = get<0>(values);
        vector<Direction> dirs = get<1>(values);
        vector<AGENT_STATE> states = get<2>(values);
        vector<Site*> agent_sites = get<3>(values);

		for (auto agent : agents) {
//            cout << "step: " << time << ", agent: " << agent->id << ", state: " << Agent::toString(agent->state) << endl;
//            cout << "step: " << time << agent->toString() << endl;
			agent->step(dancerCountBySize, numDancers);
		}
		time += 1;
        if (time % 100 == 0)
            cout << "steps taken: " << time << endl;

//		values = getAllAgentPosesDirsStatesSites();
//
//		poses = get<0>(values);
//		dirs = get<1>(values);
//		states = get<2>(values);
//		agent_sites = get<3>(values);
//
//
//		allPoses.push_back(poses);
//		allDirs.push_back(dirs);
//		allStates.push_back(states);
//		allSites.push_back(agent_sites);

		vector<int> dancers = getDancerCountBySite();
        int maxVal = -1;
        int maxIndex = -1;
        for (int currDancerIndex = 0; currDancerIndex < dancers.size(); ++currDancerIndex)
        {
            if (dancers.at(currDancerIndex) > maxIndex)
            {
                maxIndex = currDancerIndex;
                maxVal = dancers.at(currDancerIndex);
            }
        }
		if (maxVal > (COMMIT_THRESHOLD * numAgents)) {
            // set convergedToSite to the quality of the site with the most dancers
            convergedToSite = sites.at(maxIndex)->quality;
			break;
		}
	}
    for (Agent* agent : agents)
    {
        cout << "deleting agent" << endl;
        delete agent;
    }
//	ofstream outFile;
//	outFile.open("./sim_results/" + to_string(iterations) + ".csv");
//	outFile << "time, agent_position, agent_directions, agent_states, agent_sites, \n";
//	outFile << "[";
//	for (int i = 0; i < allPoses.size(); i++) {
//		outFile << "\"[";
//		for (int j = 0; j < allPoses.at(i).size(); j++) {
//			outFile << to_string(allPoses.at(i).at(j).x) + ", " + to_string(allPoses.at(i).at(j).y);
//		}
//		outFile << "], ";
//	}
//	outFile << "\",";
	//something similar to this for the other three
	

	//create something similar to a dataframe that stores the list of values then save to metadata

	//write the values to a csv
}


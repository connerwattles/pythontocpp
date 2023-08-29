#include "World.h"
#include "Agent.h"
#include "Params.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;


World::World(int siteCount, vector<Site*> sites, int agentCount, string uniqueFileName) {
	numSites = siteCount;
	numAgents = agentCount;
	this->sites = sites;
    this->uniqueFileName = uniqueFileName;
}



void World::simulateSingleThreaded() {
	addAgents();

    tuple<vector<Position>, vector<Direction>, vector<AGENT_STATE>, vector<Site*>> start = getAllAgentPosesDirsStatesSites();
    
    ofstream outFile;
    outFile.open("./sim_results/" + uniqueFileName + ".csv", ios_base::app);                    //check again to make file name unique

    outFile << ",time,agent_positions,agent_directions,agent_states,agentsites\n";

	while (time < TIME_LIMIT)  {
        vector<int> dancerCountBySize = getDancerCountBySite();
        int numDancers = accumulate(dancerCountBySize.begin(), dancerCountBySize.end(), 0);

		for (auto agent : agents) {
//            cout << "step: " << time << ", agent: " << agent->id << ", state: " << Agent::toString(agent->state) << endl;
//            cout << "step: " << time << agent->toString() << endl;
			agent->step(dancerCountBySize, numDancers);
		}
		time += 1;
        if (time % 100 == 0)
            cout << "steps taken: " << time << endl;


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
        tuple<vector<Position>, vector<Direction>, vector<AGENT_STATE>, vector<Site*>> values;
        values = getAllAgentPosesDirsStatesSites();

        vector<Position> poses = get<0>(values);
        vector<Direction> dirs = get<1>(values);
        vector<AGENT_STATE> states = get<2>(values);
        vector<Site*> agent_sites = get<3>(values);

        outFile << to_string(time) << "," << to_string(time) << ",[";

        for (int i = 0; i < poses.size(); i++) {
            outFile << "[" << to_string(poses.at(i).getX()) << ", " << to_string(poses.at(i).getY()) << "], ";
        }

        outFile << "], [";

        for (int i = 0; i < dirs.size(); i++) {
            outFile << "[" << to_string(dirs.at(i).getXComponent()) << ", " << to_string(dirs.at(i).getYComponent()) << "], ";
        }

        outFile << "], [";

        for (int i = 0; i < states.size(); i++) {
            outFile << states.at(i) << ", " ;
        }

        outFile << "], [";

        for (int i = 0; i < agent_sites.size(); i++) {
            int val = agent_sites.at(i)->id;

            if (val == -1) outFile << "None, ";
            else outFile << to_string(val) << ", ";
        }

        outFile << "]\n";
        outFile.close();
	}
    for (Agent* agent : agents)
    {
        cout << "deleting agent" << endl;
        delete agent;
    }

    ofstream metadata;
    metadata.open("./sim_results/" + uniqueFileName + "metadata" + ".csv", ios_base::app);
    metadata << ",num_sites,site_qualities,site_positions,hub_position,num_agents,site_converged,time_converged\n";
    metadata << to_string(numSites) << "," << "(";
    for (int i = 0; i < numSites; i++) {
        //write to csv each site quality
    }
    metadata << "),(";
    for (int i = 0; i < numSites; i++) {
        //write position for site
    }
    metadata << "),[" << to_string(HUB_LOCATION.getX()) << ", " << to_string(HUB_LOCATION.getY()) << "]," <<
        to_string(numAgents) << ",";    //Add num sites converged and time converged
}


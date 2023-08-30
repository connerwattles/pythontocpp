#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Site.h"
#include "Agent.h"

using namespace std;

class World
{

public:

	int numSites;
	int numAgents;
	double convergedToSite = 0.0;
    string uniqueFileName;
//	int iterations = 0;

	vector<Agent*> agents;

	vector<Site*> sites;

	World(int siteCount, vector<Site*> sites, int agentCount, string uniqueFileName);	//Update data type for siteQual and SitePos

	void saveMetaData()
    {
        cout << "not done yet" << endl;
    }

    void addAgents() {
        for (int agent = 0; agent < numAgents; agent++) {
            Agent* newAgentPtr = new Agent(agent, { 0, 0 }, sites);

            agents.push_back(newAgentPtr);
        }
    }

	void simulateSingleThreaded();

    vector<int> getDancerCountBySite() {
        vector<int> dancerCountBySite;
        for (int i = 0; i < numSites; i++) {
            dancerCountBySite.push_back(0);
        }
        for (Agent* agent : agents) {
            if (agent->state == AGENT_STATE::DANCE) {
                getters::assert(agent->assignedSite != nullptr, "assigned site must not be null (getDancerCountBySite)");
                dancerCountBySite.at(agent->assignedSite->id) += 1;
            }
        }
        return dancerCountBySite;
    }

    tuple<vector<Position>, vector<Direction>, vector<AGENT_STATE>, vector<Site*>> getAllAgentPosesDirsStatesSites() {
        vector<Position> poses;
        vector<Direction> dirs;
        vector<AGENT_STATE> states;
        vector<Site*> sites;
        for (Agent* agent : agents) {
            poses.push_back(agent->position);
            dirs.push_back(agent->direction);
            states.push_back(agent->state);
            sites.push_back(agent->assignedSite);
        }
        return make_tuple(poses, dirs, states, sites);
    }

    void addLineToCSV(bool firstLine, int time)
    {
        ofstream outFile;

        if (firstLine)
        {
            outFile.open("sim_results/" + uniqueFileName + ".csv");
            outFile << "time, agent_position, agent_directions, agent_states, agent_sites" << endl;
        }
        else
        {
            outFile.open("sim_results/" + uniqueFileName + ".csv", std::ofstream::app);
        }
        outFile << time << ",";
        outFile << "[";
        for (int ag = 0; ag < numAgents; ag++)
        {
            outFile << "[" << agents.at(ag)->position.getX() << ", "
                    << agents.at(ag)->position.getY() << "], ";
        }
        outFile << "],";
        outFile << "[";
        for (int ag = 0; ag < numAgents; ag++)
        {
            outFile << "[" << agents.at(ag)->direction.getXComponent() << ", "
                    << agents.at(ag)->direction.getYComponent() << "], ";
        }
        outFile << "],";
        outFile << "[";
        for (int ag = 0; ag < numAgents; ag++)
        {
            outFile << Agent::toString(agents.at(ag)->state) << ",";
        }
        outFile << "],";
        outFile << "[";
        for (int ag = 0; ag < numAgents; ag++)
        {
            if (agents.at(ag)->assignedSite == nullptr) outFile << "None, ";
            else outFile << agents.at(ag)->assignedSite->id << ",";
        }
        outFile << "]" << endl;
        outFile.close();
    }

    void simulateMultiThreaded();
};
#endif
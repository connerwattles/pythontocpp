#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include "Site.h"
#include "Agent.h"

using namespace std;

class World
{

public:

	int numSites;
	int numAgents;
	double convergedToSite = 0.0;
    //string uniqueFileName;

	int time = 0;

//	int iterations = 0;

	vector<Agent*> agents;

	vector<Site*> sites;

	World(int siteCount, vector<Site*> sites, int agentCount);	//Update data type for siteQual and SitePos

	void saveMetaData()
    {
        cout << "SAVE META DATA IS NOT DONE YET" << endl;
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
};
#endif
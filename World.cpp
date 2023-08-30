#include "World.h"
#include "Agent.h"
#include "Params.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>
#include <thread>

using namespace std;


World::World(int siteCount, vector<Site*> sites, int agentCount, string uniqueFileName) {
	numSites = siteCount;
	numAgents = agentCount;
	this->sites = sites;
    this->uniqueFileName = uniqueFileName;
}



void World::simulateSingleThreaded() {

	addAgents();

    saveMetaData();
    this->addLineToCSV(true, 0);
    vector<int> dancerCountBySize = getDancerCountBySite();
    int numDancers = 0;
    int time = 0;
	while (time < TIME_LIMIT)  {
		for (auto agent : agents) {
			agent->step(dancerCountBySize, numDancers);
		}
		time += 1;
        if (time % 500 == 0)
            cout << "steps taken: " << time << endl;
        this->addLineToCSV(false, time);


        dancerCountBySize = getDancerCountBySite();
        numDancers = accumulate(dancerCountBySize.begin(), dancerCountBySize.end(), 0);
        int maxVal = -1;
        int maxIndex = -1;
        for (int currDancerIndex = 0; currDancerIndex < dancerCountBySize.size(); ++currDancerIndex)
        {
            if (dancerCountBySize.at(currDancerIndex) > maxIndex)
            {
                maxIndex = currDancerIndex;
                maxVal = dancerCountBySize.at(currDancerIndex);
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
//        cout << "deleting agent" << endl;
        delete agent;
    }
    for (auto site : sites)
    {
//                    cout << "deleting site" << endl;
        delete site;
    }

}

void World::simulateMultiThreaded() {

    addAgents();

    saveMetaData();
    this->addLineToCSV(true, 0);
    vector<int> dancerCountBySize = getDancerCountBySite();
    int numDancers = 0;
    int time = 0;
    while (time < TIME_LIMIT)  {

        std::vector<std::thread> threads; // To store the threads

        // Launch threads for each agent's step function
        for (auto agent : agents) {
            threads.emplace_back([&]() {
                agent->step(dancerCountBySize, numDancers);
            });
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }
        time += 1;
        if (time % 500 == 0)
            cout << "steps taken: " << time << endl;
        this->addLineToCSV(false, time);


        dancerCountBySize = getDancerCountBySite();
        numDancers = accumulate(dancerCountBySize.begin(), dancerCountBySize.end(), 0);
        int maxVal = -1;
        int maxIndex = -1;
        for (int currDancerIndex = 0; currDancerIndex < dancerCountBySize.size(); ++currDancerIndex)
        {
            if (dancerCountBySize.at(currDancerIndex) > maxIndex)
            {
                maxIndex = currDancerIndex;
                maxVal = dancerCountBySize.at(currDancerIndex);
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
//        cout << "deleting agent" << endl;
        delete agent;
    }
    for (auto site : sites)
    {
//                    cout << "deleting site" << endl;
        delete site;
    }


}
#pragma once
#include <iostream>
#include "params.h"
#include "Agent.h"
#include "World.h"
#include <vector>
#include <random>
#include <time.h>
#include <tuple>


using namespace std;

extern vector<World> worlds;

//HELPER FUNCTIONS	

vector<vector<double>> getValidQualities(int num_sites, int num_configs) {
    vector<vector<double>> qual_arr;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    for (int config = 0; config < num_configs; config++) {
        std::vector<double> quals;
        for (int i = 0; i < num_sites; i++) {
            double qual = dis(gen);
            while (qual < 0.5) {
                qual = dis(gen);
            }
            quals.push_back(qual);
        }
        qual_arr.push_back(quals);
    }

    return qual_arr;
}

double getDist2D(pair<double, double> a, pair<double, double> b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

vector<pair<float, float>>  getPoses(int s, int d) {
    float pi = 2 * acos(0.0);
    double angles = 2 * pi / s;
    vector<pair<float, float>> poses;

    for (int i = 0; i < s; i++) {
        pair<float, float> pose;
        pose.first = (d * cos(angles * i));         
        pose.second = (d * sin(angles * i));        
        poses.push_back(pose);
    }
    return poses;
}

vector<double> getHomeDir(vector<double> pos) {                     
    vector<double> dir = { -1.0 * pos[0], -1.0 * pos[1] };

    double norm = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
    dir[0] /= norm;
    dir[1] /= norm;

    return dir;
}

vector<double> getSiteDir(vector<double> pos, vector<double> sitePos) { 
    vector<double> dir = { sitePos[0] - pos[0], sitePos[1] - pos[1] };
    double norm = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
    dir[0] /= norm;
    dir[1] /= norm;
    return dir;
}

vector<double> getExploreDir(vector<double> dir) {
    srand(static_cast <unsigned> (time(0)));
    float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


    if (random > EXPLORE_RANDOMNESS) {
        vector<int> intList{1, -1};
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(0, intList.size() - 1);
        int choice = intList[distr(eng)];

        float to_change_dir = EXPLORE_DIRECTION_CHANGE * (choice);
        double xchange = to_change_dir;
        double ychange = to_change_dir;
        dir[0] += xchange;
        dir[1] += ychange;
        double norm = sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
        dir[0] /= norm;
        dir[1] /= norm;
    }

    return dir;
}

bool agentAtAssignedSite(Agent ag) {    //Tested works
    if (&ag.assignedSite == NULL) return false;

    else if (getDist2D(ag.position, ag.assignedSite.position) < SITE_SIZE) return true;

    else return false;
}

bool agentAtHub(Agent ag) {     //Tested and works
    if (getDist2D(ag.position, HUB_LOCATION) < SITE_SIZE) return true;

    else return false;

    return false;
}

pair<bool, Site> agentAtAnySite(Agent ag) {
    World tempWorld = worlds.at(ag.assignedWorld);
    for (Site site : tempWorld.sites) {
        if (getDist2D(ag.position, site.position) < SITE_SIZE)
            return { true, site };
    }
    
    Site emptySite(0, 0, { 0, 0 });
    return { false, emptySite};
}

vector<int> getDancersBySiteForWorld(World world) {
    vector<int> dancers;
    for (int i = 0; i < world.numSites; i++) {
        dancers.push_back(0);
    }
    for (Agent agent : world.agents) {
        if (agent.state == "DANCE") {
            dancers.at(agent.assignedSite.id) += 1;
        }
    }
    return dancers;
}

vector<int> getDancersBySite(Agent ag) {
    World world = worlds.at(ag.assignedWorld);
    vector<int> dancers;
    for (int i = 0; i < world.numSites; i++) {
        dancers.push_back(0);
    }
    for (Agent agent : world.agents) {
        if (agent.state == "DANCE") {
            dancers.at(agent.assignedSite.id) += 1;
        }
    }
    return dancers;
}

tuple<vector<pair<double, double>>, vector<pair<double, double>>, vector<string>, vector<Site>> getAllAgentPosesDirsStatesSites(World world) {
    vector<pair<double, double>> poses;
    vector<pair<double, double>> dirs;
    vector<string> states;
    vector<Site> sites;
    for (Agent agent : world.agents) {
        poses.push_back(agent.position);
        dirs.push_back(agent.dir);
        states.push_back(agent.state);
        if (&(agent.assignedSite) != NULL) {
            sites.push_back(agent.assignedSite);
        }
        else {
            Site nullSite;
            Site* temp = &nullSite;
            temp = NULL;
            sites.push_back(nullSite);
        }
    }
    return make_tuple(poses, dirs, states, sites);
}
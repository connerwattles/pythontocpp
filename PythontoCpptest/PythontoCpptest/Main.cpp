#include <iostream>
#include <random>
#include "World.h"
#include "Position.h"

using namespace std;

vector<World> worlds;

/*void worldTest() {
	cout << "world test: ";

	vector<World> worlds;

	int sites = 2;
	int agents = 20;
	vector<double> qualities = { 2 };
	vector<pair<float, float>> positions = { {0,0}, {0,0} };

	World newWorld(0, sites, qualities, positions, agents);
	worlds.push_back(newWorld);

	newWorld.printValues();

	newWorld.addAgents();

	cout << worlds.at(newWorld.agents.at(0).assignedWorld).worldInd << endl;

	return;
}

void dist2DTest() {
	cout << "dist 2D test: ";

	pair<double, double> a;
	pair<double, double> b;

	a.first = 10;
	a.second = 9;

	b.first = 5;
	b.second = 4;

	cout << getDist2D(a, b) << endl;
	
	return;
}

void validQualitiesTest() {
	cout << "valid qualities test: ";

	vector<vector<double>> quals = getValidQualities(2, 3);
	for (int i = 0; i < quals.size(); i++) {
		for (int j = 0; j < quals.at(i).size(); j++) {
			cout << quals.at(i).at(j) << " ";
		}
		cout << " ";
	}
	cout << endl;
	
	return;
}

void posesTest() {
	cout << "positions test: ";

	vector<pair<float, float>> poses = getPoses(2, 100);
	for (int i = 0; i < poses.size(); i++) {
		cout << poses.at(i).first << " " << poses.at(i).second << "     ";
	}
	cout << endl;
	
	return;
}

void homeDirTest() {
	cout << "home direction test: ";

	vector<double> homeDirTest = { 45, -108 };
	vector<double> homeDirTestRes = getHomeDir(homeDirTest);
	cout << "homeDir: ";
	for (int i = 0; i < homeDirTestRes.size(); i++) {
		cout << homeDirTestRes.at(i) << " ";
	}
	cout << endl;
	
	return;
}

void siteDirTest() {
	cout << "site direction test: ";

	vector<double> siteDirRes = getSiteDir({ 0, 0 }, { -100, 0 });
	cout << "getSiteDir: ";
	for (int i = 0; i < siteDirRes.size(); i++) {
		cout << siteDirRes.at(i) << " ";
	}
	cout << endl;

	return;
}

void exploreDirTest() {
	cout << "explore direction test: ";

	vector<double> exploreDirRes = getExploreDir({ 0.9887, 0.14983 });
	cout << "getExploreDir: ";
	for (int i = 0; i < exploreDirRes.size(); i++) {
		cout << exploreDirRes.at(i) << " ";
	}
	cout << endl;
	
	return;
}

void agentAtHubTest() {
	cout << "agent at hub test: ";

	int sites = 2;
	int agents = 20;
	vector<double> qualities = { 2 };
	vector<pair<float, float>> positions = { {0,0}, {0,0} };

	World newWorld(0, sites, qualities, positions, agents);

	Agent tempAgent({ 0, 0 }, newWorld.worldInd);

	if (agentAtHub(tempAgent) == true) cout << "agent is at hub" << endl;
	else cout << "agent is not at hub" << endl;

	return;
}

void agentAtAssignedSiteTest() {
	cout << "agent at assigned site test: ";

	int sites = 2;
	int agents = 20;
	vector<double> qualities = { 2 };
	vector<pair<float, float>> positions = { {0,0}, {0,0} };

	World newWorld(0, sites, qualities, positions, agents);

	Agent tempAgent({ 3, 4.2 }, newWorld.worldInd);

	Site tempSite(0, 1.3, { 5, 5 });
	tempAgent.assignedSite = tempSite;
	bool isAtSite = agentAtAssignedSite(tempAgent);
	if (isAtSite) cout << "Agent is at Site";
	else if (!isAtSite) cout << "Agent is not at Site";
	else cout << "error";
	cout << endl;

	return;
}

void agentAtAnySiteTest() {
	cout << "agent at any site test: ";

	vector<World> worlds;

	int sites = 2;
	int agents = 20;
	vector<double> qualities = { 2 };
	vector<pair<float, float>> positions = { {0,0}, {0,0} };

	World newWorld(0, sites, qualities, positions, agents);
	worlds.push_back(newWorld);

	Agent tempAgent({ 0, 0 }, newWorld.worldInd);

	Site nextSite(1, 1.3, { -62, 3 });
	worlds.at(tempAgent.assignedWorld).sites.push_back(nextSite);
	Site anotherSite(2, 2.2, { 32, 21 });
	worlds.at(tempAgent.assignedWorld).sites.push_back(anotherSite);

	pair<bool, Site> agentAtAnySiteResult = agentAtAnySite(tempAgent, worlds);
	if (agentAtAnySiteResult.first) cout << "Agent is at a site " << agentAtAnySiteResult.second.id;
	else cout << "Agent not at any site";
	cout << endl;

	return;
}

int main() {
	worldTest();				//works

	dist2DTest();				//works

	validQualitiesTest();		//works

	posesTest();				//works

	homeDirTest();				//works

	siteDirTest();				//works

	exploreDirTest();			//works

	agentAtHubTest();			//works

	agentAtAssignedSiteTest();	//works

	agentAtAnySiteTest();		//works
}*/

vector<vector<double>> getValidQualitiesMain(int num_sites, int num_configs) {
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

vector<pair<float, float>>  getPosesMain(int s, int d) {
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

vector<World> generateWorldConfigs(int siteConfigs, vector<int> distances, int agentConfigs, int simsPerConfig, int simsPerDistance)
{
	vector<World> worlds;

	for (int distance = 0; distance < distances.size(); distance++) {
		for (int simDistance = 0; simDistance < simsPerDistance; simDistance++) {
			vector<pair<float, float>> poses = getPosesMain(siteConfigs, distances[distance]); //from helper function
			vector<vector<double>> qualities = getValidQualitiesMain(siteConfigs, simsPerConfig);
			for (int i = 0; i < qualities.size(); i++) {
				World newWorld(i, siteConfigs, qualities.at(i), poses, agentConfigs);
				worlds.push_back(newWorld);
			}
		}
	}
	return worlds;
}

int main() {
	int siteConfigs = 2;
	vector<int> distances = { 100, 200 };
	int agentConfigs = 20;
	int simsPerConfig = 10;
	int simsPerDistance = 20;

	//vector<World> worlds;

	worlds = generateWorldConfigs(siteConfigs, distances, agentConfigs, simsPerConfig, simsPerDistance);

	for (int sim = 0; sim < worlds.size(); sim++) {
		worlds.at(sim).simulate();
		cout << sim << " done" << endl;
	}
}
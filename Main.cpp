#include <iostream>
#include <random>
#include "World.h"

using namespace std;

vector<World> worlds;

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

vector<Position>  getPosesMain(int s, int d) {
	float pi = 2 * acos(0.0);
	double angles = 2 * pi / s;
	vector<Position> poses;

	for (int i = 0; i < s; i++) {
		Position p = {
                (d * cos(angles * i)),
                (d * sin(angles * i))
        };
		poses.push_back(p);
	}
	return poses;
}

void runWorlds(int siteConfigs, vector<int> distances, int agentConfigs, int simsPerConfig, int simsPerDistance)
{

	for (int distance = 0; distance < distances.size(); distance++) {
		for (int simDistance = 0; simDistance < simsPerDistance; simDistance++) {
			vector<Position> poses = getPosesMain(siteConfigs, distances[distance]); //from helper function
			vector<vector<double>> qualities = getValidQualitiesMain(siteConfigs, simsPerConfig);
			for (int i = 0; i < qualities.size(); i++) {
                vector<Site*> sites;
                sites.reserve(poses.size());
                for (int j = 0; j < poses.size(); ++j)
                    sites.push_back(new Site(j, qualities.at(i).at(j), poses.at(j)));
				World(siteConfigs, sites, agentConfigs).simulateSingleThreaded();
                for (auto site : sites)
                {
                    cout << "deleting site" << endl;
                    delete site;
                }
			}
		}
	}
}

int main() {
	int siteConfigs = 5;
	vector<int> distances = { 50 };
	int agentConfigs = 5;
	int simsPerConfig = 1;
	int simsPerDistance = 1;

    try
    {
        runWorlds(siteConfigs, distances, agentConfigs, simsPerConfig, simsPerDistance);
    }
    catch (const char* msg)
    {
        cout << msg << endl;
        return 1;
    }
    return 0;
//
//	for (int sim = 0; sim < worlds.size(); sim++) {
//		worlds.at(sim).simulateSingleThreaded();
//		cout << sim << " done" << endl;
//	}

}
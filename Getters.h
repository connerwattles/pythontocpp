#pragma once
#include <tuple>
#include <vector>
#include "HelperFunctions.h"
#include "Params.h"
#include "Site.h"

using namespace std;

double getRestToExploreProb(Agent agent, double p, double toTravelSite) {
	if (agentAtHub(agent)) return (p * (1 - toTravelSite));
	else return 0.0;
}

tuple<double, Site> getRestToTravelSiteProb(Agent agent, double p) {
	if (agentAtHub(agent)) {
		//vector<int> dancers = getDancersBySite(agent, )		FIGURE OUT HOW TO PASS THE VECTOR OF WORLDS
		if (p != 0) {
			//double prob = 1 * p / sum of dancers
			//set probs to choose to dancers divided by the sum of dancers
			//set togo to a random site probs to choose
		}
		else {
			// double prob = 0.0;
			//Site togo = None;
		}
		//return make_tuple(prob, togo);
	}
	else {
		//return make_tuple(0.0, None);
	}
}




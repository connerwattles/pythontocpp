#ifndef SITE_H
#define SITE_H
#include <iostream>
#include "Position.h"
#include "Params.h"
using namespace std;

class Site
{
public:
	int id = 0;
	double quality = 0;
	int agentsAssigned = 0;
	Position position = Position(0,0);

    Site(int i, double qual , Position pos) {
        id = i;
        quality = qual;
        agentsAssigned = 0;
        this->position = pos;
    }

    bool isInSite(const Position* p) const
    {
        if (p->getDist2D(position) < SITE_SIZE)
            return true;
        return false;
    }
};
#endif
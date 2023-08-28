//
// Created by walte on 8/15/2023.
//

#ifndef DIRECTION_H
#define DIRECTION_H

#include <ostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Position.h"
#include "Params.h"
#include <vector>
#include <random>
#include <time.h>
#include <tuple>

class Direction
{
public:
    double x_component;
    double y_component;

    void normalize()
    {
//        cout << "normalized" << endl;
        double norm = sqrt((x_component * x_component) + (y_component * y_component));
        this->x_component = x_component / norm;
        this->y_component = y_component / norm;
    }

    Direction(double xComponent, double yComponent) : x_component(xComponent), y_component(yComponent)
    {

    }

    double getXComponent() const
    {
        return x_component;
    }

    void setXComponent(double xComponent)
    {
        x_component = xComponent;
    }

    double getYComponent() const
    {
        return y_component;
    }

    void setYComponent(double yComponent)
    {
        y_component = yComponent;
    }

    bool operator==(const Direction &rhs) const
    {
        return x_component == rhs.x_component &&
               y_component == rhs.y_component;
    }

    bool operator!=(const Direction &rhs) const
    {
        return !(rhs == *this);
    }

    bool operator<(const Direction &rhs) const
    {
        if (x_component < rhs.x_component)
            return true;
        if (rhs.x_component < x_component)
            return false;
        return y_component < rhs.y_component;
    }

    bool operator>(const Direction &rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(const Direction &rhs) const
    {
        return !(rhs < *this);
    }

    bool operator>=(const Direction &rhs) const
    {
        return !(*this < rhs);
    }

    friend ostream &operator<<(ostream &os, const Direction &direction)
    {
        os << "x_component: " << direction.x_component << " y_component: " << direction.y_component;
        return os;
    }

    static Direction getDirection(Position* from, Position* to)
    {
        Direction dir = { to->x - from->x, to->y - from->y };
//        dir.normalize();
        return dir;
    }

    Direction getExploreDir() {
        srand(static_cast <unsigned> (time(0)));
        float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


        Direction dir(x_component, y_component);
        if (random > EXPLORE_RANDOMNESS) {
            vector<int> intList{1, -1};
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(0, intList.size() - 1);
            int choice = intList[distr(eng)];

            float to_change_dir = EXPLORE_DIRECTION_CHANGE * (choice);
            double xchange = to_change_dir;
            double ychange = to_change_dir;

            dir.x_component += xchange;
            dir.y_component += ychange;
        }

//        dir.normalize();
        return dir;
    }
};



#endif //RESEARCH_LAB_DIRECTION_H

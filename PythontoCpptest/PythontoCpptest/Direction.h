//
// Created by walte on 8/15/2023.
//

#ifndef RESEARCH_LAB_DIRECTION_H
#define RESEARCH_LAB_DIRECTION_H

#include <ostream>
#include <string>
#include <sstream>

class Direction
{
public:
    double x_component;
    double y_component;

    void normalize()
    {
        double norm = sqrt((x_component * x_component) + (y_component * y_component));
        this->x_component = x_component * norm;
        this->y_component = y_component * norm;
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


};


#endif //RESEARCH_LAB_DIRECTION_H

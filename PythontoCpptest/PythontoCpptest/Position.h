//
// Created by walte on 8/15/2023.
//

#ifndef RESEARCH_LAB_POSITION_H
#define RESEARCH_LAB_POSITION_H


#include <ostream>
#include <string>
#include <sstream>

class Position
{
public:
    double x;
    double y;

    Position(double x, double y) : x(x), y(y)
    {}

    double getX() const
    {
        return x;
    }

    void setX(double x)
    {
        Position::x = x;
    }

    double getY() const
    {
        return y;
    }

    void setY(double y)
    {
        Position::y = y;
    }

    bool operator==(const Position &rhs) const
    {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Position &rhs) const
    {
        return !(rhs == *this);
    }

    bool operator<(const Position &rhs) const
    {
        if (x < rhs.x)
            return true;
        if (rhs.x < x)
            return false;
        return y < rhs.y;
    }

    bool operator>(const Position &rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(const Position &rhs) const
    {
        return !(rhs < *this);
    }

    bool operator>=(const Position &rhs) const
    {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Position &position)
    {
        os << "x: " << position.x << " y: " << position.y;
        return os;
    }

    std::string toString() const
    {
        std::stringstream os;
        os << "x: " << x << " y: " << y;
        return os.str();
    }

};


#endif //RESEARCH_LAB_POSITION_H

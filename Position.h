//
// Created by walte on 8/15/2023.
//

#ifndef POSITION_H
#define POSITION_H


#include <ostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;
class Position
{
public:
    double x;
    double y;

    vector<Position>  createPositions(int s, int d) {
        double pi = 2 * acos(0.0); // is there a reason we manually recalculate pi every time?
        double angles = 2 * pi / s;
        vector<Position> positions;

        for (int i = 0; i < s; i++) {
            Position position = {
                    (d * cos(angles * i)),
                    (d * sin(angles * i))
            };
            positions.push_back(position);
        }
        return positions;
    }

    double getDist2D(const Position& other) const
    {
        return sqrt(pow(this->getX() - other.getX(), 2) + pow(this->getY() - other.getY(), 2));
    }

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


#endif //POSITION_H

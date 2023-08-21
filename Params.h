#pragma once
#ifndef PARAMS_H
#define PARAMS_H

#include <utility>
#include "Position.h"
using namespace std;

//Environment
const Position  HUB_LOCATION(0, 0);

const int SITE_SIZE = 20;

const int ENVIRONMENT_BOUNDARY_X[4] = { -1000, -1000, 1000, 1000 };
const int ENVIRONMENT_BOUNDARY_Y[4] = { -1000, 1000, 1000, -1000 };

const int TIME_LIMIT = 35000;

const double COMMIT_THRESHOLD = 0.3;

//Agent

const int AGENT_SPEED = 5;
const int AGENT_AGENT_SENSING_DISTANCE = 20;
const double EXPLORE_RANDOMNESS = 0.1;
const double EXPLORE_DIRECTION_CHANGE = (2 * acos(0.0)) / 30;
const float SITE_QUALITY_ASSESS_THRESHOLD = 0.25;

const double BINOMIAL_COEFF_REST_TO_ASSESS_PER_DANCE = 0.1;
const double BINOMIAL_COEFF_ASSESS_TO_DANCE = 0.1;
const double BINOMIAL_COEFF_EXPLORE_TO_REST = 0.02;
const double BINOMIAL_COEFF_DANCE_TO_REST = 0.999;
const double BINOMIAL_COEFF_REST_TO_EXPLORE = 0.01;

//for the detachment
const float BASE_DANCE_TO_ASSESS = 10;
const float PWR_DANCE_TO_ASSESS = -2.0;
const float MULTIPLIER_DANCE_QUAL = -10.0;

const pair<double, double> qualities[30] = { {0.01, 1.0} ,{0.05, 0.7},{0.1, 1.0},{0.2, 1.0},{0.3, 1.0},{0.4, 1.0},
    {0.5, 1.0},{0.6, 1.0},{0.7, 1.0},{0.8, 1.0},{0.9, 1.0},{0.99, 1.0},{0.1, 0.75},{0.2, 0.75},{0.3, 0.75},{0.4, 0.75},
    {0.5, 0.75},{0.6, 0.75},{0.7, 0.75},{0.8, 0.75},{0.9, 0.75},{0.1, 0.6},{0.2, 0.6},{0.3, 0.6},{0.4, 0.6},{0.5, 0.6},
    {0.6, 0.6},{0.7, 0.6},{0.8, 0.6},{0.9, 0.6} };

#endif[]
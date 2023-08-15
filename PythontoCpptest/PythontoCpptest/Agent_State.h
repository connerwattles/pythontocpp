//
// Created by walte on 8/14/2023.
//

#ifndef RESEARCH_LAB_AGENT_STATE_H
#define RESEARCH_LAB_AGENT_STATE_H
#include <string>
enum class AGENT_STATE {
    REST,
    TRAVEL_HOME_TO_DANCE,
    TRAVEL_HOME_TO_REST,
    TRAVEL_SITE,
    EXPLORE,
    DANCE,
    ASSESS
};

string toString(const AGENT_STATE state)
{
    switch (state)
    {
        case AGENT_STATE::REST: return "REST";
        case AGENT_STATE::TRAVEL_HOME_TO_DANCE: return "TRAVEL_HOME_TO_DANCE";
        case AGENT_STATE::TRAVEL_HOME_TO_REST: return "TRAVEL_HOME_TO_REST";
        case AGENT_STATE::TRAVEL_SITE: return "TRAVEL_SITE";
        case AGENT_STATE::EXPLORE: return "EXPLORE";
        case AGENT_STATE::DANCE: return "DANCE";
        case AGENT_STATE::ASSESS: return "ASSESS";
    }
}
#endif //RESEARCH_LAB_AGENT_STATE_H

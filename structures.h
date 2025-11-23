#pragma once
#include <string>
#include <vector>

struct activity {
    int id;
    std::string name;
    std::string city;
    std::vector<std::string> category;
    std::string s_price;
    float price;
    double duration_hours;
    std::string description;
};

struct final_list_filtered_activities {
    activity* act;
    bool perfect;
    bool good;
};

extern std::vector<activity> activities;
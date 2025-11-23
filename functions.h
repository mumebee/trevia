#pragma once
#include <string>
#include <vector>
#include "structures.h"

std::string convert_str_lower(std::string s);
bool str_inside_str(std::string full, std::string part);
std::vector<std::string> split_string(const std::string& input, char separation);
bool activity_match(const std::vector<std::string>& categories, const std::string& u_preferences);
bool perfect_activity(const std::vector<std::string>& categories, const std::vector<std::string>& u_preferences);
bool good_activity(const std::vector<std::string>& categories, const std::vector<std::string>& u_preferences);
std::vector<activity*> filter_by_city(std::vector<activity> &all_activities, const std::vector<std::string>& u_cities);
std::vector<final_list_filtered_activities> filter_by_preference(std::vector<activity*>& activities_to_check, const std::vector<std::string>& u_preferences);
void display(const activity& activity);
void suggestions(const std::vector<final_list_filtered_activities>& filtered, float budget);
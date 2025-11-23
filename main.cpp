#include <iostream>
#include <vector>
#include <string>
#include "functions.h"
#include "structures.h"

using namespace std;

string welcome_message = "----------------------------------------------\n      TREVIA: UZBEKISTAN ACTIVITY FINDER      \n----------------------------------------------\n\n";
string final_message = "----------------------------------------------\n                END OF RESULTS                \n Thank you for using Trevia! Enjoy your trip! \n          See you for your next one!          \n";


int main(){
    cout << welcome_message;

    string name, budget_input, user_preferences, cities, single_city;
    float budget;
    int num_cities;
    vector<string> user_cities;

    cout << "Good day! What is your name? ";
    getline(cin, name);

    cout << "Hello " << name << "! " << endl;

    do {
        cout << "How many cities (from SAMARKAND, TASHKENT, BUKHARA) would you like to explore? (1-3): ";
        cin >> num_cities;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 3.\n";
            continue;
        }

        cin.ignore(10000, '\n'); // clears leftover input
    }
    while (num_cities < 1 || num_cities > 3);

vector<string> valid_cities = {"samarkand", "tashkent", "bukhara"};

for (int i = 1; i <= num_cities; i++) {

    cout << "Enter city #" << i << ": ";

    string line;
    getline(cin, line);

    string cleaned = convert_str_lower(line);

    // trim
    while (!cleaned.empty() && isspace(cleaned.front())) cleaned.erase(cleaned.begin());
    while (!cleaned.empty() && isspace(cleaned.back())) cleaned.pop_back();

    // validate: must match exactly
    bool valid = false;
    for (int j = 0; j < valid_cities.size(); j++) {
        if (cleaned == valid_cities[j]) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        cout << "Invalid city. Please enter ONLY: SAMARKAND, TASHKENT, BUKHARA.\n";
        i--;
        continue;
    }

    // prevent duplicates only across different inputs
    // example: user chose samarkand earlier in a different STEP
    bool already_chosen = false;
    for (string &c : user_cities) {
        if (c == cleaned) {
            already_chosen = true;
            break;
        }
    }

    if (already_chosen) {
        cout << "You already selected this city earlier. Choose a different one.\n";
        i--;
        continue;
    }

    user_cities.push_back(cleaned);
}
    cout << "Enter your preferred categories (comma separated like: cultural, walk, culinary): ";
    getline(cin, user_preferences);
    
    vector<string> user_prefs_list = split_string(user_preferences, ',');
    for(int i=0;i<user_prefs_list.size();i++){
        string s=user_prefs_list[i];
        // trim spaces
        while(!s.empty() && isspace(s[0])) s.erase(0,1);
        while(!s.empty() && isspace(s[s.size()-1])) s.erase(s.size()-1,1);
        user_prefs_list[i]=s;
    }

    cout << "Enter your budget in $: ";
    getline(cin, budget_input);
    budget = stof(budget_input);

    vector<activity*> city_filtered = filter_by_city(activities, user_cities);
    vector<final_list_filtered_activities> prefiltered = filter_by_preference(city_filtered, user_prefs_list);

    suggestions(prefiltered, budget);
    cout << final_message;

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}
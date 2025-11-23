#include "functions.h"
#include <iostream>
#include <cctype>

using namespace std;

/* 
Function name: convert_str_lower
- converts string s to all lowercase to ensure proper comparison
*/

string convert_str_lower(string s){
    for (int i = 0; i < s.size(); i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

/*
Function name: str_inside_str
- checks if a smaller string (part) exists inside a bigger string (full)
- parameters: full (string to search), part (substring to find)
- returns: true if part is found in full, case-insensitive
Example: typing 'photo' instead of 'photography'
*/
bool str_inside_str(string full, string part){
    full = convert_str_lower(full);
    part = convert_str_lower(part);

    if (part.size() == 0) return true;
    if (full.size() < part.size()) return false;

    for (int i = 0; i <= full.size() - part.size(); i++){
        bool match = true;
        for (int j = 0; j < part.size(); j++){
            if (full[i + j] != part[j]){
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

/* 
Function name: split_string
- splits a string into pieces using a separator character
- parameters: input (string to split), separation (char used to split)
- returns: vector of strings, each one a part of the original string
*/
vector<string> split_string(const string& input, char separation){
    vector<string> result;
    string current;
    for (int i = 0; i < input.size(); i++){
        if (input[i] == separation){
            if (current.size() > 0){
                result.push_back(current);
                current = "";
            }
        } else {
            current += input[i];
        }
    }
    if (current.size() > 0) result.push_back(current);
    return result;
}


/* 
Function name: activity_match
- checks if a single activity category matches a single user preference
- parameters: categories (activity's categories), u_preferences (a single preference string)
- returns: true if the activity contains that preference
*/
bool activity_match(const vector<string>& categories, const string& u_preferences){
    for (int i = 0; i < categories.size(); i++){
        if (str_inside_str(categories[i], u_preferences)) return true;
    }
    return false;
}

/* 
Function name: perfect_activity
- checks if an activity perfectly matches all user preferences
- parameters: categories (activity categories), u_preferences (user preference list)
- returns: true if all user preferences are matched
*/
bool perfect_activity(const vector<string>& categories, const vector<string>& u_preferences){
    for (int i = 0; i < u_preferences.size(); i++){
        if (!activity_match(categories, u_preferences[i])) return false;
    }
    return true;
}


/* 
Function name: good_activity
- checks if an activity matches at least one of the user's preferences
- parameters: categories (activity categories), u_preferences (user preference list)
- returns: true if any preference is matched
*/
bool good_activity(const vector<string>& categories, const vector<string>& u_preferences){
    for (int i = 0; i < u_preferences.size(); i++){
        if (activity_match(categories, u_preferences[i])) return true;
    }
    return false;
}


/*
Function name: filter_by_city
- filters all activities and returns only those in the cities the user chose
- parameters: all_activities (list of all activities), u_cities (user-selected cities)
- returns: vector of pointers to activities in those cities
*/
vector<activity*> filter_by_city(vector<activity>& all_activities, const vector<string>& u_cities){
    vector<activity*> matching;
    for (int i = 0; i < all_activities.size(); i++){
        string c = convert_str_lower(all_activities[i].city);
        for (int j = 0; j < u_cities.size(); j++){
            if (c == u_cities[j]){
                matching.push_back(&all_activities[i]);
                break;
            }
        }
    }
    return matching;
}


/* 
Function name: filter_by_preference
- filters activities based on user preferences and marks them as perfect/good
- parameters: activities_to_check (vector of activity pointers), u_preferences (vector of user's preference strings)
- returns: vector of final_list_filtered_activities with perfect/good flags
*/
vector<final_list_filtered_activities> filter_by_preference(vector<activity*>& activities_to_check, const vector<string>& u_preferences){
    vector<final_list_filtered_activities> result;
    for (int i = 0; i < activities_to_check.size(); i++){
        bool is_perfect = perfect_activity(activities_to_check[i]->category, u_preferences);
        bool is_good = good_activity(activities_to_check[i]->category, u_preferences);
        result.push_back({activities_to_check[i], is_perfect, is_good});
    }
    return result;
}

/* 
Function name: display
- prints the details of a single activity nicely
- parameters: activity reference
- prints: name, city, price, duration, description
*/
void display(const activity& activity){
    cout << "----------------------------------------------------------------\n";
    cout << activity.name << " (" << activity.city << ")\n";
    cout << "Price: " << activity.s_price << endl;
    cout << "Duration: " << activity.duration_hours << " hours\n";
    cout << activity.description << endl;
}


/* 
Function name: suggestions
ALL THE FINAL DISPLAYS!
- prints activity suggestions in order of perfect matches first, then good-but-not-perfect
- parameters: filtered (vector of final_list_filtered_activities), budget (user's budget)
- prints: suggestion headers and activities if within budget
- calculates: total price of perfect and good activities separately
*/
void suggestions(const vector<final_list_filtered_activities>& filtered, float budget){
    float total = 0; // total including all suggestions
    float perfect_total = 0; // total for perfect suggestions only
    bool any_suggested = false;


    bool has_perfect = false;
    for (int i = 0; i < filtered.size(); i++){
        if (filtered[i].perfect && filtered[i].act->price <= budget){
            has_perfect = true;
            break;
        }
    }

    if (has_perfect){
        cout << "\nHERE ARE SUGGESTIONS THAT COMPLETELY MATCH YOUR PREFERENCES:\n";
        for (int i = 0; i < filtered.size(); i++){
            if (filtered[i].perfect && filtered[i].act->price <= budget){
                display(*filtered[i].act);
                total += filtered[i].act->price;
                perfect_total += filtered[i].act->price; // record perfect total separately
                any_suggested = true;
            }
        }
    }


    bool has_good = false;
    for (int i = 0; i < filtered.size(); i++){
        if (!filtered[i].perfect && filtered[i].good && total + filtered[i].act->price <= budget){
            has_good = true;
            break;
        }
    }

    if (has_good){
        cout << "\nHERE ARE SOME ADDITIONAL SUGGESTIONS THAT YOU MAY WANT TO CONSIDER:\n";
        for (int i = 0; i < filtered.size(); i++){
            if (!filtered[i].perfect && filtered[i].good && total + filtered[i].act->price <= budget){
                display(*filtered[i].act);
                total += filtered[i].act->price; // total now includes good suggestions
                any_suggested = true;
            }
        }
    }


    if (!any_suggested){
        cout << "\nNo activities matched your preferences within budget.\n";
        for (int i = 0; i < filtered.size(); i++){
            if (filtered[i].act->price == 0){
                display(*filtered[i].act);
            }
        }
        cout << "Consider increasing your budget.\n";
    }

    if (any_suggested){
        cout << "\nTOTAL PRICE OF PERFECT ACTIVITIES: " << perfect_total << endl;
        cout << "TOTAL PRICE INCLUDING GOOD ACTIVITIES: " << total << endl;
    }
}
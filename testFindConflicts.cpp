#include <iostream>
#include "FindConflicts.h"

int main()
{
    //Main function to test FindConflicts.cpp
    vector <string> course_list = {"ENGEC327", "ENGEC311", "ENGEC330", "CASMA226","CASPY212"};
    vector <string> names = {"Densmore", "Joshi", "Moreshet", "Lin", "Butler"};
    vector <double> ratings = {4.5, 4.3, 3.8, 4.0, 4.3};
    vector <int> start_times = {230, 1220, 900, 1010, 930};
    vector <int> end_times = {415, 205, 1045, 1100, 1100};
    vector <vector<char>> days = {{'M', 'W'}, {'T', 'R'}, {'T', 'R'}, {'M', 'W', 'F'}, {'T', 'R'}};

    Professor Prof1(course_list.at(0), names.at(0), ratings.at(0), start_times.at(0), end_times.at(0), days.at(0));
    Professor Prof2(course_list.at(1), names.at(1), ratings.at(1), start_times.at(1), end_times.at(1), days.at(1));
    Professor Prof3(course_list.at(2), names.at(2), ratings.at(2), start_times.at(2), end_times.at(2), days.at(2));
    Professor Prof4(course_list.at(3), names.at(3), ratings.at(3), start_times.at(3), end_times.at(3), days.at(3));
    Professor Prof5(course_list.at(4), names.at(4), ratings.at(4), start_times.at(4), end_times.at(4), days.at(4));

    Professor* ptr1 = &Prof1;
    Professor* ptr2 = &Prof2;
    Professor* ptr3 = &Prof3;
    Professor* ptr4 = &Prof4;
    Professor* ptr5 = &Prof5;

    vector <Professor*> prof_ptrs = {ptr1, ptr2, ptr3, ptr4, ptr5};
    vector <vector<Professor*>> sameDay_ptrs = getSameDay(prof_ptrs);

    for (vector <vector<Professor*>> :: iterator it = sameDay_ptrs.begin(); it != sameDay_ptrs.end(); it++)
    {
        cout << "professors on same day: " << endl;
        for (vector <Professor*> :: iterator it2 = (*it).begin(); it2!=(*it).end(); it2++)
        {
            cout << (*it2)->getName() << endl;
        }
    }
    return 0;

}
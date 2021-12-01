#ifndef FINDCONFLICTS_H
#define FINDCONFLICTS_H

#include "Professor.h"
#include <algorithm>

vector <vector<Professor*>> getSameDay(vector <Professor*> prof_ptrs); //finds classes happening on the same day
bool hasTimeConflicts(vector <Professor*> prof_ptrs); //finds time conflicts between classes happening on the same day
bool isStartAfterStart(int startTime1, int startTime2); //takes two start times as arguments and checks if the first happens after the second
bool isStartBeforeEnd(int startTime, int endTime); //takes a start time and an end time as arguments and checks if the start time happens before the end time

#endif
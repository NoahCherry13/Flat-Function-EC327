#ifndef FINDCONFLICTS_H
#define FINDCONFLICTS_H
#include "Professor.h"
#include <algorithm>

vector <vector<Professor*>> getSameDay(vector <Professor*> prof_ptrs); //finds classes happening on the same day
bool hasTimeConflicts(vector <Professor*> prof_ptrs); //finds time conflicts between classes happening on the same day

#endif
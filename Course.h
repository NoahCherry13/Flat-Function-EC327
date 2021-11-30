#ifndef COURSE_H
#define COURSE_H

#include "Professor.h"

struct loop_calc
{
	int loop_helper;
	bool did_it_loop;
};
class Course
{
public:
	vector <double> CalcAverages(vector <vector<Professor*>> clist);
	vector <Professor*> MakeCombination(vector <int> ids, vector <vector <Professor*>> clist, int clist_size);
};

#endif


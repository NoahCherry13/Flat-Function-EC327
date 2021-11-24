#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Professor
{
private:
	string course_id;
	string name;
	double rating;
	int start_time;
	int end_time;
	vector <char> day_taught;
public:
	Professor();
	Professor(string c_id, string name, double rating, int start_time, int end_time, vector <char> days);
	void AddNode(string c_id, int course_id_num, string name, double rating, int start_time, int end_time, vector <char> days, vector <Professor*> &list);
	void Display();
};

#endif


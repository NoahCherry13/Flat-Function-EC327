#include "Professor.h"

Professor::Professor()
{
	course_id = "";
	name = "";
	rating = 0.0;
	start_time = 0;
	end_time = 0;
}

Professor::Professor(string c_id, string name, double rating, int start_time, int end_time, vector<char> days)
{
	course_id = c_id;
	this->name = name;
	this->rating = rating;
	this->start_time = start_time;
	this->end_time = end_time;
	day_taught = days;
}

void Professor::AddNode(string c_id, int course_id_num, string name, double rating, int start_time, int end_time, vector<char> days, vector <Professor*> &list)
{
	Professor *next = new Professor(c_id, name, rating, start_time, end_time, days);
	list.push_back(next);
}

void Professor::Display()
{
	cout << "Course Name: " << course_id << endl;
	cout << "Prof Name: " << name << endl;
	cout << "Rating: " << rating << endl;
	cout << "Start Time: " << start_time << endl;
	cout << "End Time: " << end_time << endl;
	cout << "Days: ";
	for (char i : day_taught)
	{
		cout << i << " ";
	}
	cout << endl;
	cout << "\n";
}

double Professor::GetRating()
{
	return rating;
}


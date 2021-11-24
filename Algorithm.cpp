//Use a greedy algorithm to traverse the csv files from the web scraper
// 1) CSV file read from the output of web scraper
// 2) Store the info in the member variable into the object variables
// 3) Traverse using probably a binary tree algorith or doubly linked list 

#include "Professor.h"
#include "FileIn.h"
#include "Course.h"
#include <algorithm>
#include <cmath>

int main()
{
	Professor prof;
	vector <vector<Professor*>> courseslist;

	//test cases
	vector <string> course_id = {"ENGEC327", "ENGEC327" ,"ENGEC327" , "CASMA226", "CASMA226" , "ENGEK307", "ENGEK307" , "ENGEK307" };
	vector <string> prof_name = { "Densmore", "Guiles", "Noah", "Lin", "Weinstein","Mass", "Pavi", "Pranet"};
	vector <double> rating = {4.5,3.3,2.3,4.6,3.3,4.3,3.2,3.0};
	vector <int> class_start_time = {1200,1321,980,1200,1101,980,1200,1234};
	vector <int> class_end_time = {1920, 1101, 1245, 1345, 1321, 1245, 1343, 1321};
	vector <vector<char>> days_in_file = { {'M','W'}, { 'M','W','F'} , { 'T','R' } , { 'M','W' } ,{ 'M','W','F' }, { 'T','R' }, { 'M','W','F' }, { 'T','R' } };

	int size = course_id.size();

	vector <string> cid_copy = course_id;
	sort(cid_copy.begin(), cid_copy.end());
	cid_copy.erase(unique(cid_copy.begin(), cid_copy.end()), cid_copy.end());
	int uniqueCourse = cid_copy.size();

	for (int i = 0; i < uniqueCourse; i++)
	{
		vector <Professor*> prof_temp;
		for (int j = 0; j < size; j++)
		{
			if (cid_copy[i] == course_id[j])
			{
				prof.AddNode(course_id[j], i, prof_name[j], rating[j], class_start_time[i], class_end_time[j], days_in_file[1], prof_temp);
			}
		}
		courseslist.push_back(prof_temp);
	}

	for (vector<Professor*> p : courseslist)
	{
		for (Professor* p_1 : p)
		{
			p_1->Display();
		}
		cout << "\n" << endl;
	}

	return 0;
}
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
	vector <string> prof_name = { "Densmore", "Guiles", "Hornet", "Lin", "Weinstein","Mass", "Pavi", "Pranet"};
	vector <double> rating = {4.5,3.3,2.3,4.6,3.3,2.3,4.6,3.0};
	vector <int> class_start_time = {1200,1101,980,1200,1101,980,1200,1234};
	vector <int> class_end_time = {1920, 1321, 1245, 1345, 1321, 1245, 1343, 1321};
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

	/*Professor* p1 = new Professor();
	p1->SetProfInfo("ENGEC327", "Densmore", 4.2, 1200, 0010, { 'M', 'W' });
	Professor* p2 = new Professor();
	p2->SetProfInfo("CASMA223", "Weinstein", 3.2, 1000, 2010, { 'M', 'W', 'F'});
	Professor* p3 = new Professor();
	p3->SetProfInfo("ENGEK307", "Semeter", 3.8, 1500, 1720, { 'T', 'R' });
	Professor* p4 = new Professor();
	p4->SetProfInfo("CASPY212", "Li", 2.2, 1230, 1010, { 'M', 'W' });*/
	/*course.push_back(p1);
	course.push_back(p2);
	course.push_back(p3);
	course.push_back(p4);
	Professor* head = nullptr;*/

	/*prof.AddNode("ENGEC327", 1, "Densmore", 4.6, 1200, 920, {'M','W'}, courseslist);
	prof.AddNode("ENGEC327", 1, "Guiles", 3.3, 1101, 1321, { 'M','W','F'}, courseslist);
	prof.AddNode("ENGEC327", 1, "Hornet", 2.3, 980, 1245, { 'T','R' }, courseslist);
	prof.AddNode("CASMA223", 2, "Lin", 4.6, 1200, 920, { 'M','W' }, courseslist);
	prof.AddNode("CASMA223", 2, "Weinstein", 3.3, 1101, 1321, { 'M','W','F' }, courseslist);
	prof.AddNode("CASMA223", 2, "Mass", 2.3, 980, 1245, { 'T','R' }, courseslist);
	prof.AddNode("ENGEC307", 3, "Pavi", 4.6, 1200, 920, { 'M','W' }, courseslist);
	prof.AddNode("ENGEC307", 3, "Pranet", 3.3, 1101, 1321, { 'M','W','F' }, courseslist);*/

	/*for (vector<Professor*> p : courseslist)
	{
		for (Professor* p_1 : p)
		{
			p_1->Display();
		}
	}*/

	return 0;
}
//Use a greedy algorithm to traverse the csv files from the web scraper
// 1) CSV file read from the output of web scraper
// 2) Store the info in the member variable into the object variables
// 3) Traverse using probably a binary tree algorith or doubly linked list 

#include "Professor.h"
#include "FileIn.h"
#include "Course.h"

int main()
{
	Professor prof;
	Course course;
	vector <vector<Professor*>> courseslist;
	FileIn inputFile;
	string fileName = "testFile.csv";
	inputFile.ReadFromFile(fileName);
	//test cases
	vector <string> course_id = inputFile.getCourseId();/*{"ENGEC327", "ENGEC327" ,"ENGEC327" ,
								 "CASMA226", "CASMA226" ,
								 "ENGEK307", "ENGEK307" , "ENGEK307" ,
								 "CASPY212", "CASPY212"};*/
	cout << "Course ID's: " << endl;
	/*for (string str : course_id)
	{
		cout << str << ", " << endl;
	}*/
	vector <string> prof_name = inputFile.getName();/*{ "Densmore", "Guiles", "Noah",
								  "Lin", "Weinstein",
								  "Mass", "Pavi", "Pranet",
								  "Aya", "Nashwa"};*/
	cout << "Names: " << endl;
	/*for (string name : prof_name)
	{
		cout << name << ", " << endl;
	}*/
	vector <double> rating = inputFile.getRating();/*{4.5,3.3,2.3,
							  4.6,3.3,
							  4.3,3.2,3.0,
							  4.1, 2.9};*/
	cout << "Course ID's: " << endl;
	/*for (double str : rating)
	{
		cout << str << ", " << endl;
	}*/
	vector <int> class_start_time = inputFile.getStartTime(); /*{1200,1321,980,
									 1200,1101,
									 980,1200,1234,
									 1230,1100};*/
	/*for (int str : class_start_time)
	{
		cout << str << ", " << endl;
	}*/
	vector <int> class_end_time = inputFile.getEndTime();/*{1920, 1101, 1245,
								   1345, 1321,
								   1245, 1343, 1321,
								   1430,1212};*/
	//for (double str : class_end_time)
	//{
	//	cout << str << ", " << endl;
	//}
	vector <vector<char>> days_in_file = inputFile.getDays();/*{ {'M','W'}, { 'M','W','F'} , { 'T','R' } ,
										   { 'M','W' } ,{ 'M','W','F' },
										   { 'T','R' }, { 'M','W','F' }, { 'T','R' },
										   {'M'}, {'T', 'R'} };*/
	/*for (vector <char> str : days_in_file)
	{
		for(char str: str)
		cout << str << ", " << endl;
		cout << endl;
	}*/

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

	vector <double> avg;
	avg = course.CalcAverages(courseslist);

	for (double p_1 : avg)
	{
		cout << p_1 << " ";
	}
	return 0;
}
#ifndef FILEIN_H
#define FILEIN_H

// Class will read from the csv file

#include <string>
#include <fstream>
#include <vector>
#include <utility> 
#include <stdexcept> 
#include <sstream>
#include <vector>
using namespace std;

class FileIn
{
private: 
	vector <string> course_id;       //stores the course name
	vector <string> prof_name;		 //stores the professor name
	vector <double> rating;			 //stores the rating
	vector <int> class_start_time;	 //stores the start time in 24 hour format
	vector <int> class_end_time;	 //stores end time in 24 hr format
	vector <string> days_in_file;	 //stores the character array of the class days 
	vector <char> days;				 //stores in each element the days of each class 
public:
	void ReadFromFile(string filename);

};

#endif


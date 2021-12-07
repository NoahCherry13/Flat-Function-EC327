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
	//all vectors should be same length
	vector <string> course_id;       //stores the course name
	vector <string> prof_name;		 //stores the professor name
	vector <double> rating;			 //stores the rating
	vector <int> class_start_time;	 //stores the start time in 24 hour format
	vector <int> class_end_time;	 //stores end time in 24 hr format
	vector <vector<char>> days_in_file;		 //stores the character array of the class days for each prof
public:
	void ReadFromFile(string filename);
	//getters to return the needed variable 
	vector <string> getCourseId();
	vector <string> getName();
	vector <double> getRating();
	vector <int> getStartTime();
	vector <int> getEndTime();
	vector <vector<char>> getDays();
	int getSize();

};

#endif



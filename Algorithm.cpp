//Use a looping algorithm to traverse the csv files from the web scraper
// 1) CSV file read from the output of web scraper
// 2) Store the info in the member variable into the object variables
// 3) Traverse using a vector of vectors 

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

	vector <string> course_id = inputFile.getCourseId();
	vector <string> prof_name = inputFile.getName();
	vector <double> rating = inputFile.getRating();
	vector <int> class_start_time = inputFile.getStartTime(); 
	vector <int> class_end_time = inputFile.getEndTime();
	vector <vector<char>> days_in_file = inputFile.getDays();

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
				prof.AddNode(course_id[j], i, prof_name[j], rating[j], class_start_time[j], class_end_time[j], days_in_file[j], prof_temp);
			}
		}
		courseslist.push_back(prof_temp);
	}

	vector <rating_prof> list_of_best;
	vector <double> avg_rating;
	list_of_best = course.CalcAverages(courseslist);

	for (rating_prof p_1 : list_of_best)
	{
		avg_rating.push_back(p_1.average_rating);
	}

	double maximum_average =  *max_element(avg_rating.begin(), avg_rating.end());
	int index_of_max = 0;

	for (int i = 0; i < avg_rating.size(); i++)
	{
		if (maximum_average == avg_rating[i])
		{
			index_of_max = i;
		}
	}

	cout << "BEST POSSIBLE SCHEDULE" << endl;
	cout << "With an average professor rating of: " << list_of_best[index_of_max].average_rating << endl;
	cout << "The Classes are: " << endl;
	for (Professor* professors : list_of_best[index_of_max].profs)
	{
		professors->Display();
	}

	return 0;
}
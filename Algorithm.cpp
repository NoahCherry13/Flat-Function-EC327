//Use a looping algorithm to traverse the csv files from the web scraper
// 1) CSV file read from the output of web scraper
// 2) Store the info in the member variable into the object variables
// 3) Traverse using a vector of vectors 

#include "Professor.h"
#include "FileIn.h"
#include "Course.h"

bool compareByRating(const rating_prof &i, const rating_prof &j)
{
	return i.average_rating > j.average_rating;
}

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
	list_of_best = course.CalcAverages(courseslist);

	sort(list_of_best.begin(), list_of_best.end(), compareByRating);

	cout << "BEST POSSIBLE SCHEDULE" << endl;
	cout << "With an average professor rating of: " << list_of_best[0].average_rating << endl;
	cout << "The Classes are: " << endl;
	for (Professor* professors : list_of_best[0].profs)
	{
		professors->Display();
	}
	
	cout << "_______________________________________________________" << endl;

	char choice;
	int count_best = 1;
	cout << "Do You Wish To See The Next Best Schedule? (Y/Any other character)" << endl;
	cin >> choice;

	while (choice == 'Y')
	{
		cout << "At Position - " << (count_best + 1) << " ,the rating is " << list_of_best[count_best].average_rating << endl;
		for (Professor* professors : list_of_best[count_best].profs)
		{
			professors->Display();
		}
		cout << "_______________________________________________________" << endl;
		count_best++;
		if (count_best <= list_of_best.size())
		{
			cout << "Do You Wish To See The Next Best Schedule? (Y/N)" << endl;
			cin >> choice;
		}
		else
			break;
	}
	

}
#include <iostream>
#include "FileIn.h"
using namespace std;

void FileIn :: ReadFromFile(string filename)
{
    //declaring string variables to read into from the file
    ifstream inFile;
    string id;
    string name;
    string profRating;
    string startTime;
    string endTime;
    string days;
    inFile.open(filename);
    if(!inFile.is_open())
    {
        cout << "File could not be opened. " << endl;
    }
    else
    {
        while(getline(inFile, id, ','))
        {
            getline(inFile, name, ',');
            getline(inFile, profRating, ',');
            getline(inFile, startTime, ',');
            getline(inFile, endTime, ',');
            getline(inFile, days, '\n');

            course_id.push_back(id);
            prof_name.push_back(name);
            rating.push_back(stod(profRating));
            class_start_time.push_back(stoi(startTime));
            class_end_time.push_back(stoi(endTime));
            vector<char> daysVec(days.begin(), days.end());
            days_in_file.push_back(daysVec);
        }
        inFile.close();
    }
}

vector <string> FileIn :: getCourseId()
{
    return course_id;
}

vector <string> FileIn :: getName()
{
    return prof_name;
}

vector <double> FileIn :: getRating()
{
    return rating;
}

vector <int> FileIn :: getStartTime()
{
    return class_start_time;
}

vector <int> FileIn :: getEndTime()
{
    return class_end_time;
}

vector <vector<char>> FileIn :: getDays()
{
    return days_in_file;
}

int FileIn :: getSize()
{
    return course_id.size(); //because all vectors have the same size
}

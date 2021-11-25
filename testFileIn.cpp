#include <iostream>
#include "FileIn.h"
using namespace std;

int main()
{
    string filename = "testFile.csv";
    FileIn myFile;
    myFile.ReadFromFile(filename);
    for (int i = 0; i < myFile.getSize(); i++)
    {
        cout << "Class " << i+1 << ": " << endl;
        cout << "       Course ID: " << myFile.getCourseId().at(i) << endl;
        cout << "       Professor Name: " << myFile.getName().at(i) << endl;
        cout << "       Rating: " << myFile.getRating().at(i) << endl;
        cout << "       Class start time: " << myFile.getStartTime().at(i) << endl;
        cout << "       Class end time: " << myFile.getEndTime().at(i) << endl;
        cout << "       Days: ";
        for (int j = 0; j < myFile.getDays().at(i).size(); j++)
        {
            cout << myFile.getDays().at(i).at(j);
        }
        cout << endl;
    }
    return 0;
}
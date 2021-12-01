#include <iostream>
#include "FindConflicts.h"
using namespace std;

vector <vector<Professor*>> getSameDay(vector <Professor*> prof_ptrs)
{
    //for (Professor* p : prof_ptrs)
    //{
    //    p->Display();
    //}
    //This function finds the professors teaching on the same day to narrow down the classes causing potential time conflicts
    vector <vector<Professor*>> sameDay_ptrs; //each element of this vector is a vector of professors teaching on the same day
    int index = 0;
    for (vector <Professor*> ::iterator it = prof_ptrs.begin(); it != prof_ptrs.end(); it++)
    {
        int count = 0;
        if (it != prof_ptrs.end())
        {
            for (vector <Professor*> ::iterator itNext = next(it, 1); itNext != prof_ptrs.end(); itNext++)
            {
                bool isSameDay = false;
                bool doesExist = false;
                for (int i = 0; i < ((*it)->getDay()).size(); i++)
                {
                    for (int j = 0; j < (*itNext)->getDay().size(); j++)
                    {
                        if ((*it)->getDay().at(i) == (*itNext)->getDay().at(j))
                        {
                            isSameDay = true;
                        }
                    }
                }
                if (isSameDay)
                {
                    count++;
                    if (!sameDay_ptrs.empty())
                    {
                        for (vector <vector<Professor*>> ::iterator iter = sameDay_ptrs.begin(); iter != sameDay_ptrs.end(); iter++)
                        {
                            if ((find((*iter).begin(), (*iter).end(), (*it)) != (*iter).end()) && (find((*iter).begin(), (*iter).end(), (*itNext)) != (*iter).end())) //checks that the two professors are not already in a vector
                            {
                                doesExist = true;
                            }
                        }
                        if (!doesExist)
                        {
                            sameDay_ptrs.resize(index + 1);
                            if (count == 1)
                            {
                                sameDay_ptrs.at(index).push_back(*it);
                            }
                            sameDay_ptrs.at(index).push_back(*itNext);
                        }
                    }
                    else
                    {
                        sameDay_ptrs.resize(index + 1);
                        if (count == 1)
                        {
                            sameDay_ptrs.at(index).push_back(*it);
                        }
                        sameDay_ptrs.at(index).push_back(*itNext);
                    }
                }
            }
            index++;
        }
    }
    return sameDay_ptrs;
}


bool isStartAfterStart(int startTime1, int startTime2)
{
    //takes two start times as arguments and returns true if the first happens after the second
    int hour1 = startTime1 / 100;
    int hour2 = startTime2 / 100;
    //given that classes are in 24 hour format

    if (hour1 > hour2)
    {
        return true;
    }
    else if (hour1 < hour2)
    {
        return false;
    }
    else
    {
        int min1 = startTime1 % 100;
        int min2 = startTime2 % 100;
        if (min1 >= min2)
        {
            return true; //also return true if time is the same (because it will create a time conflict)
        }
        else
        {
            return false;
        }
    }
}
bool isStartBeforeEnd(int startTime, int endTime)
{
    int hourStart = startTime / 100;
    int hourEnd = endTime / 100;
    if (hourStart < hourEnd)
    {
        return true;
    }
    else if (hourStart > hourEnd)
    {
        return false;
    }
    else
    {
        int minStart = startTime % 100;
        int minEnd = endTime % 100;
        if (minStart <= minEnd)
        {
            return true; //also return true if time is the same (because it will create time conflicts)
        }
        else
        {
            return false;
        }
    }
}

bool hasTimeConflicts(vector <Professor*> prof_ptrs)
{
    //this function checks whether or not the classes being taught on the same day create time conflicts
    vector <vector<Professor*>> sameDay_prof_ptrs = getSameDay(prof_ptrs);
    for (vector <vector<Professor*>> ::iterator it = sameDay_prof_ptrs.begin(); it != sameDay_prof_ptrs.end(); it++)
    {
        if (!(*it).empty())
        {
            for (vector <Professor*> ::iterator itDay = (*it).begin(); itDay != (*it).end(); itDay++)
            {
                if (itDay != (*it).end())
                {
                    for (vector <Professor*> ::iterator itNext = next(itDay, 1); itNext != (*it).end(); itNext++)
                    {
                        if (isStartAfterStart((*itDay)->getStartTime(), (*itNext)->getStartTime()) && isStartBeforeEnd((*itDay)->getStartTime(), (*itNext)->getEndTime()))
                        {
                            return true;
                        }
                        else if (isStartAfterStart((*itNext)->getStartTime(), (*itDay)->getStartTime()) && isStartBeforeEnd((*itNext)->getStartTime(), (*itDay)->getEndTime()))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
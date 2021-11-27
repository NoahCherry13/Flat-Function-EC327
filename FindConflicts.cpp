#include <iostream>
#include "FindConflicts.h"
using namespace std;

vector <vector<Professor*>> getSameDay(vector <Professor*> prof_ptrs)
{
    //This function finds the professors teaching on the same day to narrow down the classes causing potential time conflicts
    vector <vector<Professor*>> sameDay_ptrs; //each element of this vector is a vector of professors teaching on the same day
    int index = 0;
    for(vector <Professor*> :: iterator it = prof_ptrs.begin(); it != prof_ptrs.end(); it++) 
    {
        int count = 0;
        if(it != prof_ptrs.end())
        {
            for (vector <Professor*> :: iterator itNext = next(it, 1); itNext != prof_ptrs.end(); itNext++) 
            {
                bool isSameDay = false;
                bool doesExist = false;
                for (int i = 0; i < (*it)->getDay().size(); i++)
                {
                    for (int j = 0; j < (*itNext)->getDay().size(); j++)
                    {
                        if((*it)->getDay().at(i) == (*itNext)->getDay().at(j))
                        {
                            isSameDay = true;
                        }
                    }
                }
                if (isSameDay)
                {
                    count ++;
                    if(it != prof_ptrs.begin())
                    {
                        vector <Professor*> :: iterator itPrev = prev(it, 1);
                        for(vector <vector<Professor*>> :: iterator iter = sameDay_ptrs.begin(); iter != sameDay_ptrs.end(); iter++)
                        {
                            if((find((*iter).begin(), (*iter).end(), (*it)) != (*iter).end()) && (find((*iter).begin(), (*iter).end(), (*itNext)) != (*iter).end())) //checks that the two professors are not already in a vector
                            {
                                doesExist = true;
                            }
                        }
                        if (!doesExist) 
                        {
                            sameDay_ptrs.resize(index + 1);
                            if(count == 1)
                            {
                                sameDay_ptrs.at(index).push_back(*it);
                            }
                            sameDay_ptrs.at(index).push_back(*itNext);
                        }
                    }
                    else
                    {
                        sameDay_ptrs.resize(index + 1);
                        if(count == 1)
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

bool hasTimeConflicts(vector <Professor*> prof_ptrs)
{
    //this function checks whether or not the classes being taught on the same day create time conflicts
}


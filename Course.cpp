#include "Course.h"
#include "FindConflicts.h"

vector <double> Course::CalcAverages(vector<vector<Professor*>> clist)
{
	int size_clist = clist.size();
	vector <int> plist_size;
	for (vector<Professor*> plist : clist)
	{
		plist_size.push_back(plist.size() - 1);
	}

	vector <loop_calc> store_count(size_clist, { 0, false });
	double t_rating = 0;
	int test = 1;
	vector <double> average_rating;

	int count = 0;
	while (true)
	{
		if (count == 0)
		{
			count = -1;
		}
		else
		{
			bool ret = true;
			for (int i = 0; i < size_clist; i++)
			{
				if (store_count[i].loop_helper != 0)
				{
					ret = false;
				}
			}
			if (ret)
			{
				return average_rating;
			}
		}
		vector <int> store_combi_ids;
		for (int i = 0; i < size_clist; i++)
		{
			t_rating += clist[i][store_count[i].loop_helper]->getRating();
			store_combi_ids.push_back(store_count[i].loop_helper);
		}
		vector <Professor*> temp_storage = MakeCombination(store_combi_ids, clist, size_clist);

		//print combinations for test
		
		cout << "Combination#" << test <<": " << endl;
		test++;
		for (Professor* p : temp_storage)
		{
			p->Display();
		}
		cout << "__________" << endl;

		//check for time before pushing
		if (!hasTimeConflicts(temp_storage))
		{
			cout << "No time comflict" << endl;
			average_rating.push_back((t_rating / size_clist));
		}

		store_combi_ids.clear();
		temp_storage.clear();

		store_count[size_clist - 1].loop_helper += 1;
		for (int i = size_clist - 1; i >= 0; i--)
		{
			if (store_count[i].loop_helper > plist_size[i] && !store_count[i].did_it_loop)
			{
				store_count[i].did_it_loop = true;
				store_count[i].loop_helper = 0;
				if (store_count[i].did_it_loop && i != 0)
				{
					store_count[i - 1].loop_helper += 1;
					if (store_count[i - 1].loop_helper == plist_size[i - 1])
					{
						store_count[i - 1].did_it_loop = true;
					}
					if (i != size_clist - 1)
						store_count[i].did_it_loop = false;
				}
				if (store_count[i].did_it_loop)
				{
					store_count[i].did_it_loop = false;
				}
			}
			else
				store_count[i].did_it_loop = false;
		}
		t_rating = 0;
	}
	return { 0 };
}

vector <Professor*> Course::MakeCombination(vector<int> ids, vector<vector<Professor*>> clist, int clist_size)
{
	vector <Professor*> ret_combi;
	for (int i = 0; i < clist_size; i++)
	{
		ret_combi.push_back(clist[i][ids[i]]);
	}
	return ret_combi;
}


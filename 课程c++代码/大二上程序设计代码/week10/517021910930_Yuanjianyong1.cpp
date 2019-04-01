#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> buckets;
	string s;
	while (getline(cin,s,','))
	{
		buckets.push_back(stoi(s));
	}
	int water = 0;
	vector<int> indexVector;
	if (!buckets.empty())
	{
		indexVector.push_back(0);
	}
	else
	{
		cout << water;
		return 0;
	}
	for (int i = 1; i < buckets.size(); i++)
	{
		if (buckets[i] <= buckets[indexVector.back()])
		{
			indexVector.push_back(i);
		}
		else
		{
			int j;
			int k;
			while (!indexVector.empty()&&buckets[i]>buckets[indexVector.back()])
			{
				j = indexVector.back();
				indexVector.pop_back();
				if (!indexVector.empty())
					k = indexVector.back();
				else
					break;
				if (buckets[indexVector[0]] >= buckets[i])
					water += (j - k)*(buckets[i] - buckets[j]);
				else
					water += (j - k)*(buckets[indexVector[0]] - buckets[j]);
				
			}
			indexVector.push_back(i);
			
		}
	}
	cout << water;
	return 0;
}
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main()
{
	string s = "";
	vector<int>bucket;
	while (getline(cin, s, ' '))
	{
		bucket.push_back(stoi(s));
	}
	stack<int> left;
	stack<int> right;
	vector<int> final;
	int lefttopindex = 0;
	int righttopindex = bucket.size() - 1;
	int leftMaxIndex = lefttopindex;
	int rightMaxIndex = righttopindex;
	int water = 0;

	left.push(bucket[leftMaxIndex]);
	right.push(bucket[rightMaxIndex]);
	lefttopindex++;
	righttopindex--;

	for (int i = 0; i < bucket.size(); i++)
	{
		if (lefttopindex >= righttopindex)
		{
			if (leftMaxIndex == rightMaxIndex)
				break;//只有一个元素
			int minHigh = min(bucket[leftMaxIndex], bucket[rightMaxIndex]);
			water += (rightMaxIndex - leftMaxIndex - 1)*minHigh;

			for (int j = leftMaxIndex + 1; j < rightMaxIndex; j++)
			{
				int tmp = (bucket[j]) < minHigh ? (bucket[j]) : minHigh;
				water -= tmp;
			}

			if (bucket[leftMaxIndex] > bucket[rightMaxIndex])
			{
				while (!left.empty())
				{
					final.push_back(left.top() > minHigh ? left.top() - minHigh : 0);
					left.pop();
				}
			}
			else if (bucket[leftMaxIndex] < bucket[rightMaxIndex])
			{
				while (!right.empty())
				{
					final.push_back(right.top() > minHigh ? right.top() - minHigh : 0);
					right.pop();
				}
			}

			while (final.size() > 1)
			{
				auto biggest = max_element(final.begin(), final.end() - 1);
				int width = 0;
				for (auto it = biggest + 1; it < final.end() - 1; it++)
				{
					water -= *it;
					width++;
				}
				water += width * (*biggest);
				final.erase(biggest + 1, final.end());
			}
			break;
		}

		if (bucket[lefttopindex] >= bucket[leftMaxIndex])
		{
			water += (left.size() - 1)*(bucket[leftMaxIndex]);
			while (left.size() != 1)
			{
				water -= left.top();
				left.pop();
			}
			left.pop();//清空left

			leftMaxIndex = lefttopindex;
			left.push(bucket[leftMaxIndex]);
		}
		else
		{
			left.push(bucket[lefttopindex]);
		}
		if (bucket[righttopindex] >= bucket[rightMaxIndex])
		{
			water += (right.size() - 1)*(bucket[rightMaxIndex]);
			while (right.size() != 1)
			{
				water -= right.top();
				right.pop();
			}
			right.pop();

			rightMaxIndex = righttopindex;
			right.push(bucket[rightMaxIndex]);
		}
		else
		{
			right.push(bucket[righttopindex]);
		}
		lefttopindex++;
		righttopindex--;
	}
	cout << water << endl;
	system("pause");
	
	return 0;
}
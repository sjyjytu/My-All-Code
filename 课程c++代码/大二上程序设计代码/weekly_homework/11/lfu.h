#include <iostream>
#include <list>
#include <utility>
#include <unordered_map>

using namespace std;

class LFUCache
{
public:
	struct unit
	{
		int value;
		list<pair<int, list<int>>>::iterator headpair;  //the iterator of head
		list<int>::iterator elekey;  //the iterator of elem, which is a key to the unit
	};
	LFUCache(int cap)
	{
		capacity = cap;
	}

	int get(int key)
	{
		auto it = keyUnit.find(key);
		if (it == keyUnit.end())
			return -1;
		visit(it);
		return it->second.value;
	}

	void put(int key, int value)
	{
		if (capacity == 0)
			return;
		auto it = keyUnit.find(key);
		if (it == keyUnit.end())
		{
			//not exit and create it
			if (keyUnit.size() == capacity)
			{
				//full and delete the front front one
				auto it2 = freList.front().second.begin();  //the least one key
				keyUnit.erase(*it2);
				freList.front().second.erase(it2);
				if (freList.front().second.empty())
					freList.pop_front();
			}
			
			if (freList.empty() || freList.front().first > 1)
			{
				//empty or no frequency 1 son list exit, create it
				list<int> newList;
				newList.push_back(key);
				freList.push_front(make_pair(1, newList));
			}
			else
			{
				freList.front().second.push_back(key);  //add new key to the front back
			}
			//update keyUnit
			unit newUnit;
			newUnit.value = value;
			newUnit.headpair = freList.begin();
			newUnit.elekey = prev(freList.front().second.end());
			keyUnit[key] = newUnit;
		}
		else
		{
			it->second.value = value;
			visit(it);
		}
	}
private:
	int capacity;
	unordered_map<int, unit> keyUnit;
	list<pair<int, list<int>>> freList;
	void visit(unordered_map<int,unit>::iterator it)
	{
		//move the visited unit to the next frequency freList
		int oldFre = it->second.headpair->first;
		int newFre = oldFre + 1;
		int key = *it->second.elekey;
		it->second.headpair->second.erase(it->second.elekey);
		if (it->second.headpair->second.empty())  //remove if this son list is empty
			it->second.headpair = freList.erase(it->second.headpair);
		else
		{
			it->second.headpair++;
		}
		
		if (it->second.headpair == freList.end() || it->second.headpair->first != newFre)
		{
			//the son list of newFre not exit
			list<int> newList;
			//update freList
			newList.push_back(key);
			it->second.headpair = freList.insert(it->second.headpair,make_pair(newFre, newList));
		}
		else
		{
			it->second.headpair->second.push_back(key);
		}

		//update keyUnit
		it->second.elekey = prev(it->second.headpair->second.end());
	}
};

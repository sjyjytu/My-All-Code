#include <iostream>
#include <list>
#include <utility>
#include <unordered_map>

using namespace std;

class LFUCache
{
  public:
	  typedef list<pair<int, int>> elem;
	  struct unit
	  {
		  int frequency;
		  elem::iterator ele;
	  };
    LFUCache(int Capacity)
    {
		capacity = Capacity;
		count = 0;
    }

    int get(int key)
    {
		unordered_map<int, unit>::iterator it = key_unit.find(key);
		if (it != key_unit.end())
		{
			visit(key);
			return it->second.ele->second;
		}
		return -1;
    }

    void put(int key, int value)
    {
		unordered_map<int, unit>::iterator it = key_unit.find(key);
		if (it != key_unit.end())
		{
			//key exits
			it->second.ele->second = value;
			visit(key);
		}
		else
		{
			//not exit
			if (count == 0)
			{
				//empty
				elem *newlist = new elem();
				newlist->push_front(make_pair(key, value));
				lfu_data.push_back(*newlist);
				//update map
				fre_list.insert(make_pair(1, *newlist));
				unit newunit;
				newunit.frequency = 1;
				newunit.ele = newlist->begin();
				key_unit.insert(make_pair(key, newunit));
			}
			else
			{
				elem *leastFrelist = new elem();
				*leastFrelist = lfu_data.back();
				pair<int, int> lastone = leastFrelist->back();
				int leastFre = key_unit.find(lastone.first)->second.frequency;
				if (count >= capacity)
				{
					//full
					leastFrelist->pop_back();  //delete the last one

				}
				if (leastFre == 1)
				{
					leastFrelist->push_front(make_pair(key, value));
					//update map
					fre_list.insert(make_pair(1, *leastFrelist));
					unit newunit;
					newunit.frequency = 1;
					newunit.ele = leastFrelist->begin();
					key_unit.insert(make_pair(key, newunit));
				}
				else
				{
					elem *newlist = new elem();
					newlist->push_front(make_pair(key, value));
					lfu_data.push_back(*newlist);
					//update map
					fre_list.insert(make_pair(1, *newlist));
					unit newunit;
					newunit.frequency = 1;
					newunit.ele = newlist->begin();
					key_unit.insert(make_pair(key, newunit));
				}
			}
			count++;
		}
    }
private:
	int capacity;
	int count;
	list <elem> lfu_data;  //two delema list
	unordered_map<int, unit> key_unit;  //key to unit(frequency and ele_it)
	unordered_map<int, elem> fre_list;//frequency to son list

	void visit(int key)
	{
		unordered_map<int, unit>::iterator unit_it = key_unit.find(key);
		int frequency = unit_it->second.frequency;
		int new_frequency = frequency + 1;
		unit_it->second.frequency = new_frequency;  //update frequency

		unordered_map<int, elem>::iterator curFrelistIt = fre_list.find(frequency);
		unordered_map<int, elem>::iterator nextFrelistIt = fre_list.find(new_frequency);
		
		elem *nextFrelist = new elem();
		if (nextFrelistIt != fre_list.end())
		{
			//next frequency list exits
			*nextFrelist = nextFrelistIt->second;	
		}
		else
		{
			//next frequency list not exit
			//create a new list
			fre_list.insert(make_pair(new_frequency, *nextFrelist));
		}

		//move the cur point from old frequency to the new frequency list
		pair<int, int> curPoint = *unit_it->second.ele;
		curFrelistIt->second.erase(unit_it->second.ele);
		nextFrelist->push_front(curPoint);

		//update the unordered_map
		unit_it->second.ele = nextFrelist->begin();
	}
};

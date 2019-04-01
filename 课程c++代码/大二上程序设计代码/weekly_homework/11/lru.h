#include <iostream>
#include <list>
#include <utility>
#include <unordered_map>

using namespace std;

typedef list<pair<int, int>> lrucache;
class LRUCache
{
  public:
    LRUCache(int Capacity)
    {
		capacity = Capacity;
    }

    int get(int key)
    {
		unordered_map<int, lrucache::iterator>::iterator it = lru_map.find(key);
		if (it != lru_map.end())
		{
			lrucache::iterator cur_element = it->second;
			//put the current visit one to the front of the lru_data
			pair<int,int> tmp = *cur_element;
			lru_data.erase(cur_element);
			lru_data.push_front(tmp);
			//update the lru_map
			lru_map[key] = lru_data.begin();

			return it->second->second;
		}
		return -1;  //not exit
    }

    void put(int key, int value)
    {
		unordered_map<int, lrucache::iterator>::iterator it = lru_map.find(key);
		if (it != lru_map.end())  //exit
		{
			it->second->second = value;

			//change cur's position to the front
			lrucache::iterator cur_element = it->second;
			pair<int, int> tmp = *cur_element;
			lru_data.erase(cur_element);
			lru_data.push_front(tmp);

			//update lru_map
			lru_map[key] = lru_data.begin();
		}
		else
		{
			//not exit
			if (lru_data.size()>=capacity)
			{
				//full and delete the least recently one from unordered_map
				unordered_map<int, lrucache::iterator>::iterator mapdelit;
				mapdelit = lru_map.find(lru_data.back().first);
				lru_map.erase(mapdelit);
				lru_data.pop_back();
			}
			pair<int, int> new_element = make_pair(key, value);
			lru_data.push_front(new_element);
			lru_map[key] = lru_data.begin();
		}
    }

private:
	int capacity;
	lrucache lru_data;  //save the key-value, can erase element in O(1)
	unordered_map<int, lrucache::iterator> lru_map;
	//save key-iterator of data, can find element in O(1)
};

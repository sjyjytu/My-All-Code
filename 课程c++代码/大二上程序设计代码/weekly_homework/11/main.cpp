#include <iostream>
#include "lfu2.h"

using namespace std;

int main()
{
	LFUCache cache = LFUCache(2 /* capacity */);
	
	cache.put(1, 1);
	cache.put(2, 2);
	cout << cache.get(1);       // returns 1
	cache.put(3, 3);    // evicts key 2
	cout << cache.get(2);       // returns -1 (not found)
	cout << cache.get(3);       // returns 3.
	cache.put(4, 4);    // evicts key 1.
	cout << cache.get(1);       // returns -1 (not found)
	cout << cache.get(3);       // returns 3
	cout << cache.get(4);       // returns 4
	

	system("pause");
	return 0;
}
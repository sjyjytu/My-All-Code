#ifndef EXTENDEDLIST3_H
#define EXTENDEDLIST3_H

#include <iostream>
#include <vector>

using namespace std;

template<class T>
class extendedList3
{
public:
	extendedList3(int size);
	~extendedList3();
	bool isFull();
	bool isEmpty();
	bool Add(T x);
	bool Insert(int i, T x);
	bool Delete(int i, T &x);
	void Print();
	int lastIndexOf(const T &x);
	void halfMove();
	void reduceSpace(double percentage = 0.25, double reduceRatio = 0.5);
	T getData(int i);
private:
	vector<T> data;
	int length;
	int maxSize;
};

template<class T>
extendedList3<T>::extendedList3(int size)
{
	maxSize = size;
	length = 0;
}

template<class T>
extendedList3<T>::~extendedList3()
{
}

template<class T>
bool extendedList3<T>::isFull()
{
	if (length == maxSize)
		return true;
	return false;
}

template<class T>
bool extendedList3<T>::isEmpty()
{
	if (length == 0)
		return true;
	return false;
}

template<class T>
bool extendedList3<T>::Add(T x)
{
	if (isFull())	return false;
	data.push_back(x);
	length++;
	return true;
}

template<class T>
bool extendedList3<T>::Insert(int i, T x)
{
	if (isFull()) return false;
	if (i<0 || i>length)
		return false;
	data.insert(i, x);
	length++;
	return true;
}

template<class T>
bool extendedList3<T>::Delete(int i, T &x)
{
	if (isEmpty()) return false;
	if (i<0 || i >= length)
		return false;
	x = data[i];
	data.erase(data.begin()+i);
	length--;
	reduceSpace();
	return true;
}

template<class T>
void extendedList3<T>::Print()
{
	for (int i = 0; i < length; i++)
	{
		cout << i << ":" << data[i] << "  ";
	}
	cout << endl;
}
template<class T>
inline int extendedList3<T>::lastIndexOf(const T & x)
{
	int Index = -1;
	for (int i = 0; i < length; i++)
	{
		if (data[i] == x)
		{
			Index = i;
		}
	}
	return Index;
}
template<class T>
inline void extendedList3<T>::halfMove()
{
	length = (length + 1) / 2;
	for (int i = 0; i < length; i++)
	{
		data[i] = data[2 * i];
	}
}
template<class T>
inline void extendedList3<T>::reduceSpace(double percentage, double reduceRatio)
{
	if (double(length) / maxSize < percentage)
	{
		int newMaxsize = maxSize * (1 - reduceRatio);
		maxSize = newMaxsize;
	}
}
template<class T>
inline T extendedList3<T>::getData(int i)
{
	if (i < 0 || i >= length || isEmpty())
	{
		return NULL;
	}
	return data[i];
}
#endif // !EXTENDEDLIST3_H

/*#include "extendedList.h"

template<class T>
extendedList<T>::extendedList(int size)
{
	maxSize = size;
	length = 0;
	data = new int [maxSize];
	if (data == 0)
	{
		std::cerr << "wrong!!";
		std::exit(1);
	}
}

template<class T>
extendedList<T>::~extendedList()
{
	delete[] data;
}

/*template<class T>
bool extendedList<T>::isFull()
{
	if (length == maxSize)
		return true;
	return false;
}

template<class T>
bool extendedList<T>::isEmpty()
{
	if (length == 0)
		return true;
	return false;
}

template<class T>
bool extendedList<T>::Add(T x)
{
	if (isFull())	return false;
	data[length] = x;
	length++;
	return true;
}

template<class T>
bool extendedList<T>::Insert(int i, T x)
{
	if (isFull()) return false;
	if (i<0 || i>length)
		return false;
	for (int j = length; j > i; j--)
	{
		data[j] = data[j - 1];
	}
	data[i] = x;
	length++;
	return true;
}

template<class T>
bool extendedList<T>::Delete(int i, T &x)
{
	if (isEmpty()) return false;
	if (i<0 || i>=length)
		return false;
	x = data[i];
	for (int j = i; j < length - 1; j++)
	{
		data[j] = data[j + 1];
	}
	length--;
	return true;
}

template<class T>
void extendedList<T>::Print()
{
	for (int i = 0; i < length; i++)
	{
		std::cout << i << ":" << data[i];
	}
	std::cout << endl;
}
*/
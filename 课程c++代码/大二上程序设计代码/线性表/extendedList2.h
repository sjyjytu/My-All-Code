#ifndef EXTENDEDLIST2_H
#define EXTENDEDLIST2_H

#include <iostream>

using namespace std;


template<class T>
class extendedList2
{
public:
	extendedList2(int size);
	~extendedList2();
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
	struct linkNode
	{
		T prev;
		T data;
		linkNode *next;
	};
	linkNode *head;
	linkNode *rear;
	int length;
	int maxSize;
};

#endif // !EXTENDEDLIST2_H

template<class T>
inline extendedList2<T>::extendedList2(int size)
{
	maxSize = size;
	length = 0;
	head = rear = new linkNode;
	if (head == 0||rear == 0)
	{
		cerr << "wrong!!";
		exit(1);
	}
}

template<class T>
inline extendedList2<T>::~extendedList2()
{
	linkNode *p = new linkNode;
	p = head;
	while (p->next != NULL)
	{
		head = p->next;
		delete p;
		p = head;
	}
	delete head;
}

template<class T>
inline bool extendedList2<T>::isFull()
{
	if (length == maxSize)
		return true;
	return false;
}

template<class T>
inline bool extendedList2<T>::isEmpty()
{
	if (length == 0)
		return true;
	return false;
}

template<class T>
inline bool extendedList2<T>::Add(T x)
{
	if (isFull())	return false;
	linkNode *p = new linkNode;
	p->data = x;
	p->next = NULL;
	rear->next = p;
	if (rear != head)
		p->prev = rear->data;
	rear = p;

	length++;
	return true;
}

template<class T>
inline bool extendedList2<T>::Insert(int i, T x)
{
	if (i<0 || i>length || isFull())
		return false;
	linkNode *p = new linkNode;
	linkNode *q = new linkNode;
	p->next = head;
	q->data = x;
	for (int j = 0; j < i; j++)
	{
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	length++;
	
	return true;
}

template<class T>
inline bool extendedList2<T>::Delete(int i, T & x)
{
	if (i<0 || i >= length || isEmpty())
		return false;
	linkNode *p = new linkNode;
	linkNode *q = new linkNode;
	p->next = head;
	for (int j = 0; j < i; j++)
	{
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	x = q->data;
	delete q;
	length--;
	return true;
}

template<class T>
inline void extendedList2<T>::Print()
{
	linkNode *p = new linkNode;
	p = head->next;
	cout << "length:" << length << endl;
	while (p != NULL)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << endl;
}

template<class T>
inline int extendedList2<T>::lastIndexOf(const T & x)
{
	int Index = -1;
	int i = 0;
	linkNode *p = new linkNode;
	p = head;
	while (p != NULL)
	{
		if (p->data == x)
		{
			Index = i;
		}
		i++;
		p = p->next;
	}
	return Index;
}

template<class T>
inline void extendedList2<T>::halfMove()
{
	linkNode *p = new linkNode;
	linkNode *q = new linkNode;
	p = head->next;
	
	while (p != NULL)
	{
		q = p->next;
		if (q != NULL)
		{
			p->next = q->next;
			delete q;
		}
		p = p->next;
	}
	
	length = (length + 1) / 2;
}

template<class T>
inline void extendedList2<T>::reduceSpace(double percentage, double reduceRatio)
{
	if (double(length) / maxSize < percentage)
	{
		int newMaxsize = maxSize * (1 - reduceRatio);
		maxSize = newMaxsize;
	}
}

template<class T>
inline T extendedList2<T>::getData(int i)
{
	if (i < 0 || i >= length || isEmpty())
	{
		return NULL;
	}
	linkNode *p = new linkNode;
	p = head->next;
	for (int j = 0; j < i; j++)
	{
		p = p->next;
	}
	return p->data;
}

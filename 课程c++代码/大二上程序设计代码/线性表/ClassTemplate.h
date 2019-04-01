// ClassTemplate.h
#ifndef ClassTemplate_HH
#define ClassTemplate_HH

template<typename T1, typename T2>

class myClass {

private:
	T1 I;
	T2 J;

public:
	myClass(T1 a, T2 b);//Constructor
	void show();
};


//���ǹ��캯��
//ע����Щ��ʽ

template <typename T1, typename T2>

myClass<T1, T2>::myClass(T1 a, T2 b) :I(a), J(b) {}



//����void show();

template <typename T1, typename T2>

void myClass<T1, T2>::show()
{
	cout << "I=" << I << ", J=" << J << endl;
}
#endif
#include <iostream>

using namespace std;

class CExample
{
	int m_nTest;
public:
	
	CExample(int x):m_nTest(x) //带参数构造函数
	{ 
	   cout << "constructor with argument"<<endl;
	}
	
	CExample(const CExample & ex) //拷贝构造函数
	{
		m_nTest = ex.m_nTest;
		cout << "copy constructor"<<endl;
	}
	
	CExample& operator = (const CExample &ex)//赋值函数(赋值运算符重载)
	{	
		cout << "assignment operator"<<endl;
		m_nTest = ex.m_nTest;
		return *this;
	}
	
	void myTestFunc(CExample ex)
	{
	}
};

int main()
{
	CExample aaa(2);
	CExample bbb(3);
	bbb = aaa;
	CExample ccc = aaa;
	bbb.myTestFunc(aaa);
	
	return 0;	
}


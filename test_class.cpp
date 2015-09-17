#include <stdio.h>
#include <iostream>

using namespace std;

//测试
//1.普通成员可以在构造函数前赋值
//2.只读，引用，带参构造类，只能在初始化列表中初始化
//3.static类成员，在类体外构造(但是没成功)
    class TC {
    public:
        int a=3;
        TC(int _a):a(_a){
            
        }
    };
    class TestClass1{
    public:
        const int cValue=2;
        static int sValue=6;
        static const int scValue=7;
        int a=5;
        int &b=a;
        TC tc;
        TestClass1():tc(9){}
    };
    
//    int TestClass1::sValue=3;
//    const int TestClass1::scValue=4;
    
    int main(){
        TestClass1 tc;
        cout << tc.sValue << ","<< tc.scValue<<endl;
	return 0;
    }

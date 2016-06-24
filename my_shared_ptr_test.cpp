/*************************************************************************
	> File Name: testmySmartPtr<int>.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年05月28日 星期四 13时36分12秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include "mySmartPtr.h"
using namespace std;

class Base             // 定义一个基类
{
public:
    virtual ~Base(){
        cout << "class Base" << endl;
    }
};

class Derived1 : public Base   // 派生类1
{
public:
    ~Derived1(){
        cout << "class Derived1" << endl;
    }
};    

class Derived2 : public Base    // 派生类2
{
public:
    ~Derived2(){
        cout << "class Derived2" << endl;
    }
};

int main()
{   
    int *pi = new int(42);     
    mySmartPtr<int> *hpa(new mySmartPtr<int>(pi));        // 构造函数  
    mySmartPtr<int> *hpb = new mySmartPtr<int>(*hpa);     // 拷贝构造函数  
    mySmartPtr<int>  hpd = *hpa;                          // 拷贝构造函数  
    // 观察引用计数的变化
    cout << hpa->getPtrCounter() << " " << hpb->getPtrCounter() << " "<< hpd.getPtrCounter() << endl;  
    delete hpa;  
    cout << hpd.getPtrCounter() << endl;  
    delete hpb;  
    cout << hpd.getPtrCounter() << endl;
    
    // 观察派生类向基类的隐式转换
    vector<mySmartPtr<Base> > obj;        // 父类指针vector
    obj.push_back(new Derived1);          // 存入子类
    obj.push_back(new Derived2);
    
    vector<mySmartPtr<Base> > obj2;  
    obj2.push_back(obj[0]);
    
    if (obj2[0])
        cout << "Cast Derived1 to Base successd" << endl;
    else
        cout << "Cast Derived1 to Base failed" << endl;
    
    // 观察不同类型的显式转换
    mySmartPtr<Derived1> d1 = new Derived1;
    mySmartPtr<Base> b = d1;              
    mySmartPtr<Derived2> d2 = b.Cast<Derived2>();  
    // d2是空，因为b指向的是Derived1而不是Derived2
    if (d2)
        cout << "Cast Derived1 to Derived2 successd" << endl;
    else
        cout << "Cast Derived1 to Derived2 failed" << endl;

    return 0;
}

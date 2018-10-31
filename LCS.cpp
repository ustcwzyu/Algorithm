#include<iostream>
using namespace std;
class B{
    public:
    B() {
        cout<<"B ";
    }
};
class B1: virtual public B{
    public:
    B1() {
        cout<<"B1 ";
    }
};
class B2: virtual public B{
    public:
    B2() {
        cout<<"B2 ";
    }
};
class B3{
    public:
     B3() {
         cout<<"B3 ";
     }
};
class C:virtual public B3, public B1, public B2{
    public:
     C() {
         cout<<"C ";
     }
};
int main() {
    C obj;
    system("pause");
}
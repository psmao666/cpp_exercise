#include <bits/stdc++.h>
using namespace std;

class A{
public:
    int x;
    int y;
    A(): x(0), y(0) {}
    A(int _, int __): y(_), x(__) {}
    void print() {
        cout << x << ' ' << y << endl;
    }
};
class B : public A {
public:
    B() {}
    void print() {
        cout << x << ' ' << y << endl;
    }

};

int main() {
    /*
    int w = 4, v = 3;
    cout << "w is " << w <<' ' << "v is " << v << endl;
    function<void(int&, int&)> lambda = [&](int &k, int &z) {
        int t = k;
        k = z;
        z = t;
    };
    lambda(w, v);
    cout << "w is " << w <<' ' << "v is " << v << endl;*/
    A tst(3, 2);
    A tst2 = tst;
    tst2.print();
    tst.print();
    B t2;
    t2.print();
    return 0;
}
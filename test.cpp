#include <iostream>
#include <deque>
#include <string>
#include <memory>

class Base {
protected:
    int x;
public:
    Base() {}
    Base(int _x): x(_x) {}
    virtual void func() {
        printf("Base function");
    }
    virtual ~Base() {

    }
};
class Derived: public Base {
public:
    Derived() {}
    Derived(int _x): Base(_x) {
        x = _x;
    }
    void func() {
        printf("derived function");
    }
};

void func(const std::string& s) {
    std::cout << s << std::endl;
}

int main() {
    try {
        int*x = new int[1000000000000000];
    }catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    func("Hello");
    Base* base = new Derived;
    Derived* derived = dynamic_cast<Derived*>(base);
    std::cout << base << std::endl;
    if (derived != nullptr) std::cout << derived << std::endl;
    else std::cout << "null";
    delete base;
    return 0;
}
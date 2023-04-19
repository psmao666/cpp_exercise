#include <bits/stdc++.h>

template<typename T>
class unique_ptr {
    T* ptr;
public:
    unique_ptr(): ptr(nullptr) {}
    explicit unique_ptr(T* a) {
        this->ptr = a;
    }
    unique_ptr(unique_ptr<T>& a) = delete; 
    unique_ptr<T>& operator= (const unique_ptr<T>& a) = delete;
    T& operator* () const {
        return (*ptr);
    }
    T* operator->() const {
        return ptr;
    }
    ~unique_ptr() {
        delete ptr;
    }
};

class Base{
    int x;
public:
    Base(): x(1) {}
    Base(int _): x(_) {}
    int getvalue() {
        return x;
    } 
};

void func(int&& a) {
    int* tmp = &a;
}

int main() {
    // general test
    unique_ptr<int> ptr(new int(3));
    std::cout << (*ptr) << std::endl;
    // test modification
    int& x = (*ptr);
    x = 8;
    std::cout << (*ptr) << std::endl;
    // test class type, and function
    unique_ptr<Base> ptr2(new Base(2));
    std::cout << ptr2->getvalue() << std::endl;
    // test pointer copy
    //unique_ptr<int> ptr3 = ptr;
    //std::cout << (*ptr3) << std::endl;
    std::vector<int> a, b, c;
    for (int i = 0; i < 1000000; ++ i) a.push_back(i);
    std::cout << a.size() << std::endl;
    b = std::move(a);
    std::cout << a.size() << std::endl;
    return 0;
}
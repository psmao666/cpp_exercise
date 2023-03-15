#include <iostream>
#include <memory> 

void func();   // test forward declaration
void func(int x);
class g;

void test_pointers(){
    int x = 23, y = 40;
    const int *a = &x; // mutable pointer to immutable value
    a = &y;
    // *a = 30; invalid
    std::cout << *a << std::endl;
    int *const b = &x; // immutable pointer to mutable value
    *b = 38;
    //b = &y; invalid
    std::cout << *b << ' ' << *a << std::endl;
    const int* const c = &x; // immutable pointer to immutable value
}

void test_function_overload() {
    func();
    func(4);
}
void func() {
    std::cout << "shit" << std::endl;
}
void func(int x) {
    std::cout << x << std::endl;
}

void test_smartpointers() {
    int* raw = new int[10];
    *raw = 5;
    *(raw+1) = 6;
    std::cout << raw[0] << ' ' << raw[1] << std::endl;
    delete[] raw;
    int x = 255;
    //raw = &x;
    std::shared_ptr<int> ptr(new int(19260817));
    std::cout << (*ptr) << ' ' << ptr.get() << std::endl;
    ptr.reset();
    ptr = std::make_shared<int>(666);
    std::cout << (*ptr) << ' ' << ptr.get() << std::endl;
    std::shared_ptr<int> ptr2 = ptr;
    std::cout << (*ptr2) << ' ' << ptr2.get() << std::endl;
    (*ptr) = 4;
    std::cout << (*ptr2) << ' ' << ptr2.get() << std::endl;
    ptr.reset();
    ptr = std::make_shared<int>(888);
    std::cout << (*ptr) << ' ' << ptr.get() << std::endl;
    std::cout << (*ptr2) << ' ' << ptr2.get() << std::endl;

}

int main() {
    test_pointers();
    test_function_overload();
    test_smartpointers();
    return 0;
}
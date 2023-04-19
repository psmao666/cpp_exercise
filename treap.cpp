#include <bits/stdc++.h>
using namespace std;

class Employee{
public:
    string name;
    int age;
    Employee(){}
    Employee(string _x, int y): name(_x), age(y){}
};

Employee* findEmployee(const string& sur, const string& given, bool r = false) {
    Employee* tmp = new Employee(given, 3);
    return tmp;
}
Employee* findEmployee(const string& sur, bool r = false) {
    Employee* tmp = new Employee(sur, 3);
    cout << r << endl;
    return tmp;
}

int main() {
    Employee* e = findEmployee("a", "b");
    cout << e->name << endl;
    return 0;
}

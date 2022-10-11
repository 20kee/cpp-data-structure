#include <iostream>
#include <string>
using namespace std;

class Employee {
    int num;
    string ename;
    float salary;
    string dept;
    static int count;
public:
    Employee();
    Employee(int);
    Employee(const Employee&);
    ~Employee();
    Employee& operator = (const Employee&);
    int operator++();
    static int Show() { return count; }
    friend ostream& operator<< (ostream& stream, Employee&);
    float get_salary() const { return salary; }
};

Employee::Employee():ename("Unknown"),dept("computer development")
{
    num = count+1;
    salary = 0.0f;
    count += 1;
}

Employee::Employee(int k):ename("Unknown"),dept("computer development")
{
    num = count+1;
    salary = 0.0f;
    count += 1;
}

Employee::Employee(const Employee& em)
{
    this->num = count+1;
    this->salary = em.get_salary();
    count += 1;
}

Employee::~Employee()
{
    count -= 1;
}



void main()
{
    Employee sd1;
    Employee sd2(10);
    Employee sd3(sd2);
    Employee::Show();
    sd1.Show();
    Employee sd4 = sd2;
    sd3 = sd2;
    cout << endl;
    cout << sd4;
    system("pause");


}
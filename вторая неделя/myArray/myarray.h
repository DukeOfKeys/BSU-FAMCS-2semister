#include <iostream>
using namespace std;

struct Bad_dimensions
{
};

struct error
{
    const char *string;
    error(const char str[100]) : string(str) {}
};

class Array
{
    int size;
    int *a;

public:
    Array();
    ~Array();
    Array(int size);
    Array(const Array &obj);
    Array(Array &&obj);

    Array &operator=(const Array &obj);
    Array &operator=(int var);
    Array &operator=(Array &&obj);

    friend Array operator+(Array &obj1, Array &obj2);
    friend Array operator-(Array &obj1, Array &obj2);
    friend Array operator*(Array &obj1, Array &obj2);
    friend Array operator/(Array &obj1, Array &obj2);

    friend Array operator+(int var, Array &obj);
    friend Array operator+(Array &obj, int var);
    friend Array operator-(int var, Array &obj);
    friend Array operator-(Array &obj, int var);
    friend Array operator*(int var, Array &obj);
    friend Array operator*(Array &obj, int var);
    friend Array operator/(int var, Array &obj);
    friend Array operator/(Array &obj, int var);

    Array &operator+=(const Array &obj);
    Array &operator-=(const Array &obj);
    Array &operator*=(const Array &obj);
    Array &operator/=(const Array &obj);

    Array &operator+=(int var);
    Array &operator-=(int var);
    Array &operator*=(int var);
    Array &operator/=(int var);

    friend bool operator<(Array &obj1, Array &obj2);
    friend bool operator>(Array &obj1, Array &obj2);
    friend bool operator==(Array &obj1, Array &obj2);
    friend bool operator!=(Array &obj1, Array &obj2);
    friend bool operator<=(Array &obj1, Array &obj2);
    friend bool operator>=(Array &obj1, Array &obj2);

    friend bool operator<(Array &obj1, int var);
    friend bool operator>(Array &obj1, int var);
    friend bool operator==(Array &obj1, int var);
    friend bool operator!=(Array &obj1, int var);
    friend bool operator<=(Array &obj1, int var);
    friend bool operator>=(Array &obj1, int var);

    friend bool operator<(int var, Array &obj);
    friend bool operator>(int var, Array &obj);
    friend bool operator==(int var, Array &obj);
    friend bool operator!=(int var, Array &obj);
    friend bool operator<=(int var, Array &obj);
    friend bool operator>=(int var, Array &obj);

    friend istream &operator>>(istream &in, Array &obj);
    friend ostream &operator<<(ostream &out, Array &obj);

    friend Array operator-(Array &obj);
    friend Array operator+(Array &obj);

    Array operator++(int);
    Array &operator++();

    int &operator[](int i);

    void print(Array &obj);
};

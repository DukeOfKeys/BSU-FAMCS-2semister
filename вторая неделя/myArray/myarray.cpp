#include "myarray.h"
#include <iostream>
using namespace std;

Array::Array()
{
    size = 10;
    a = new int[10];
    for (int i = 0; i < size; i++)
        a[i] = i + 1;
}

Array::Array(Array &&obj)
{
    size = obj.size;
    a = obj.a;
    obj.a = nullptr;
}

Array::~Array()
{
    delete[] a;
}

Array::Array(int size)
{
    a = new int[size];
    this->size = size;
    for (int i = 0; i < size; i++)
        a[i] = rand() % 10;
}
Array::Array(const Array &obj)
{
    if (this != &obj)
    {
        this->size = obj.size;
        this->a = new int[obj.size];
        for (int i = 0; i < this->size; i++)
            this->a[i] = obj.a[i];
    }
}

Array &Array::operator=(const Array &obj)
{
    if (this != &obj)
    {
        delete[] a;
        size = obj.size;
        a = new int[size];
        for (int i = 0; i < size; i++)
            a[i] = obj.a[i];
        return *this;
    }
}

Array &Array::operator=(Array &&obj)
{
    size = obj.size;
    delete[] a;
    a = obj.a;
    obj.a = NULL;
}

Array &Array::operator=(int var)
{
    if (size == 1)
    {
        a[0] = var;
        return *this;
    }
}

Array Array::operator++(int)
{
    for (int i = 0; i < size; i++)
        a[i]++;
    return *this;
}

Array &Array::operator++()
{
    for (int i = 0; i < size; i++)
        ++a[i];
    return *this;
}

int &Array::operator[](int i)
{
    if (i < 0 || i >= size)
        throw error("����� �� ������� �������");
    return a[i];
}

void Array::print(Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        cout << obj[i] << ' ';
    cout << endl;
}

ostream &operator<<(ostream &out, Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        out << obj[i] << " ";
    out << endl;
    return out;
}

Array operator-(Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] = -obj[i];
    return obj;
}

Array operator+(Array &obj)
{
    return obj;
}

istream &operator>>(istream &in, Array &obj)
{
    cout << "������� �������� �������: ";
    for (int i = 0; i < obj.size; i++)
        in >> obj[i];
    return in;
}

Array operator+(Array &obj1, Array &obj2)
{
    if (obj1.size != obj2.size)
        throw error("�� ����� �����������");
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            obj2[i] += obj1[i];
    return obj2;
}

Array operator-(Array &obj1, Array &obj2)
{
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            obj2[i] -= obj1[i];
    return obj2;
}

Array operator/(Array &obj1, Array &obj2)
{
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
        {
            if (obj1[i] == 0)
                throw "����� �� ������� �������";
            obj2[i] /= obj1[i];
        }
    return obj2;
}

Array operator*(Array &obj1, Array &obj2)
{
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            obj2[i] *= obj1[i];
    return obj2;
}

Array operator+(int var, Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] += var;
    return obj;
}

Array operator-(int var, Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] = var - obj[i];
    return obj;
}

Array operator*(int var, Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] *= var;
    return obj;
}

Array operator/(int var, Array &obj)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] = var / obj[i];
    return obj;
}

Array operator+(Array &obj, int var)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] += var;
    return obj;
}

Array operator-(Array &obj, int var)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] -= var;
    return obj;
}

Array operator*(Array &obj, int var)
{
    for (int i = 0; i < obj.size; i++)
        obj[i] *= var;
    return obj;
}

Array operator/(Array &obj, int var)
{
    if (var == 0)
        throw "������� ������� �� 0";
    for (int i = 0; i < obj.size; i++)
        obj[i] /= var;
    return obj;
}

Array &Array::operator+=(const Array &obj)
{
    Array c(obj);
    if (size == obj.size)
        for (int i = 0; i < size; i++)
            c[i] += a[i];
    if (this != &c)
    {
        for (int i = 0; i < size; i++)
            a[i] = c[i];
        return *this;
    }
}

Array &Array::operator-=(const Array &obj)
{
    Array c(obj);
    if (size == obj.size)
        for (int i = 0; i < size; i++)
            c[i] = a[i] - c[i];
    if (this != &c)
    {
        for (int i = 0; i < size; i++)
            a[i] = c[i];
        return *this;
    }
}

Array &Array::operator*=(const Array &obj)
{
    Array c(obj);
    if (size == obj.size)
        for (int i = 0; i < size; i++)
            c[i] *= a[i];
    if (this != &c)
    {
        for (int i = 0; i < size; i++)
            a[i] = c[i];
        return *this;
    }
}

Array &Array::operator/=(const Array &obj)
{
    Array c(obj);
    if (size == obj.size)
        for (int i = 0; i < size; i++)
        {
            if (c[i] == 0)
                throw error("������� ������� �� 0");
            c[i] = a[i] / c[i];
        }
    if (this != &c)
    {
        for (int i = 0; i < size; i++)
            a[i] = c[i];
        return *this;
    }
}

Array &Array::operator+=(int var)
{
    if (var)
    {
        for (int i = 0; i < size; i++)
            a[i] += var;
        return *this;
    }
}

Array &Array::operator-=(int var)
{
    if (var)
    {
        for (int i = 0; i < size; i++)
            a[i] -= var;
        return *this;
    }
}

Array &Array::operator*=(int var)
{
    if (var != 1)
    {
        for (int i = 0; i < size; i++)
            a[i] *= var;
        return *this;
    }
}

Array &Array::operator/=(int var)
{
    if (var == 0)
        throw error("������� ������� �� 0");
    if (var != 1)
    {
        for (int i = 0; i < size; i++)
            a[i] += var;
        return *this;
    }
}

bool operator<(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] >= obj2[i])
                count++;
            else if (obj1[i] < obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] <= obj2[i])
                count++;
            else if (obj1[i] > obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator<=(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] > obj2[i])
                count++;
            else if (obj1[i] <= obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>=(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] < obj2[i])
                count++;
            else if (obj1[i] >= obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator==(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] != obj2[i])
                count++;
            else if (obj1[i] == obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator!=(Array &obj1, Array &obj2)
{
    int count = 0;
    if (obj1.size == obj2.size)
        for (int i = 0; i < obj1.size; i++)
            if (obj1[i] == obj2[i])
                count++;
            else if (obj1[i] != obj2[i])
                count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator<(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] >= var)
            count++;
        else if (obj1[i] < var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] <= var)
            count++;
        else if (obj1[i] > var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator<=(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] > var)
            count++;
        else if (obj1[i] <= var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>=(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] < var)
            count++;
        else if (obj1[i] >= var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator==(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] != var)
            count++;
        else if (obj1[i] == var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator!=(Array &obj1, int var)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] == var)
            count++;
        else if (obj1[i] != var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator<(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] <= var)
            count++;
        else if (obj1[i] > var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] >= var)
            count++;
        else if (obj1[i] < var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator<=(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] < var)
            count++;
        else if (obj1[i] >= var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator>=(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] > var)
            count++;
        else if (obj1[i] <= var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator==(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] != var)
            count++;
        else if (obj1[i] == var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

bool operator!=(int var, Array &obj1)
{
    int count = 0;
    for (int i = 0; i < obj1.size; i++)
        if (obj1[i] == var)
            count++;
        else if (obj1[i] != var)
            count--;
    if (count >= 0)
        return false;
    else if (count < 0)
        return true;
}

#ifndef M_SET_H
#define M_SET_H
#include <algorithm>
#include <iostream>
#include <QTextStream>
#include <QDataStream>
#include <deque>
#include <QString>
using namespace std;
template <class T>
class m_set
{
private:
    deque<T> data;
    unsigned int size;

    bool contains(T &obj)
    {
        return binary_search(data.begin(), data.end(), obj);
    }
    // может быть лишним
    void remove_duplicates()
    {
        sort(data.begin(), data.end());
        auto it = unique(data.begin(), data.end());
        data.erase(it, data.end());
    }

public:
    m_set() : data(deque<T>()), size(0) {}
    m_set(const T &obj) : size(obj.size), data(obj.data) {}
    void push(T obj)
    {
        if (contains(obj))
            return;
        size++;
        data.push_back(obj);
        sort(data.begin(), data.end());
    }
    m_set operator+(const m_set &obj)
    {
        m_set new_obj;
        for (int index1 = 0, index2 = 0; index1 < size || index2 < obj.size;)
            if (index2 == obj.size || (index1 < size && data[index1] < obj.data[index2]))
                new_obj.data.push_back(data[index1++]);
            else if (index1 == size || (index2 < obj.size && obj.data[index2] < data[index1]))
                new_obj.data.push_back(obj.data[index2++]);
            else
                new_obj.data.push_back(data[index1++]), ++index2;

        new_obj.size = new_obj.data.size();
        return new_obj;
    }
    m_set operator-(const m_set &obj)
    {
        m_set new_obj;
        for (int index1 = 0, index2 = 0; index1 < size || index2 < obj.size;)
        {
            if (index2 == obj.size || (index1 < size && data[index1] < obj.data[index2]))
                new_obj.data.push_back(data[index1++]);
            else if (index1 == size || (index2 < obj.size && obj.data[index2] < data[index1]))
                index2++;
            else
                ++index1, ++index2;
        }
        new_obj.size = new_obj.data.size();
        return new_obj;
    }
    m_set operator&(const m_set &obj)
    {
        m_set new_obj;
        for (int index1 = 0, index2 = 0; index1 < size || index2 < obj.size;)

            if (index2 == obj.size || (index1 < size && data[index1] < obj.data[index2]))
                index1++;
            else if (index1 == size || (index2 < obj.size && obj.data[index2] < data[index1]))
                index2++;
            else
                new_obj.data.push_back(data[index1++]), ++index2;

        new_obj.size = new_obj.data.size();
        return new_obj;
    }
    m_set &operator=(const m_set &obj)
    {
        size(obj.size);
        data(obj.data);
        return *this;
    }
    m_set operator^(const m_set &obj)
    {
        m_set new_obj;
        for (int index1 = 0, index2 = 0; index1 < size || index2 < obj.size;)
            if (index2 == obj.size || (index1 < size && data[index1] < obj.data[index2]))
                new_obj.data.push_back(data[index1++]);
            else if (index1 == size || (index2 < obj.size && obj.data[index2] < data[index1]))
                new_obj.data.push_back(obj.data[index2++]);
            else
                index1++, ++index2;

        new_obj.size = new_obj.data.size();
        return new_obj;
    }
    friend ostream &operator<<(ostream &_out, const m_set &obj)
    {
        if (!obj.size)
            return _out << "no data" << endl;
        for (int index = 0; index < obj.size; index++)
        {
            _out << obj.data[index] << " ";
        }
        _out << endl;
        return _out;
    }
    friend QTextStream &operator<<(QTextStream &_out, const m_set &obj)
    {
        _out << obj.size << "\n";
        for (auto el : obj.data)
        {
            _out << el << "\n";
        }
        return _out;
    }

    friend QTextStream &operator>>(QTextStream &_in, m_set &obj)
    {
        unsigned int size_obj;
        _in >> size_obj;
        T in_obj;
        for (int index = 0; index < size_obj; index++)
        {
            _in >> in_obj;
            obj.push(in_obj);
        }
        return _in;
    }
    friend QDataStream &operator<<(QDataStream &_out, const m_set &obj)
    {
        _out << obj.size;
        for (auto el : obj.data)
        {
            _out << el;
        }
        return _out;
    }

    friend QDataStream &operator>>(QDataStream &_in, m_set &obj)
    {
        unsigned int size_obj;
        _in >> size_obj;
        cout << "SIZE: " << size_obj << endl;
        T in_obj;
        for (int index = 0; index < size_obj; index++)
        {
            _in >> in_obj;
            obj.push(in_obj);
        }
        return _in;
    }
};
class Student
{
    int id;
    QString name;
    QString surname;
    unsigned int group;
    bool operator==(const Student &obj)
    {
        return id == obj.id;
    }
    friend ostream &operator<<(ostream &_out, Student obj)
    {
        _out << "| Id:" << obj.id << " Name: " << obj.name.toStdString() << " Surname: " << obj.surname.toStdString() << " Group: " << obj.group;
        return _out;
    }
    friend QTextStream &operator<<(QTextStream &_out, const Student &obj)
    {
        _out << obj.id << " " << obj.name << obj.surname << " " << obj.group;
        return _out;
    }

    friend QTextStream &operator>>(QTextStream &_in, Student &obj)
    {
        _in >> obj.id >> obj.name >> obj.surname >> obj.group;
        return _in;
    }
    friend QDataStream &operator<<(QDataStream &_out, const Student &obj)
    {
        _out << obj.id << obj.name << obj.surname << obj.group;
        return _out;
    }

    friend QDataStream &operator>>(QDataStream &_in, Student &obj)
    {
        _in >> obj.id >> obj.name >> obj.surname >> obj.group;
        return _in;
    }

public:
    Student() {}
    Student(QString _name, QString _surname, unsigned int _group) : id(rand() % 1000), name(_name), surname(_surname), group(_group) {}
    friend bool operator<(const Student &obj1, const Student &obj)
    {
        return obj1.id < obj.id;
    }
};
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
// #include "m_set.h"
#include <time.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    srand(time(NULL));
    // m_set<double> el1{};
    // m_set<double> el2{};
    // for (int index = 0; index < 5; index++)
    // {
    //     el1.push(double(rand() % 5));
    //     el2.push(double(rand() % 5));
    // }
    // cout << el1 << el2;
    // m_set<double> el3 = el1 + el2;
    // m_set<double> el4 = el1 - el2;
    // cout << el3;
    // cout << el4;
    // QFile file("output.dat");
    // if (file.open(QIODevice::WriteOnly)) {
    //     QDataStream out(&file);
    //     out << el3;
    //     file.close();
    // }

    // m_set<double> newObj;
    // if (file.open(QIODevice::ReadOnly)) {
    //     QDataStream in(&file);
    //     in >> newObj;
    //     file.close();
    // }
    // cout << newObj;

    // m_set<double> new_el;
    // QFile file_text("output.txt");
    // if (file_text.open(QIODevice::WriteOnly | QIODevice::Text)) {
    //     QTextStream out(&file_text);
    //     out << newObj;
    //     file_text.close();
    // }

    // if (file_text.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     QTextStream in(&file_text);
    //     in >> new_el;
    //     file_text.close();
    // }
    // cout<< new_el;

    Student u1("1", "1", 1), u2("2", "2", 1);
    m_set<Student> university;
    university.push(u1);
    university.push(u2);
    cout << university;

    QFile file("output.dat");
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << university;
        file.close();
    }

    m_set<Student> newObj;
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> newObj;
        file.close();
    }
    cout << "from binary" << newObj;
    return a.exec();
}

#endif // M_SET_H

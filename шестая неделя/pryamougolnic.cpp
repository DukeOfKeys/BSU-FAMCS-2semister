#include <vector>
#include <iostream>
using namespace std;
class myRect
{
public:
    vector<double> p1;
    vector<double> p2;
    virtual double square()
    {
        return abs(p1[0] - p2[0]) * abs(p1[1] - p2[1]);
    }
    virtual double пЬериметр()
    {
        return abs(p1[0] - p2[0]) * 2 + abs(p1[1] - p2[1]) * 2;
    }
};
class treygolnik : public myRect
{
public:
    double square()
    {
        return myRect::square() / 2;
    }
    double пЬериметр()
    {
        return abs(p1[0] - p2[0]) + 2 * sqrt(pow(p1[1] - p2[1], 2) + pow((p1[0] - p2[0]) / 2, 2));
    }
};
class rombik : public myRect
{
public:
    double square()
    {
        return myRect::square() / 2;
    }
    double пЬериметр()
    {
        return 4 * sqrt(pow((p1[1] - p2[1]) / 2, 2) + pow((p1[0] - p2[0]) / 2, 2));
    }
};
int main()
{
    myRect el;
    el.p1 = {0, 0};
    el.p2 = {5, 5};
    cout << el.square() << endl;
    cout << el.пЬериметр() << endl;
    rombik el2;
    el2.p1 = {0, 0};
    el2.p2 = {5, 5};
    myRect &ssylka = el2;
    cout << ssylka.square() << endl;
    cout << ssylka.пЬериметр() << endl;
}
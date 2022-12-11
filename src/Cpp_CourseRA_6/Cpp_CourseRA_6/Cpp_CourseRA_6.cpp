// Cpp_CourseRA_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "student.h"

using namespace std;

/// <summary>
/// TODO: Remove later
/// https://boardgamearena.com/tutorial?game=hex&tutorial=746
/// Plan: 
///     - create a nxn board where n is odd (5 to start?),
///     - sd
/// </summary>
/// <returns></returns>

void Wk_1__numerical_ex1();
void Wk_1_for_each_ex1();
void Wk_1_myMapExample2();
void Wk_2_grad_new();
void Wk_2_mc_2();

int main()
{
    //Wk_1__numerical_ex1();
    //Wk_1_for_each_ex1();
    //Wk_1_myMapExample2();
    //Wk_2_grad_new();
    Wk_2_mc_2();
}

void Wk_1__numerical_ex1()
{
    double v1[3] = { 1.0, 2.5, 4.6 },
        v2[3] = { 1.0, 2.0, -3.5 };
    double sum, inner_p;

    //v1 and v2 are base addresses - so they can be used as
    //the beginning of an iterator range
    //v1 + 3 is pointer arithmetic and is the end sentinel.

    sum = accumulate(v1, v1 + 3, 0.0);
    inner_p = inner_product(v1, v1 + 3, v2, 0.0);
    cout << "sum = " << sum
        << ",   product = " << inner_p
        << endl;
}

void Wk_1_for_each_ex1()
{
    const int size = 6;
    vector <int>  v(size);
    //classic for 
    for (int i = 0; i < size; ++i)
    {
        v[i] = i;
        cout << v[i] << "\t";
    }
    cout << endl;
    //iterator logic + auto C++11
    for (auto p = v.begin(); p != v.end(); ++p)
        cout << *p << "\t";
    cout << endl;
    //for range 
    for (int element : v)
        cout << element << "\t";
    cout << endl;

    //STL   C++11  lambda
    for_each(v.begin(), v.end(),
        [](int i) {cout << i << "\t"; }
    );
    cout << endl;
}

void Wk_1_myMapExample2()
{
    vector <std::string> words;
    string temp_str, file_name;
    cout << "What File do you want?\n";
    cin >> file_name;

    ifstream fin(file_name);
    while (fin >> temp_str) // Will read up to eof()
        words.push_back(temp_str);

    fin.close();

    unordered_map<std::string, size_t>  word_map;
    for (const auto& w : words)
        ++word_map[w];

    for (const auto& pair : word_map)
        cout << pair.second
        << " occurrences of word '"
        << pair.first << "'\n";
}

void Wk_2_grad_new()
{
    /**
    With Virtual print() in student

Mae Pohl , 100 ,  Fresh  , 3.425

Morris Pohl , 200 ,  Grad  , 3.2564
Pharmacy ,  TA
Retail Pharmacies

Morris Pohl , 200 ,  Grad  , 3.2564
Pharmacy ,  TA
Retail Pharmacies

-----------------------    
    Without Virtual print() in student

Mae Pohl , 100 ,  Fresh  , 3.425

Morris Pohl , 200 ,  Grad  , 3.2564

Morris Pohl , 200 ,  Grad  , 3.2564
Pharmacy ,  TA
Retail Pharmacies

    **/
    student        s("Mae Pohl", 100, 3.425, year::fresh), * ps = &s;
    grad_student   gs("Morris Pohl", 200, 3.2564,
        year::grad, support::ta, "Pharmacy",
        "Retail Pharmacies"), * pgs;

    ps->print();     //student::print
    ps = pgs = &gs;
    ps->print();     //grad_student::print
    pgs->print();    //grad_student::print
}

///////////////////Wk_2_mc_2////////////

typedef tuple<double, double> point;
ostream& operator<<(ostream& out, const point& pt)
{
    out << "( " << get<0>(pt) << ", ";
    out << get<1>(pt) << ") ";
    return out;
}

point random_point()
{
    default_random_engine generator;
    uniform_real_distribution<double> u(0, 1);
    point temp;
    get<0>(temp) = u(generator);
    get<1>(temp) = u(generator);
    return temp;
}

double mc_count(double f(double), vector<point>::iterator first, vector <point>::iterator last)
{
    int trials = 0; int below = 0;
    for (first; first != last; ++first) {
        ++trials;
        if (f(get<0>(*first)) > get<1>(*first))
            ++below;
    }
    return(1.0 * below / trials);
}

void Wk_2_mc_2()
{
    default_random_engine  e(time(nullptr));  //seed in constructor
    int data_size;
    cout << " How Many Points? " << endl;
    cin >> data_size;
    vector<point> data(data_size);
    for (auto& element : data) {
        element = random_point();
        cout << element << endl;
    }


    cout << " PI by MC integration is " <<
        4.0 * mc_count([](double x) { return (sqrt(1 - x * x)); }, data.begin(), data.end());
    cout << endl;
}
////////////////////////////////
#pragma once
#include <string>

using namespace std;

enum class year { fresh, soph, junior, senior, grad };
class student {
public:
	student(string nm, int id, double g, year x);
	virtual void  print()const;
protected:
	int       student_id;
	double    gpa;
	year      y;
	string    name;
};

enum class support { ta, ra, fellowship, other };
class grad_student : public student {
public:
	grad_student
	(string  nm, int id, double g, year x, support t, string d, string th);
	void print()const;
protected:
	support      s;
	string       dept;
	string       thesis;
};
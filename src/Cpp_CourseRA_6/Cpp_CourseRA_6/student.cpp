#include "student.h"
#include <iostream>

ostream& operator<<(ostream& out, const year& yr)
{
	if (yr == year::fresh) out << " Fresh ";
	else if (yr == year::soph) out << " Soph ";
	else if (yr == year::junior) out << " Junior ";
	else if (yr == year::senior) out << " Senior ";
	else if (yr == year::grad) out << " Grad ";

	return out;
}

ostream& operator<<(ostream& out, const support& s)
{
	if (s == support::ta) out << " TA ";
	else if (s == support::ra) out << " RA ";
	else if (s == support::fellowship) out << " Fellowship ";
	else if (s == support::other) out << " Other ";

	return out;
}

student::student(string nm, int id, double g, year x)
	:student_id(id), gpa(g), y(x), name(nm) { }

grad_student::grad_student(
	string nm, int id, double g, year x,
	support t, string d, string th)
	:student(nm, id, g, x), s(t), dept(d), thesis(th) { }

void student::print() const
{
	cout << "\n" << name << " , " << student_id << " , "
		<< y << " , " << gpa << endl;
}

void grad_student::print()const
{
	student::print();    //base class information is printed
	cout << dept << " , " << s << "\n" << thesis << endl;
}

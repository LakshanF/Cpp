#pragma once

class duo {
protected:
	double first, second;
public:
	duo():first(0.0), second(0.0){}
	void set_first(double d) { first = d; }
	void set_second(double d) { second = d; }
	double get_first() { return first; }
	double get_second() { return second; }
};
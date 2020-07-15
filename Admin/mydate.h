#pragma once
#include <vector>
using namespace std;

#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/WDateTime>
#include <Wt/WTime>

using namespace Wt;

class MyDate : public WDateTime {
private:
	int wday;
	WTime start;
	WTime end;
protected:
public:
	MyDate(int wday, WTime start, WTime end);
	~MyDate();
	int getIntWday();
	WString getStrWday();
	WTime getStart();
	WTime getEnd();
};
#include "myDate.h"

MyDate::MyDate(int wday, WTime start, WTime end) :
	wday(wday), start(start), end(end)
{
	return;
}

MyDate::~MyDate()
{
	return;
}

int MyDate::getIntWday()
{
	return this->wday;
}

WString MyDate::getStrWday()
{
	switch (this->wday)
	{
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	case 7:
		return "Sunday";
	}
}

WTime MyDate::getStart()
{
	return this->start;
}

WTime MyDate::getEnd()
{
	return this->end;
}

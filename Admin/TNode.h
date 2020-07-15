#pragma once
#include<iostream>
#include <vector>
#include <Wt/WPushButton>
#include<string.h>
using namespace Wt;
using namespace std;

class TNode {
public:
	TNode * this_node = this;
	WString time_str1;
	WString time_str2;
	int t_row;
	WString weekday;
	int NodNum;
	int sort_param;
	int week_day;
	int hour;
	int minute;
	int hour2;
	int minute2;
	bool is_EP;
	static int week_day_cal(WString weekday) {
		if (weekday == "Saturday") {
			return 6;
		}
		else if (weekday == "Sunday") {
			return 7;
		}
		else if (weekday == "Monday") {
			return 1;
		}
		else if (weekday == "Tuesrday") {
			return 2;
		}
		else if (weekday == "Wednesday") {
			return 3;
		}
		else if (weekday == "Thirsday") {
			return 4;
		}
		else if (weekday == "Friday") {
			return 5;
		}
	}
	TNode(int hour, int minute, int hour2, int minute2, WString weekday, WString time_str1, WString time_str2, int t_row, bool is_EP) {
		this->weekday = weekday;
		this->hour = hour;
		this->minute = minute;
		this->hour2 = hour2;
		this->minute2 = minute2;
		this->time_str1 = time_str1;
		this->time_str2 = time_str2;
		this->t_row = t_row;
		this->week_day = week_day_cal(weekday);
		this->is_EP = is_EP;
	}
};

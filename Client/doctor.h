#pragma once
#include <vector>
#include "mydate.h"
#include <Wt/WDate>
using namespace std;

#include <Wt/WApplication>
#include <Wt/WString>

using namespace Wt;
class Doctor {
private:
	int id;
	WString fname;
	WString lname;
	WString speciality;
	vector<MyDate> normal_presence;
	vector<MyDate> emergency_presence;
	int visit_time;
	int visit_price;
	vector<WDateTime> appointments;
	static unsigned int doc_cnt;
protected:
public:
	Doctor(WString fname, WString lname, WString speciality, int visit_tm, int visit_pr, bool create_file = true);
	~Doctor();
	void addNP(MyDate np, bool write_in_file = 1);
	void addEP(MyDate ep, bool write_in_file = 1);
	vector<MyDate> getEps();
	vector<MyDate> getNps();
	int getVisit_tm();
	bool InApps(WDateTime app);
	int getID();
	void addApp(WDateTime app);
	int getVisitPr();
	static unsigned int getCnt();
	WString getSpeciality();
	WString getName();
	WString getFamily();
	vector <WDateTime> appointment(WDate fdate, WDate ldate,bool emergency);
};
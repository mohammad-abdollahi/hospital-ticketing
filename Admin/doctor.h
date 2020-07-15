#pragma once
#include <vector>
#include "mydate.h"
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
	Doctor(WString fname, WString lname, WString speciality, int visit_tm, int visit_pr);
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
	static void set_doc_cnt() {
		ifstream doc("C:/doctors/doc1.d", ios::_Nocreate);
		while (doc) {
			doc_cnt++;
			string fname;
			ostringstream convert;
			convert << doc_cnt + 1;
			fname = "C:/doctors/doc" + convert.str() + ".d";
			doc.close();
			doc.open(fname.c_str(), ios::_Nocreate);
		}
	}
};
#include <fstream>
#include <string>
#include <cstdio>
#include "doctor.h"
#include "mydate.h"
using namespace std;

Doctor::Doctor(WString fname, WString lname, WString speciality, int visit_tm, int visit_pr):
	fname(fname), lname(lname), speciality(speciality), visit_time(visit_tm), visit_price(visit_pr)
{
	this->id = ++doc_cnt;
	ostringstream convert;
	convert << id;
	string det_name = "C:/doctors/doc" + convert.str() + ".d"; //doctor details file
	string app_name = "C:/doctors/doc" + convert.str() + ".a"; //doctor appointments file
	ofstream doc(det_name, ios::_Noreplace);
	if (doc)
		doc << fname << '\t' << lname << '\t' << speciality << '\t' << visit_tm << '\t' << visit_pr << endl;
	ofstream doc_apps(app_name, ios::_Noreplace);
	doc.close();
	doc_apps.close();
		return;
}

Doctor::~Doctor()
{
	this->doc_cnt--;
	ostringstream convert;
	convert << id;
	string file_name = "C:/doctors/doc" + convert.str() + ".d";
	char filename[20] = {};
	int i;
	for (i = 0; i < file_name.size(); i++)
		filename[i] = file_name[i];
	remove(filename);
	filename[i - 1] = 'a';
	remove(filename);
	return;
}

void Doctor::addNP(MyDate np, bool write_in_file)
{
	this->normal_presence.push_back(np);
	if (write_in_file) {
		ostringstream convert;
		convert << id;
		string file_name = "C:/doctors/doc" + convert.str() + ".d";
		ofstream doc(file_name, ios::app);
		doc << "NP: " << np.getStrWday() << ' ' << np.getStart().toString() << ' ' << np.getEnd().toString() << endl;
	}
	return;
}

void Doctor::addEP(MyDate ep, bool write_in_file)
{
	this->emergency_presence.push_back(ep);
	if (write_in_file) {
		ostringstream convert;
		convert << id;
		string file_name = "C:/doctors/doc" + convert.str() + ".d";
		ofstream doc(file_name, ios::app);
		doc << "EP: " << ep.getStrWday() << ' ' << ep.getStart().toString() << ' ' << ep.getEnd().toString() << endl;
	}
	return;
}

vector<MyDate> Doctor::getEps()
{
	return this->emergency_presence;
}

vector<MyDate> Doctor::getNps()
{
	return this->normal_presence;
}

int Doctor::getVisit_tm()
{
	return this->visit_time;
}

bool Doctor::InApps(WDateTime app)
{
	for (auto i : this->appointments) {
		if (i == app)
			return true;
	}
	return false;
}

int Doctor::getID()
{
	return this->id;
}

void Doctor::addApp(WDateTime app)
{
	this->appointments.push_back(app);
	return;
}

int Doctor::getVisitPr()
{
	return this->visit_price;
}

unsigned int Doctor::getCnt()
{
	return doc_cnt;
}

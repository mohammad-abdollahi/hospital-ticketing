#pragma once
#include "doctor.h"
#include <vector>
using namespace std;

#include <Wt/WApplication>
#include <Wt/WDate>
#include <Wt/WString>
#include <Wt/WDateTime>
using namespace Wt;

class Patient {
private:
	int id;
	WString fname;
	WString lname;
	int age;
	bool emergency;
	Doctor doctor;
	bool insurance;
	bool gender;
	WString details;
	static unsigned int patient_cnt;
protected:
public:
	Patient(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString details);
	~Patient();
	vector<WDateTime> appointment(WDate fdate, WDate ldate);
	void final_appointment(WDateTime fapp);
	int getVisit();
	bool getInsurance();
	virtual int payment() = 0;
};
class Dental_P : public Patient {
private:
	WString dental_service;
	bool pic;
protected:
public:
	Dental_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString dental_service, bool pic);
	~Dental_P();
	virtual int payment();
};
class General_P : public Patient {
private:
	WString exp;
protected:
public:
	General_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString exp);
	~General_P();
	virtual int payment();
};
class Heart_P : public Patient {
private:
	bool op_hist;
	bool angiography;
	bool failure;
protected:
public:
	Heart_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool op_hist, bool angiography, bool failure);
	~Heart_P();
	virtual int payment();
};
class Neuro_P : public Patient {
private:
	bool ctscan;
protected:
public:
	Neuro_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool ctscan);
	~Neuro_P();
	virtual int payment();
};
class EThN_P : public Patient {
private:
	int which;
protected:
public:
	EThN_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, int which);
	~EThN_P();
	virtual int payment();
};
class Women_P : public Patient {
private:
	bool pregnancy;
protected:
public:
	Women_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool pregnancy);
	~Women_P();
	virtual int payment();
};
class HairSkin_P : public Patient {
private:
	int hair_skin;
	WString general_complain;
protected:
public:
	HairSkin_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, int hair_skin, WString general_complain);
	~HairSkin_P();
	virtual int payment();
};
class Internal_P : public Patient {
private:
	WString organ;
protected:
public:
	Internal_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString organ);
	~Internal_P();
	virtual int payment();
};
class Orthopedics_P : public Patient {
private:
	WString organ;
	bool breakness;
protected:
public:
	Orthopedics_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString organ, bool breakness);
	~Orthopedics_P();
	virtual int payment();
};
class Eye_P : public Patient {
private:
	bool checkup;
	bool eyeglasses;
	bool lense;
protected:
public:
	Eye_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool checkup, bool eyeglasses, bool lense);
	~Eye_P();
	virtual int payment();
};
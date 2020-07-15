#include "patient.h"
#include "doctor.h"

Patient::Patient(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString details) :
	fname(fname), lname(lname), age(age), emergency(emergency), doctor(doctor), insurance(insurance), gender(gender), details(details)
{
	patient_cnt++;
	return;
}

Patient::~Patient()
{
	patient_cnt--;
	return;
}

vector<WDateTime> Patient::appointment(WDate fdate, WDate ldate)
{
	vector<WDateTime> apps;
	for (WDate x = fdate; x <= ldate; x = x.addDays(1)) {
		for (auto a : this->doctor.getNps()) {
			if (x.dayOfWeek() == a.getIntWday()) {
				for (WTime i = a.getStart(); i < a.getEnd(); i = i.addSecs(doctor.getVisit_tm() * 60)) {
					WDateTime input;
					input.setDate(x);
					input.setTime(i);
					if (doctor.InApps(input)) {
						continue;
					}
					else {
						apps.push_back(input);
					}
				}
			}
		}
	}
	if (this->emergency) { //for emergency patients
		for (WDate x = fdate; x <= ldate; x = x.addDays(1)) {
			for (auto a : this->doctor.getEps()) {
				if (x.dayOfWeek() == a.getIntWday()) {
					for (WTime i = a.getStart(); i < a.getEnd(); i = i.addSecs(doctor.getVisit_tm() * 60)) {
						WDateTime input;
						input.setDate(x);
						input.setTime(i);
						if (doctor.InApps(input)) {
							continue;
						}
						else {
							apps.push_back(input);
						}
					}
				}
			}
		}
	}
	return apps;
}

void Patient::final_appointment(WDateTime fapp)
{
	this->doctor.addApp(fapp);
	ostringstream convert;
	convert << this->doctor.getID();
	string app_name = "C:/doctors/doc" + convert.str() + ".a";
	ofstream apps_file(app_name, ios::app);
	apps_file << fapp.toString() << endl;
	return;
}

int Patient::getVisit()
{
	return this->doctor.getVisitPr();
}

bool Patient::getInsurance()
{
	return this->insurance;
}

Dental_P::Dental_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString dental_service, bool pic) :
	dental_service(dental_service), pic(pic), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Dental_P::~Dental_P()
{
	return;
}

int Dental_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	if (this->pic)
		pay -= 2000;
	return pay;
}

General_P::General_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString exp) :
	exp(exp), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

General_P::~General_P()
{
	return;
}

int General_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	return pay;
}

Heart_P::Heart_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool op_hist, bool angiography, bool failure) :
	op_hist(op_hist), angiography(angiography), failure(failure), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Heart_P::~Heart_P()
{
	return;
}

int Heart_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	if (this->angiography)
		pay -= pay / 10;
	return pay;
}

Neuro_P::Neuro_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool ctscan) :
	ctscan(ctscan), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Neuro_P::~Neuro_P()
{
	return;
}

int Neuro_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	if (this->ctscan)
		pay -= pay / 10;
	return pay;
}

EThN_P::EThN_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, int which) :
	which(which), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

EThN_P::~EThN_P()
{
	return;
}

int EThN_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	switch (this->which) {
	case 1:
		pay += 2000;
		break;
	case 2:
		pay += 1000;
		break;
	case 3:
		pay += 1500;
		break;
	}
	return pay;
}

Women_P::Women_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool pregnancy) :
	pregnancy(pregnancy), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Women_P::~Women_P()
{
	return;
}

int Women_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	return pay;
}

HairSkin_P::HairSkin_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, int hair_skin, WString general_complain) :
	hair_skin(hair_skin), general_complain(general_complain), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

HairSkin_P::~HairSkin_P()
{
	return;
}

int HairSkin_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	switch (hair_skin)
	{
	case 1:
		pay += 1000;
		break;
	case 2:
		pay += 1500;
		break;
	}
	return pay;
}

Internal_P::Internal_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString organ) :
	organ(organ), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Internal_P::~Internal_P()
{
	return;
}

int Internal_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	return pay;
}

Orthopedics_P::Orthopedics_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, WString organ, bool breakness) :
	organ(organ), breakness(breakness), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Orthopedics_P::~Orthopedics_P()
{
	return;
}

int Orthopedics_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	if (this->breakness)
		pay += 2500;
	return pay;
}

Eye_P::Eye_P(WString fname, WString lname, int age, bool emergency, Doctor& doctor, bool insurance, bool gender, WString history, bool checkup, bool eyeglasses, bool lense) :
	checkup(checkup), eyeglasses(eyeglasses), lense(lense), Patient(fname, lname, age, emergency, doctor, insurance, gender, history)
{
	return;
}

Eye_P::~Eye_P()
{
	return;
}

int Eye_P::payment()
{
	int pay = this->getVisit();
	if (this->getInsurance())
		pay -= pay / 5;
	if (this->checkup)
		pay = 10000;
	return pay;
}

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "doctor.h"
#include "patient.h"
#include "mydate.h"

#include <Wt/WApplication>
#include <Wt/WString>
#include <Wt/WLabel>
#include <Wt/WComboBox>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WImage>
#include <Wt/WPushButton>
#include <Wt/WDatePicker>
#include <Wt/WBootstrapTheme>
#include <Wt/WCheckBox>
#include <Wt/WLineEdit>
#include <Wt/WSpinBox>
#include <Wt/WDialog>
#include <Wt/WGridLayout>
#include <Wt/WMessageBox>
using namespace Wt;


unsigned int Doctor::doc_cnt = 0;
unsigned int Patient::patient_cnt = 0;
vector<Doctor *> docs;
int doc_spc_bx_item = 0;
long long int dates_bx_items = 0;


class WtApp : public WApplication
{
public:

	WComboBox *doc_bx = new WComboBox();

	WComboBox *doc_spc_bx = new WComboBox();

	WVBoxLayout *main_lay = new WVBoxLayout();

	WDatePicker *from_box = new WDatePicker();
	WDatePicker *to_box = new WDatePicker();

	WCheckBox *emergency_btn = new WCheckBox();

	WComboBox *dates_bx = new WComboBox();

	WPushButton *search_btn = new WPushButton("search");

	WPushButton *reserve_btn = new WPushButton("reserve");

	WPushButton *ens_cancel = new WPushButton("Cancel");

	WPushButton *ens_ok = new WPushButton("Ok");

	WDialog *reserve_dlg = new WDialog("reserve appoinment");


	//dialog items
	WLineEdit *name_led = new WLineEdit();

	WLineEdit *family_led = new WLineEdit();

	WCheckBox *emg_btn = new WCheckBox();

	WSpinBox *age_led = new WSpinBox();

	WCheckBox *ens_btn = new WCheckBox();

	WCheckBox *gen_btn = new WCheckBox();

	WLineEdit *details_led = new WLineEdit();

	//genral doctor
	WLineEdit *gDoc_exp_led = new WLineEdit();

	//dentist special parts
	WLineEdit *Dent_serv_led = new WLineEdit();
	WCheckBox *Dent_pic_btn = new WCheckBox();

	//heart doctor special parts
	WCheckBox *hDoc_op_his_btn = new WCheckBox();
	WCheckBox *hDoc_angio_btn = new WCheckBox();
	WCheckBox *hDoc_fail_btn = new WCheckBox();


	//women doctor special parts
	WCheckBox *women_pre_btn = new WCheckBox();

	//hair doctor special parts
	WCheckBox *hair_btn = new WCheckBox();
	WCheckBox *skin_btn = new WCheckBox();
	WLineEdit *hair_comp_led = new WLineEdit();


	//internal doctor special parts
	WLineEdit *internal_org_led = new WLineEdit();

	//orthoped special parts
	WLineEdit *orth_org_led = new WLineEdit();
	WCheckBox *orth_brk_btn = new WCheckBox();

	//eye doctor special parts
	WCheckBox *eye_chk_btn = new WCheckBox();
	WCheckBox *eye_glass_btn = new WCheckBox();
	WCheckBox *eye_lense_btn = new WCheckBox();

	//EThn special parts
	WCheckBox *ethn_ear_btn = new WCheckBox();
	WCheckBox *ethn_nose_btn = new WCheckBox();
	WCheckBox *ethn_throat_btn = new WCheckBox();

	//nuero special parts
	WCheckBox *nue_ct_btn = new WCheckBox();



	WtApp(const WEnvironment & env)
		: WApplication(env)
	{
		this->setTitle("Clinical Appointment System");
		constructing_docs();

		WImage *medic = new WImage("medical.jpg");
		medic->setHeight(250);

		WVBoxLayout *lay1 = new WVBoxLayout();

		WLabel *doc_name = new WLabel("Doctor speciality:");

		doc_bx->setMaximumSize(125, 30);
		doc_bx->addItem("General");
		doc_bx->addItem("Eye");
		doc_bx->addItem("EThN");
		doc_bx->addItem("Dentist");
		doc_bx->addItem("Internal");
		doc_bx->addItem("Hair & skin");
		doc_bx->addItem("Heart");
		doc_bx->addItem("Nuero");
		doc_bx->addItem("Orthopedics");
		doc_bx->addItem("Women");

		lay1->addWidget(doc_name);
		lay1->addWidget(doc_bx, 2);

		WVBoxLayout *lay2 = new WVBoxLayout();

		WLabel *doc_spc = new WLabel("Doctor name:");

		doc_spc_bx->setMaximumSize(125, 30);
		//doc_spc_bx->addItem("All doctors");

		lay2->addWidget(doc_spc);
		lay2->addWidget(doc_spc_bx, 2);

		WVBoxLayout *from_lay = new WVBoxLayout();

		WLabel *from_lbl = new WLabel("From:");
		from_box->setMaximumSize(125, 30);

		from_lay->addWidget(from_lbl);
		from_lay->addWidget(from_box, 2);

		WVBoxLayout *to_lay = new WVBoxLayout();
		WLabel *to_lbl = new WLabel("To:");
		to_box->setMaximumSize(125, 30);

		to_lay->addWidget(to_lbl);
		to_lay->addWidget(to_box, 2);

		WVBoxLayout *emergency_lay = new WVBoxLayout();
		WLabel *emergency_label = new WLabel("Emergency");
		emergency_btn->setMaximumSize(20, 20);
		emergency_lay->addWidget(emergency_label);
		emergency_lay->addWidget(emergency_btn, 2);

		WHBoxLayout *hLay = new WHBoxLayout();

		hLay->addLayout(lay1);
		hLay->addLayout(lay2);
		hLay->addLayout(from_lay);
		hLay->addLayout(to_lay);
		hLay->addLayout(emergency_lay);


		WHBoxLayout *hLay2 = new WHBoxLayout();

		WVBoxLayout *search_lay = new WVBoxLayout();
		search_btn->setMaximumSize(125, 30);
		search_lay->addWidget(search_btn);

		WVBoxLayout *dates_lay = new WVBoxLayout();
		WLabel *dates_lbl = new WLabel("dates");
		dates_bx->setMaximumSize(125, 30);
		dates_lay->addWidget(dates_lbl);
		dates_lay->addWidget(dates_bx, 2);

		WVBoxLayout *reserve_lay = new WVBoxLayout();
		reserve_btn->setMaximumSize(125, 30);
		reserve_lay->addWidget(reserve_btn);

		hLay2->addLayout(search_lay);
		hLay2->addLayout(dates_lay);
		hLay2->addLayout(reserve_lay);
		main_lay->addWidget(medic);
		main_lay->addLayout(hLay);
		main_lay->addLayout(hLay2);
		root()->setLayout(main_lay);


		doc_bx->doubleClicked().connect(this, &WtApp::spc_search);

		search_btn->clicked().connect(this, &WtApp::date_search);

		reserve_btn->clicked().connect(this, &WtApp::reservation);

		ens_ok->clicked().connect(this, &WtApp::ens_accepted);

		ens_cancel->clicked().connect(this, &WtApp::res_canceled);

		//Setting the theme
		setCssTheme("polished");
		
		return;
	}
protected:
private:

	void sucsessfull(Patient &pat) {
		ifstream pid("pid.txt");
		string spid;
		getline(pid, spid);
		int ipid = atoi(spid.c_str());
		ostringstream convert;
		convert << ++ipid;
		ostringstream convert2;
		convert2 << pat.payment();
		WMessageBox *sucsess = new WMessageBox();
		sucsess->setWindowTitle("Appointment");
		sucsess->setText("Your ID = " + *new WString(convert.str()) + "\nAnd the price is " + *new WString(convert2.str()));
		pid.close();
		ofstream opid("pid.txt", ios::trunc);
		opid << ipid;
		sucsess->setClosable(true);
		sucsess->show();
		return;
	}


	void date_search()
	{
		vector<WDateTime> dates;
		dates_bx->clear();

		//for (int i = 1; i < dates_bx_items; i++)
		//	dates_bx->removeItem(i);

		dates_bx_items = 0;

		for (auto doc : docs)
		{
			WString  name = (doc->getName() + " " + doc->getFamily());
			if ( name == doc_spc_bx->currentText())
				dates = doc->appointment(from_box->date(), to_box->date(), emergency_btn->isChecked());
		}
		for (auto date : dates)
		{
			dates_bx->addItem(date.toString());
			++dates_bx_items;
		}

		return;
	}



	void spc_search()
	{
		doc_spc_bx->clear();


		wstring speciality = doc_bx->currentText().value();

		string sspeciality(speciality.begin(), speciality.end());

		for (auto iter : docs)
		{
			wstring s = iter->getSpeciality().value();
			string ss(s.begin(), s.end());
			if (!strncmp(sspeciality.c_str() ,ss.c_str(),sspeciality.size()))
			{
				WString name ="";
				name += iter->getName();
				name += " ";
				name += iter->getFamily();
				doc_spc_bx->addItem(name);
				doc_spc_bx_item++;
			}
		}
	}



	void res_canceled()
	{
		reserve_dlg->reject();
		name_led->setText("");
		family_led->setText("");
		age_led->setText("");
		details_led->setText("");
		gDoc_exp_led->setText("");
	}

	void reservation()
	{
		reserve_dlg->setClosable(true);

		reserve_dlg->setMinimumSize(750, 250);

		WLabel *name_lbl = new WLabel("Name");
		
		WVBoxLayout *name_lay = new WVBoxLayout();

		WLabel *family_lbl = new WLabel("Family");
		WVBoxLayout *family_lay = new WVBoxLayout();


		WLabel *emg_lbl = new WLabel("Emergency");
		WVBoxLayout *emg_lay = new WVBoxLayout();


		WLabel *age_lbl = new WLabel("Age");
		WVBoxLayout *age_lay = new WVBoxLayout();


		WLabel *ens_lbl = new WLabel("Insurance");
		WVBoxLayout *ens_lay = new WVBoxLayout();


		WLabel *gen_lbl = new WLabel("Male");
		WVBoxLayout *gen_lay = new WVBoxLayout();


		name_lbl->setMaximumSize(30, 30);
		name_led->setMaximumSize(125, 30);
		name_lay->addWidget(name_lbl, 1);
		name_lay->addWidget(name_led, 5);

		family_lbl->setMaximumSize(30, 30);
		family_led->setMaximumSize(125, 30);
		family_lay->addWidget(family_lbl, 1);
		family_lay->addWidget(family_led, 5);

		emg_lbl->setMaximumSize(80, 80);
		emg_btn->setMaximumSize(20, 20);
		emg_lay->addWidget(emg_lbl, 1);
		emg_lay->addWidget(emg_btn, 5);

		age_lbl->setMaximumSize(30, 30);
		age_led->setMaximumSize(60, 30);
		age_lay->addWidget(age_lbl, 1);
		age_lay->addWidget(age_led, 5);

		ens_lbl->setMaximumSize(70, 70);
		ens_btn->setMaximumSize(20, 20);
		ens_lay->addWidget(ens_lbl, 1);
		ens_lay->addWidget(ens_btn, 5);

		gen_lbl->setMaximumSize(30, 30);
		gen_btn->setMaximumSize(20, 20);
		gen_lay->addWidget(gen_lbl, 1);
		gen_lay->addWidget(gen_btn, 5);

		WGridLayout *h_lay2 = new WGridLayout(reserve_dlg->contents());

		h_lay2->addItem(name_lay, 1, 1);
		h_lay2->addLayout(family_lay, 1, 2);
		h_lay2->addLayout(emg_lay, 1, 3);
		h_lay2->addLayout(age_lay, 1, 4);
		h_lay2->addLayout(ens_lay, 1, 5);
		h_lay2->addLayout(gen_lay, 1, 6);


		WLabel *details = new WLabel("Details");
		WVBoxLayout *details_lay = new WVBoxLayout();

		details->setMaximumSize(30, 30);
		details_led->setMaximumSize(720, 30);
		details_lay->addWidget(details);
		details_lay->addWidget(details_led);

		h_lay2->addItem(details_lay, 3, 1);
		h_lay2->addWidget(ens_ok, 4, 1);
		h_lay2->addWidget(ens_cancel, 4, 2);

		//General
		if (doc_bx->currentText() == "General")
		{

			//general doctor special parts
			WLabel *gDoc_lbl = new WLabel("Experiment");
			WVBoxLayout *gDoc_lay = new WVBoxLayout();


			gDoc_lbl->setMaximumSize(30, 30);
			gDoc_exp_led->setMaximumSize(360, 30);
			gDoc_lay->addWidget(gDoc_lbl, 1);
			gDoc_lay->addWidget(gDoc_exp_led, 5);

			h_lay2->addItem(gDoc_lay, 2, 1);
		}

		//dental
		if (doc_bx->currentText() == "Dentist")
		{
			WLabel *Dent_serv_lbl = new WLabel("Dental services");
			WVBoxLayout *Dent_serv_lay = new WVBoxLayout();
			WLabel *Dent_pic_lbl = new WLabel("Picture");
			WVBoxLayout *Dent_pic_lay = new WVBoxLayout();

			Dent_serv_lbl->setMaximumSize(50, 30);

			Dent_serv_led->setMaximumSize(120, 30);
			Dent_serv_lay->addWidget(Dent_serv_lbl, 1);
			Dent_serv_lay->addWidget(Dent_serv_led, 5);

			Dent_pic_lbl->setMaximumSize(30, 30);
			Dent_pic_btn->setMaximumSize(20, 20);
			Dent_pic_lay->addWidget(Dent_pic_lbl, 1);
			Dent_pic_lay->addWidget(Dent_pic_btn, 5);

			h_lay2->addItem(Dent_serv_lay, 2, 1);
			h_lay2->addItem(Dent_pic_lay, 2, 2);
		}

		//heart
		if (doc_bx->currentText() == "Heart")
		{
			WLabel *hDoc_op_his_lbl = new WLabel("Ex_operaiton");
			WVBoxLayout *hDoc_op_his_lay = new WVBoxLayout();

			WLabel *hDoc_angio_lbl = new WLabel("Angiography");
			WVBoxLayout *hDoc_angio_lay = new WVBoxLayout();

			WLabel *hDoc_fail_lbl = new WLabel("failure");
			WVBoxLayout *hDoc_fail_lay = new WVBoxLayout();

			hDoc_op_his_lbl->setMaximumSize(30, 30);
			hDoc_op_his_btn->setMaximumSize(20, 20);
			hDoc_op_his_lay->addWidget(hDoc_op_his_lbl, 1);
			hDoc_op_his_lay->addWidget(hDoc_op_his_btn, 5);

			hDoc_fail_lbl->setMaximumSize(30, 30);
			hDoc_fail_btn->setMaximumSize(20, 20);
			hDoc_fail_lay->addWidget(hDoc_fail_lbl, 1);
			hDoc_fail_lay->addWidget(hDoc_fail_btn, 5);

			hDoc_angio_lbl->setMaximumSize(30, 30);
			hDoc_angio_btn->setMaximumSize(20, 20);
			hDoc_angio_lay->addWidget(hDoc_angio_lbl, 1);
			hDoc_angio_lay->addWidget(hDoc_angio_btn, 5);

			h_lay2->addItem(hDoc_angio_lay, 2, 1);
			h_lay2->addItem(hDoc_op_his_lay, 2, 2);
			h_lay2->addItem(hDoc_fail_lay, 2, 3);
		}

		//women
		if (doc_bx->currentText() == "Women")
		{
			WLabel *women_pre_lbl = new WLabel("pregnancy");
			WVBoxLayout *women_pre_lay = new WVBoxLayout();


			women_pre_lbl->setMaximumSize(30, 30);
			women_pre_btn->setMaximumSize(20, 20);
			women_pre_lay->addWidget(women_pre_lbl, 1);
			women_pre_lay->addWidget(women_pre_btn, 5);

			h_lay2->addItem(women_pre_lay, 2, 1);
		}

		//hair_skin
		if (doc_bx->currentText() == "Hair & skin")
		{
			WLabel *hair_lbl = new WLabel("Hair");
			WVBoxLayout *hair_lay = new WVBoxLayout();

			WLabel *skin_lbl = new WLabel("Skin");
			WVBoxLayout *skin_lay = new WVBoxLayout();

			WLabel *hair_comp_lbl = new WLabel("General complain");
			WVBoxLayout *hair_comp_lay = new WVBoxLayout();

			hair_lbl->setMaximumSize(30, 30);
			hair_btn->setMaximumSize(20, 20);
			hair_lay->addWidget(hair_lbl, 1);
			hair_lay->addWidget(hair_btn, 5);

			skin_lbl->setMaximumSize(30, 30);
			skin_btn->setMaximumSize(20, 20);
			skin_lay->addWidget(skin_lbl, 1);
			skin_lay->addWidget(skin_btn, 5);

			hair_comp_lbl->setMaximumSize(30, 30);
			hair_comp_led->setMaximumSize(360, 30);
			hair_comp_lay->addWidget(hair_comp_lbl, 1);
			hair_comp_lay->addWidget(hair_comp_led, 5);

			h_lay2->addItem(hair_lay, 2, 1);
			h_lay2->addItem(skin_lay, 2, 2);
			h_lay2->addItem(hair_comp_lay, 2, 3);
		}

		//internal
		if (doc_bx->currentText() == "Internal")
		{
			WLabel *internal_org_lbl = new WLabel("Organ");
			WVBoxLayout *internal_org_lay = new WVBoxLayout();

			internal_org_lbl->setMaximumSize(30, 30);
			internal_org_led->setMaximumSize(360, 30);
			internal_org_lay->addWidget(internal_org_lbl, 1);
			internal_org_lay->addWidget(internal_org_led, 5);

			h_lay2->addItem(internal_org_lay, 2, 1);
		}

		//orthopedics
		if (doc_bx->currentText() == "Orthopedics")
		{
			WLabel *orth_org_lbl = new WLabel("Organ");
			WVBoxLayout *orth_org_lay = new WVBoxLayout();

			WLabel *orth_brk_lbl = new WLabel("Breakness");
			WVBoxLayout *orth_brk_lay = new WVBoxLayout();

			orth_org_lbl->setMaximumSize(30, 30);
			orth_org_led->setMaximumSize(360, 30);
			orth_org_lay->addWidget(orth_org_lbl, 1);
			orth_org_lay->addWidget(orth_org_led, 5);

			orth_brk_lbl->setMaximumSize(30, 30);
			orth_brk_btn->setMaximumSize(20, 20);
			orth_brk_lay->addWidget(orth_brk_lbl, 1);
			orth_brk_lay->addWidget(orth_brk_btn, 5);

			h_lay2->addItem(orth_org_lay, 2, 1);
			h_lay2->addItem(orth_brk_lay, 2, 1);
		}

		if (doc_bx->currentText() == "Eye")
		{
			WLabel *eye_chk_lbl = new WLabel("Check-up");
			WVBoxLayout *eye_chk_lay = new WVBoxLayout();

			WLabel *eye_glass_lbl = new WLabel("Eyeglasses");
			WVBoxLayout *eye_glass_lay = new WVBoxLayout();

			WLabel *eye_lense_lbl = new WLabel("Lenses");
			WVBoxLayout *eye_lense_lay = new WVBoxLayout();

			eye_chk_lbl->setMaximumSize(30, 30);
			eye_chk_btn->setMaximumSize(20, 20);
			eye_chk_lay->addWidget(eye_chk_lbl, 1);
			eye_chk_lay->addWidget(eye_chk_btn, 5);

			eye_glass_lbl->setMaximumSize(30, 30);
			eye_glass_btn->setMaximumSize(20, 20);
			eye_glass_lay->addWidget(eye_glass_lbl, 1);
			eye_glass_lay->addWidget(eye_glass_btn, 5);

			eye_lense_lbl->setMaximumSize(30, 30);
			eye_lense_btn->setMaximumSize(20, 20);
			eye_lense_lay->addWidget(eye_lense_lbl, 1);
			eye_lense_lay->addWidget(eye_lense_btn, 5);

			h_lay2->addItem(eye_chk_lay, 2, 1);
			h_lay2->addItem(eye_glass_lay, 2, 2);
			h_lay2->addItem(eye_lense_lay, 2, 3);
		}

		//EThN
		if (doc_bx->currentText() == "EThN")
		{
			WLabel *ethn_ear_lbl = new WLabel("Ear");
			WVBoxLayout *ethn_ear_lay = new WVBoxLayout();

			WLabel *ethn_nose_lbl = new WLabel("Nose");
			WVBoxLayout *ethn_nose_lay = new WVBoxLayout();

			WLabel *ethn_throat_lbl = new WLabel("Throat");
			WVBoxLayout *ethn_throat_lay = new WVBoxLayout();

			ethn_ear_lbl->setMaximumSize(30, 30);
			ethn_ear_btn->setMaximumSize(20, 20);
			ethn_ear_lay->addWidget(ethn_ear_lbl, 1);
			ethn_ear_lay->addWidget(ethn_ear_btn, 5);

			ethn_nose_lbl->setMaximumSize(30, 30);
			ethn_nose_btn->setMaximumSize(20, 20);
			ethn_nose_lay->addWidget(ethn_nose_lbl, 1);
			ethn_nose_lay->addWidget(ethn_nose_btn, 5);

			ethn_throat_lbl->setMaximumSize(30, 30);
			ethn_throat_btn->setMaximumSize(20, 20);
			ethn_throat_lay->addWidget(ethn_throat_lbl, 1);
			ethn_throat_lay->addWidget(ethn_throat_btn, 5);


			h_lay2->addItem(ethn_ear_lay, 2, 1);
			h_lay2->addItem(ethn_nose_lay, 2, 1);
			h_lay2->addItem(ethn_throat_lay, 2, 1);
		}

		//Nuero
		if (doc_bx->currentText() == "Nuero")
		{
			WLabel *nue_ct_lbl = new WLabel("CTscan");
			WVBoxLayout *nue_ct_lay = new WVBoxLayout();

			nue_ct_lbl->setMaximumSize(30, 30);
			nue_ct_btn->setMaximumSize(20, 20);
			nue_ct_lay->addWidget(nue_ct_lbl, 1);
			nue_ct_lay->addWidget(nue_ct_btn, 5);

			h_lay2->addItem(nue_ct_lay, 2, 1);
		}


		reserve_dlg->exec();
	}


	void ens_accepted()
	{
		reserve_dlg->accept();
		WString name = name_led->text();
		WString family = family_led->text();
		int age = age_led->value();
		bool emergency = emg_btn->isChecked();
		bool insurance = ens_btn->isChecked();
		bool gender = gen_btn->isChecked();
		WString details;
		WString date = dates_bx->currentText();

		Doctor *myDoc = new Doctor("", "", "", 0, 0,false);

		if (doc_bx->currentText() == "General") {
			for (auto doc : docs)
			{
				wstring speciality = doc_bx->currentText().value();

				string sspeciality(speciality.begin(), speciality.end());

				wstring s = doc->getSpeciality().value();
				
				string ss(s.begin(), s.end());

				WString  doc_name = (doc->getName() + " " + doc->getFamily());

				if (doc_name == doc_spc_bx->currentText() && !strncmp(sspeciality.c_str(), ss.c_str(), sspeciality.size()))
				{
					myDoc = doc;
					break;
				}
			}
			WString exp = gDoc_exp_led->text();
			General_P x(name, family, age, emergency, *myDoc, insurance, gender, details, exp);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Dentist") {
			WString dental_service = Dent_serv_led->text();
			bool pic = Dent_pic_btn->isChecked();
			
			for (auto doc : docs)
				{
					wstring speciality = doc_bx->currentText().value();

					string sspeciality(speciality.begin(), speciality.end());

					wstring s = doc->getSpeciality().value();

					string ss(s.begin(), s.end());

					WString  doc_name = (doc->getName() + " " + doc->getFamily());

					if (doc_name == doc_spc_bx->currentText() && !strncmp(sspeciality.c_str(), ss.c_str(), sspeciality.size()))

				{
					myDoc = doc;
					break;
				}
			}
			Dental_P x(name, family, age, emergency, *myDoc, insurance, gender, details, dental_service, pic);
			x.final_appointment(WDateTime::fromString(date));
			sucsessfull(x);
		}
		else if (doc_bx->currentText() == "Heart") {
			bool op_his = hDoc_op_his_btn->isChecked();
			bool failure = hDoc_fail_btn->isChecked();
			bool angio = hDoc_angio_btn->isChecked();

			for (auto doc : docs)
			{
				wstring speciality = doc_bx->currentText().value();

				string sspeciality(speciality.begin(), speciality.end());

				wstring s = doc->getSpeciality().value();

				string ss(s.begin(), s.end());

				WString  doc_name = (doc->getName() + " " + doc->getFamily());

				if (doc_name == doc_spc_bx->currentText() && !strncmp(sspeciality.c_str(), ss.c_str(), sspeciality.size()))
			{
					myDoc = doc;
					break;
			}
			}
			Heart_P x(name, family, age, emergency, *myDoc, insurance, gender, details, op_his, angio, failure);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Women") {
			bool pregnancy = women_pre_btn->isChecked();
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Women")
				{
					myDoc = doc;
					break;
				}
			}
			Women_P x(name, family, age, emergency, *myDoc, insurance, gender, details, pregnancy);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Hair & skin") {
			int hs = skin_btn->isChecked();
			WString general_comp;
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Hair & skin")
				{
					myDoc = doc;
					break;
				}
			}
			HairSkin_P x(name, family, age, emergency, *myDoc, insurance, gender, details, hs, general_comp);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Internal") {
			WString organ = internal_org_led->text();
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Internal")
				{
					myDoc = doc;
					break;
				}
			}
			Internal_P x(name, family, age, emergency, *myDoc, insurance, gender, details, organ);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Orthopedics") {
			WString organ = orth_org_led->text();
			bool breakness = orth_brk_btn->isChecked();
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Orthopedics")
				{
					myDoc = doc;
					break;
				}
			}
			Orthopedics_P x(name, family, age, emergency, *myDoc, insurance, gender, details, organ, breakness);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Eye") {
			bool eyeglasses = eye_glass_btn->isChecked();
			bool checkup = eye_chk_btn->isChecked();
			bool lense = eye_lense_btn->isChecked();
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Eye")
				{
					myDoc = doc;
					break;
				}
			}
			Eye_P x(name, family, age, emergency, *myDoc, insurance, gender, details, checkup, eyeglasses, lense);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "EThN") {
			int which;
			if (ethn_ear_btn->isChecked())
				which = 1;
			else if (ethn_nose_btn->isChecked())
				which = 2;
			else if (ethn_throat_btn->isChecked())
				which = 3;

			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "EThN")
				{
					myDoc = doc;
					break;
				}
			}
			EThN_P x(name, family, age, emergency, *myDoc, insurance, gender, details, which);
			x.final_appointment(WDateTime::fromString(date));
		}
		else if (doc_bx->currentText() == "Nuero") {
			bool ctscan = nue_ct_btn->isChecked();
			for (auto doc : docs)
			{
				if (doc->getName() == name && doc->getFamily() == family&&doc->getSpeciality() == "Nuero")
				{
					myDoc = doc;
					break;
				}
			}
			Neuro_P x(name, family, age, emergency, *myDoc, insurance, gender, details, ctscan);
			x.final_appointment(WDateTime::fromString(date));
		}


		name_led->setText("");
		family_led->setText("");
		age_led->setText("");
		details_led->setText("");
		gDoc_exp_led->setText("");



		return;
	}


	void constructing_docs() {
		fstream det_file("C:/doctors/doc1.d");
		fstream app_file("C:/doctors/doc1.a");
		while (det_file) {
			string line;
			getline(det_file, line);
			string fname;
			fname.resize(50);
			int i;
			for (i = 0; line[i] != '\t'; i++)
				fname[i] = line[i];
			
			fname.resize(i);
			i++;
			string lname;
			lname.resize(50);
			int j;
			for (j = 0; line[i] != '\t'; i++, j++)
				lname[j] = line[i];
		
			lname.resize(j);
			i++;
			string speciality;
			speciality.resize(50);
			for (j = 0; line[i] != '\t'; i++, j++)
				speciality[j] = line[i];
			
			speciality.resize(j);
			i++;
			string s_visit_tm;
			s_visit_tm.resize(50);
			for (j = 0; line[i] != '\t'; i++, j++)
				s_visit_tm[j] = line[i];
			s_visit_tm[j] = 0;
			i++;
			int visit_tm = stoi(s_visit_tm);
			string s_visit_pr;
			s_visit_pr.resize(50);
			for (j = 0; line[i] != 0; i++, j++)
				s_visit_pr[j] = line[i];
			s_visit_pr[j] = 0;
			i++;
			int visit_pr = stoi(s_visit_pr);
			Doctor *doc = new Doctor(fname, lname, speciality, visit_tm, visit_pr, false);
			while (getline(det_file, line) && line != "") {
				string s_wday;
				s_wday.resize(50);
				int i, j;
				for (i = 4, j = 0; line[i] != ' '; i++, j++)
					s_wday[j] = line[i];
				int wday;
				if (!strcmp(s_wday.c_str(), "Monday"))
					wday = 1;
				else if (!strcmp(s_wday.c_str(), "Tuesday"))
					wday = 2;
				else if (!strcmp(s_wday.c_str(), "Wednesday"))
					wday = 3;
				else if (!strcmp(s_wday.c_str(), "Thursday"))
					wday = 4;
				else if (!strcmp(s_wday.c_str(), "Friday"))
					wday = 5;
				else if (!strcmp(s_wday.c_str(), "Saturday"))
					wday = 6;
				else if (!strcmp(s_wday.c_str(), "Sunday"))
					wday = 7;
				i++;
				string s_stime;
				s_stime.resize(50);
				for (j = 0; line[i] != ' '; j++, i++) {
					s_stime[j] = line[i];
				}
				i++;
				string s_h;
				s_h.push_back(s_stime[0]);
				s_h.push_back(s_stime[1]);
				int h = stoi(s_h);
				string s_m;
				s_m.push_back(s_stime[3]);
				s_m.push_back(s_stime[4]);
				int m = stoi(s_m);
				string s_s;
				s_s.push_back(s_stime[6]);
				s_s.push_back(s_stime[7]);
				int s = stoi(s_s);
				WTime stime(h, m, s);
				string s_etime;
				s_etime.resize(50);
				for (j = 0; line[i] != 0; j++, i++) {
					s_etime[j] = line[i];
				}
				s_h.clear();
				s_h.push_back(s_etime[0]);
				s_h.push_back(s_etime[1]);
				h = stoi(s_h);
				s_m.clear();
				s_m.push_back(s_etime[3]);
				s_m.push_back(s_etime[4]);
				m = stoi(s_m);
				s_s.clear();
				s_s.push_back(s_etime[6]);
				s_s.push_back(s_etime[7]);
				s = stoi(s_s);
				WTime etime(h, m, s);
				MyDate date(wday, stime, etime);
				if (line[0] == 'N')
					doc->addNP(date, 0);
				if (line[0] == 'E')
					doc->addEP(date, 0);
			}
			while (getline(app_file, line))
			{
				WDateTime appoint;
				appoint = WDateTime::fromString(line);
				doc->addApp(appoint);
			}
			docs.push_back(doc);
			ostringstream convert;
			convert << Doctor::getCnt() + 1;
			string det_name = "C:/doctors/doc" + convert.str() + ".d";
			string app_name = "C:/doctors/doc" + convert.str() + ".a";
			app_file.close();
			det_file.close();
			app_file.open(app_name, ios::_Nocreate);
			det_file.open(det_name, ios::_Nocreate);
		}
		return;
	}
};

WApplication * createApp(const WEnvironment & env)
{
	return new WtApp(env);
}

int main(int argc, char * argv[])
{

	return WRun(argc, argv, createApp);
}
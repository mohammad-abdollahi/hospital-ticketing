#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <vector>
#include <Wt/WApplication>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WVBoxLayout>
#include <Wt/WMessageBox>
#include <Wt/WBootstrapTheme>
#include <Wt/WPushButton>
#include <Wt/WTemplate>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include<Wt/WTable>
#include<Wt/WLink>
#include<Wt/WDialog>
#include<Wt/WGridLayout>
#include<Wt/WCheckBox>
#include <Wt/WHBoxLayout>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WSpinBox>
#include <Wt/WIntValidator>
#include <Wt/WTimeEdit>
#include <Wt/WGroupBox>
#include <Wt/WScrollArea>
#include <Wt/Wtime>
#include"TNode.h"
#include "doctor.h"
#include "mydate.h"
vector <TNode *> * vec = new vector <TNode *>;
int table_row = 1;
using namespace Wt;


unsigned int Doctor::doc_cnt = 0;



class WtApp : public WApplication
{
public:
	WTable *table = new WTable;
	WTimeEdit *VTime1 = new WTimeEdit;
	WPushButton *Add = new WPushButton;
	WPushButton *remove_btn = new WPushButton;
	WTimeEdit *VTime2 = new WTimeEdit;
	WLabel *error = new WLabel;
	WComboBox *week_cb = new WComboBox();
	WLineEdit *name_le = new WLineEdit;
	WComboBox *speciality_cb = new WComboBox();
	WSpinBox *Tpv_sb = new Wt::WSpinBox();
	WSpinBox *cost_le = new WSpinBox();
	WLineEdit * l_name = new WLineEdit;
	WCheckBox * EP_checkbox = new WCheckBox;
	WLabel *submit_error = new WLabel;


	WtApp(const WEnvironment & env)
		: WApplication(env)
	{
		Doctor::set_doc_cnt();
		//-----------------------------------------------------------------//
		this->setTitle("Admin");
		WVBoxLayout * menu_lay = new WVBoxLayout;
		//-------------------container----------------------------------//
		WContainerWidget *conteiner = new WContainerWidget;
		conteiner->setMaximumSize(WLength::Auto, WLength::Auto);
		//------------------"Adding doctor menu" label------------------//
		WGroupBox *title_lable = new WGroupBox("Adding Doctor Menu");
		conteiner->addWidget(title_lable);
		//------------------"Name" label-------------------------------//
		WLabel *menu_lable = new WLabel("First Name");
		conteiner->addWidget(menu_lable);
		//------------------"name" line edit ---------------------------//
		name_le->setMaximumSize(250, 32);
		name_le->setPlaceholderText("enter doctor first name");
		conteiner->addWidget(name_le);
		//----------------------last name ------------------------------//
		WLabel * l_name_label = new WLabel("Last Name");
		conteiner->addWidget(l_name_label);
		l_name->setMaximumSize(250, 32);
		l_name->setPlaceholderText("enter doctor last name");
		conteiner->addWidget(l_name);
		//--------------------"Speciality" label------------------------//
		WLabel *speciality_lable = new WLabel("Speciality");
		conteiner->addWidget(speciality_lable);
		//-------------------speciality Dropdown menu-------------------//
		speciality_cb->setMaximumSize(250, 32);
		speciality_cb->setNoSelectionEnabled(true);//no item selected by default

		speciality_cb->addItem("Dentist");
		speciality_cb->addItem("General");
		speciality_cb->addItem("Heart");
		speciality_cb->addItem("Neuro");
		speciality_cb->addItem("EThN");
		speciality_cb->addItem("Women");
		speciality_cb->addItem("Hair & skin");
		speciality_cb->addItem("Internal");
		speciality_cb->addItem("Orthapedics");
		speciality_cb->addItem("Eye");

		conteiner->addWidget(speciality_cb);
		//------------------"Time per visit" label------------------------//
		WLabel *Tpv_lable = new WLabel("Time per visit (minutes)");
		conteiner->addWidget(Tpv_lable);
		//---------------------Time per visit---------------------//
		Tpv_sb->setMaximumSize(150, 32);
		Tpv_sb->setRange(0, 120);
		conteiner->addWidget(Tpv_sb);
		//-------------------"The cost of each visit" label-------------------//
		WLabel *cost_lable = new WLabel("The cost of each visit");
		conteiner->addWidget(cost_lable);
		//-------------------cost line edit------------------------------//
		cost_le->setMaximumSize(150, 32);
		cost_le->setRange(0, 10000000);
		conteiner->addWidget(cost_le);
		conteiner->addWidget(new Wt::WText("<br></br>"));

		//-------------------"Visit days" label---------------------------------//
		WLabel *vd_lable = new WLabel("Visit days");
		conteiner->addWidget(vd_lable);
		//--------------------visit days menu-------------------------------//
		//combo box
		week_cb->setMaximumSize(250, 32);
		week_cb->setNoSelectionEnabled(true);
		week_cb->addItem("Saturday");
		week_cb->addItem("Sunday");
		week_cb->addItem("Monday");
		week_cb->addItem("Tuesrday");
		week_cb->addItem("Wednesday");
		week_cb->addItem("Thirsday");
		week_cb->addItem("Friday");
		conteiner->addWidget(week_cb);
		WLabel *VT1_lable = new WLabel();//"From:" label
		VT1_lable->setText("From:");
		conteiner->addWidget(VT1_lable);
		//time 1 line edit
		VTime1->setFormat("h:mm:00");
		VTime1->setMaximumSize(250, 32);
		VTime1->setTime(Wt::WTime::currentTime());
		VTime1->setReadOnly(1);
		conteiner->addWidget(VTime1);
		WLabel *VT2_lable = new WLabel();//"To:" label
		VT2_lable->setText("To:");
		conteiner->addWidget(VT2_lable);
		//time 2 line edit
		VTime2->setFormat("h:mm:00");
		VTime2->setMaximumSize(250, 32);
		VTime2->setTime(Wt::WTime::currentTime());
		VTime2->setReadOnly(1);
		conteiner->addWidget(VTime2);
		conteiner->addWidget(new Wt::WText("<br></br>"));
		//EP checkbox
		EP_checkbox->setText("Emergency presence");
		conteiner->addWidget(EP_checkbox);
		conteiner->addWidget(new Wt::WText("<br></br>"));
		//add button
		Add->setText("Add to Table");
		Add->setMaximumSize(150, 50);
		Add->setIcon("add_green.png");
		Add->clicked().connect(this, &WtApp::add_clicked);
		conteiner->addWidget(Add);
		//hidden error label
		error->setHidden(1);
		conteiner->addWidget(error);
		//remove bottun decleration
		conteiner->addWidget(new Wt::WText("<br></br>"));
		conteiner->addWidget(new Wt::WText("<br></br>"));
		remove_btn->setText("remove last!");
		remove_btn->setMaximumSize(150, 50);
		remove_btn->clicked().connect(std::bind([=]() {
			if (vec->empty()) {
				return;
			}
			int a = table->rowCount() - 1;
			table->deleteRow(a);
			vec->pop_back();
			table_row--;
		}));
		conteiner->addWidget(remove_btn);

		//table

		table->addStyleClass("table form-inline");
		table->setHeaderCount(1);
		table->elementAt(0, 1)->addWidget(new WText("Weekday"));
		table->elementAt(0, 2)->addWidget(new WText("Begining time"));
		table->elementAt(0, 3)->addWidget(new WText("Ending time"));
		table->setLineHeight(50);
		conteiner->addWidget(new Wt::WText("<br></br>"));
		conteiner->addWidget(table);
		//tablescroler
		WScrollArea * table_scroller = new WScrollArea;
		table_scroller->setWidget(table);
		table_scroller->setMinimumSize(900, 250);
		table_scroller->setMaximumSize(900, 250);
		table_scroller->setScrollVisibilityEnabled(1);
		conteiner->addWidget(table_scroller);
		//-----------------------submit error ----------------------------//
		submit_error->setHidden(1);
		conteiner->addWidget(submit_error);
		conteiner->addWidget(new Wt::WText("<br></br>"));
		//-----------------------submit button---------------------------//
		WPushButton * submit_button = new WPushButton;
		submit_button->setText("Submit!");  
		submit_button->setMaximumSize(150, 50);
		submit_button->clicked().connect(this, &WtApp::submit_clicked);
		conteiner->addWidget(submit_button);
		//----------------------scroll manage----------------------------//

		WScrollArea * scroller = new WScrollArea;
		scroller->setWidget(conteiner);
		scroller->setMaximumSize(2000, 2500);
		scroller->setScrollVisibilityEnabled(1);
		menu_lay->addWidget(scroller);


		//------------------ menu layout---------------------------------//
		root()->setLayout(menu_lay);
		menu_lay->addStretch(2);

		////////////////////////////////////////////////////////////set theme

		WBootstrapTheme *bootstrapTheme = new WBootstrapTheme(this);
		bootstrapTheme->setVersion(WBootstrapTheme::Version3);
		bootstrapTheme->setResponsive(true);
		this->setTheme(bootstrapTheme);
		useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");


		return;
	}


private:
	
	void submit_clicked() {

		if(!name_le->textSize() || !l_name->textSize()|| vec->empty()){
			submit_error->setText("name labels or time table can not be empty");
			submit_error->setHidden(0);
			return;
		}
		if (speciality_cb->currentIndex() == -1 || week_cb->currentIndex() == -1) {
			submit_error->setText("doctor speciality and weekday must be chosen");
			submit_error->setHidden(0);
			return;
		}
		Doctor * doc = new Doctor(name_le->text(), l_name->text(), speciality_cb->currentText(), Tpv_sb->value(), cost_le->value());
		for (int i = 0; i < vec->size(); i++) {
			WTime *tmp_time1 = new WTime(vec->at(i)->hour, vec->at(i)->minute);
			WTime *tmp_time2 = new WTime(vec->at(i)->hour2, vec->at(i)->minute2);
			MyDate *tmp_date = new MyDate(vec->at(i)->week_day, *tmp_time1, *tmp_time2);
			
			if (vec->at(i)->is_EP)
				doc->addEP(*tmp_date);
			else
				doc->addNP(*tmp_date);
			name_le->setText("");
			l_name->setText("");
			speciality_cb->setNoSelectionEnabled(true);
			week_cb->setNoSelectionEnabled(true);
			cost_le->setValue(0);
			week_cb->setCurrentIndex(0);
			VTime1->setTime(Wt::WTime::currentTime());
			VTime2->setTime(Wt::WTime::currentTime());
			table->clear();
			table_row = 1;
			table->setHeaderCount(1);
			table->elementAt(0, 1)->addWidget(new WText("Weekday"));
			table->elementAt(0, 2)->addWidget(new WText("Begining time"));
			table->elementAt(0, 3)->addWidget(new WText("Ending time"));
			vec->clear();
		}
	}
	bool interferene_when(int hour, int minute, int hour2, int minute2, int week_day_int) {
		if (vec->empty())
			return 0;
		for (int counter = 0; counter < vec->size() ; counter++) {
			if (vec->at(counter)->week_day = week_day_int) {
				if (vec->at(counter)->hour * 60 + vec->at(counter)->minute <= hour * 60 + minute && vec->at(counter)->hour2 * 60 + vec->at(counter)->minute2 >= hour * 60 + minute) {
					return 1;
				}
				if (vec->at(counter)->hour * 60 + vec->at(counter)->minute <= hour2 * 60 + minute2 && vec->at(counter)->hour2 * 60 + vec->at(counter)->minute2 >= hour2 * 60 + minute2) {
					return 1;
				}
				if (vec->at(counter)->hour * 60 + vec->at(counter)->minute >= hour * 60 + minute && vec->at(counter)->hour2 * 60 + vec->at(counter)->minute2 <= hour2 * 60 + minute2) {
					return 1;
				}
			}
		}
		return 0;
	}
	
	void add_clicked() {
		if (VTime1->time().hour()*60 + VTime1->time().minute() >= VTime2->time().hour() * 60 + VTime2->time().minute()) {
			error->setText("begining time can not be later than ending time or the same!");
			error->setHidden(0);
			return;
		}
		else if (interferene_when(VTime1->time().hour(), VTime1->time().minute(), VTime2->time().hour(), VTime2->time().minute(), TNode::week_day_cal(week_cb->currentText())))
		{
			error->setText("interferene when occured");
			error->setHidden(0);
			return;
		}
		else {
			error->setHidden(1);
		}
		TNode *tmp = new TNode(VTime1->time().hour(), VTime1->time().minute(), VTime2->time().hour(), VTime2->time().minute(), week_cb->currentText(), VTime1->text(), VTime2->text(), table_row, EP_checkbox->isChecked());
		vec->push_back(tmp);
		table->elementAt(table_row, 1)->addWidget(new Wt::WText(week_cb->currentText()));
		table->elementAt(table_row, 2)->addWidget(new WText(VTime1->text()));
		table->elementAt(table_row, 3)->addWidget(new WText(VTime2->text()));
		table_row++;
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
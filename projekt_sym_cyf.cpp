// projekt_sym_cyf.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <list>
#include <fstream>
#include "BloodBank.h"
#include "Calendar.h"
#include "DonationByDose.h"
#include "SendingBloodOrder.h"
#include "AppearanceOfRecipient.h"
#include <conio.h>
#include "Distribution.h"
#include "DEBUG.h"

void Simulate();
void Test();
void write_state(fstream &state, int time_system, int number_of_recipients_served, int number_of_blood_spent, int act_length_queue_of_recipients, bool act_emergency_order, int j,int kernel);
char buff[100000];
int main() {
	std::cout << "Please choose the taks: 1-Simulate, 2-Test" << endl;
	int choose;
	cin >> choose;
	switch(choose)
	{
	case 1:
		Simulate();
		break;
	case 2:
		Test();
		break;
	}
	char z = '0';
	std::cout << "Please click escape to exit " << endl;
	while (!(z == 27))	//czekanie na wciśniecie ENTER
	{
		z = _getch();
	}
	return 0;
}
void Simulate()
{
	bool repeat = true;
	BloodBank *blood_bank = new BloodBank(5, 0, 10, 55000);

	blood_bank->calendar_->AddSortTimeCondition(new AppearanceOfRecipient("Pierwszy",blood_bank,0));
	blood_bank->calendar_->AddSortTimeCondition(new DonationByDose(blood_bank, 0));

	//Ustawienie warunków końca symulacji
	std::cout << "Please check end condition: 1-number of recipients served, 2-number of blood spent." << endl;
	int end_condition;
	cin >> end_condition;
	int end_number;
	switch(end_condition)
	{
	case 1:
		std::cout << "Please write number of recipients served " << endl;
		cin >> end_number;
		break;
	case 2:
		std::cout << "Please write number of blood spent " << endl;
		cin >> end_number;
		break;
	}


	if (DEBUG)std::cout << "System time: " << blood_bank->calendar_->get_time_system() << " State: blood_units= " << blood_bank->J << ", recipien_in_queue= " << blood_bank->queue_recipients_size() << ", handled_recipients=" << blood_bank->get_handled_recipients() << "." << std::endl;
	std::cout << "Start symulation ->" << endl;
	char z = '0';
	int old_time = 0;																																																																																																																	
	int old_event = 0;
	fstream state("state_simulation.txt", ios::out);
	for (list<TimeCondition*>::iterator i = blood_bank->calendar_->calendar.begin(); i != blood_bank->calendar_->calendar.end(); ++i) {
		blood_bank->calendar_->set_time_System((*i)->get_execution_time());
		if (old_time < blood_bank->calendar_->get_time_system())	//system usuwania przestarzałych zdarzeń 
		{
			for(int i=0;i<old_event;i++)
			{
				blood_bank->calendar_->DeleteTimeConditionFirst();
			}
			old_event = 0;
		}else old_event++;
		
		old_time = blood_bank->calendar_->get_time_system();
		if (STEP)
		{
			while (!(z == 13))	//czekanie na wciśniecie ENTER
			{
				z = _getch();
			}z = 'O';

		}
		if (DEBUG)std::cout << "////////////////////////////////////////" << std::endl;
		if (DEBUG)std::cout << "System time: " << blood_bank->calendar_->get_time_system() << " State: blood_units= " << blood_bank->J << ", recipien_in_queue= " << blood_bank->queue_recipients_size() <<", handled_recipients="<<blood_bank->get_handled_recipients()<<"."<< std::endl;
		if (DEBUG)std::cout << "->";
		(*i)->ReadName();
		(*i)->Execute(blood_bank);
		//IfConditions
		do
		{
			repeat = false;

			if (blood_bank->J < blood_bank->get_R() && !(blood_bank->NO))
			{
				blood_bank->calendar_->AddSortTimeCondition(new SendingBloodOrder("Normal Order", blood_bank, 5, true));
				blood_bank->NO = true;
				if(DEBUG)std::cout << "If Condition: Normal" << std::endl;
				blood_bank->inc_s_c();
				repeat = true;
			}

			if (blood_bank->queue_recipients_size() > 0)	//obsługa pierwszego w kolejce
			{
				if (blood_bank->J >= blood_bank->get_first_recipient()->A)
				{
					for(int i=0;i<blood_bank->get_first_recipient()->A;i++)
					{
						if(blood_bank->deleteFirstUnitsOfBlood())blood_bank->number_of_blood_spent++;
						else
						{
							if(DEBUG)std::cout << "ERROR. Not delete first unit of blood." << std::endl;
						}
						
					}
					if (DEBUG)std::cout << "First recipient servised" << std::endl;
					blood_bank->DeleteFirstQueue();
					blood_bank->number_of_recipients_served++;
					repeat = true;
				}
				else  //ponów próbę transfuzji krwi w natępnej iteracji kalendarza
				{
					if(DEBUG)std::cout << "WAIT FOR UnitOfBlood !!!" << std::endl;
					if (!(blood_bank->EO))
					{
						blood_bank->inc_s_c();
						blood_bank->inc_s_e();
						blood_bank->calendar_->AddSortTimeCondition(new SendingBloodOrder("Emergency Order", blood_bank, blood_bank->calendar_->get_time_system(), false));
						blood_bank->EO = true;
						if(DEBUG)std::cout << "If Condition: Emergency" << std::endl;
						repeat = false;
					}
				}
			}
			
			if (DEBUG)std::cout << std::endl;
		} while (repeat);

		//std::cout << "number_of_recipients_served=" << blood_bank->number_of_recipients_served << "	number_of_blood_spent=" << blood_bank->number_of_blood_spent << "	length_of_longest_recipient_queue=" << blood_bank->length_of_longest_recipient_queue << std::endl;
		write_state(state, blood_bank->calendar_->get_time_system(), blood_bank->number_of_recipients_served, blood_bank->number_of_blood_spent, blood_bank->queue_recipients_size(), blood_bank->EO, blood_bank->J,blood_bank->get_generate()->get_kernel());
		//Warunki końca
		if ((end_condition ) == 1 && blood_bank->number_of_recipients_served >= end_number) break;
		if ((end_condition ) == 2 && blood_bank->number_of_blood_spent >= end_number) break;

		

	}
	std::cout << "End symulation" << endl;
	blood_bank->ReadList();
	blood_bank->calendar_->ReadCalendar();

	std::cout << "State: number_of_recipients_served=" << blood_bank->number_of_recipients_served << "	number_of_blood_spent=" << blood_bank->number_of_blood_spent <<"	length_of_longest_recipient_queue=" <<blood_bank->length_of_longest_recipient_queue << std::endl;
	double p_e = (static_cast<double>(blood_bank->get_s_e()) / static_cast<double>(blood_bank->get_s_c()))*100.0 ;
	std::cout << "Probability of send emergency order is equal " <<p_e << "%." << endl;

	double p_u = (static_cast<double>(blood_bank->get_s_u()) / static_cast<double>(blood_bank->get_s_u() + blood_bank->number_of_blood_spent))*100.0 ;
	std::cout << "Probability of Utilization blood is equal " << p_u << " %." << endl;
	state.close();
}



void Test()
{
	std::cout << "Please choose the generation method 1-EvenGenerator, 2-ExponentialGenerator, 3-NormalGenerator, 4-GeometricGenerator." << endl;
	int dis;
	cin >> dis;
	std::cout << "Please  write the number of iterations." << endl;
	int iter;
	cin >> iter;
	std::cout << "Please  write the number of kernel. Simulation for 55000" << endl;
	int kernel;
	cin >> kernel;

	Distribution generate(kernel);

	fstream plik("distribution_data.txt", ios::out);
	int v=0;
	double d=0;

	
	if (plik.good())
	{
		for (int i = 0; i < iter; i++)
		{
			switch(dis)
			{
			case 1:
				v = generate.EvenGenerator(0, 10);
				plik << v << '\n';
				break;
			case 2:
				d = generate.ExponentialGenerator(1800);	//1800
				plik << d << '\n';
				break;
			case 3:
				d = generate.NormalGenerator(300, 1);
				d = round(d);
				plik << static_cast<int>(d) << '\n';
				break;
			case 4:
				d = generate.GeometricGenerator(1/0.22);
				plik << d << '\n';
				break;
				}
			
		}
	}
	plik.close();
	std::cout << "Data has been saved to file distribution_data.txt"<< endl;
	
}

void write_state(fstream &state, int time_system, int number_of_recipients_served, int number_of_blood_spent, int act_length_queue_of_recipients, bool act_emergency_order, int j,int kernel) 
{
	state << time_system << "	" << number_of_recipients_served << "	" << number_of_blood_spent << "	" << act_length_queue_of_recipients << "	" << act_emergency_order <<"	"<<j<<"	"<<kernel<<'\n';
}


//tryb debagowania (pojawianie się co się dzieje po kolei oraz tryb krokowy załączamy poprzez dyrektywę w DEBUG.h
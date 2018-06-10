#include "stdafx.h"
#include <iostream>
#include "AppearanceOfRecipient.h"
#include "Recipients.h"
#include "DEBUG.h"
#include "Calendar.h"
#include <string>
#include "Distribution.h"

AppearanceOfRecipient::AppearanceOfRecipient(string name, BloodBank* blood_bank, int t0):TimeCondition(name, blood_bank, t0)
{
}


void AppearanceOfRecipient::Execute(BloodBank* blood_bank)
{
	
	int need = blood_bank->get_generate()->GeometricGenerator(1 / t_g_); //zmienna która bêdzie brana z generatora
	int time = static_cast<int>(round(blood_bank->get_generate()->ExponentialGenerator(p_g_)));
	if (time == 0)time++;
	if (DEBUG)std::cout << "Add receipien to queue who need " << std::to_string(need) << " unit of blood. Nest is planing at " << time<<" ."<< std::endl;
	blood_bank->inc_handled_recipients();
	blood_bank->GettingToQueue(new Recipients(need));
	if(blood_bank->length_of_longest_recipient_queue < blood_bank->queue_recipients_size())	//zapisaywanie maksymalnej d³ugoœci kolejki
	{
		blood_bank->length_of_longest_recipient_queue = blood_bank->queue_recipients_size();
	}
	//iteracja iloœci pacjentów którzy weszli do banku krwi
	blood_bank->calendar_->AddSortTimeCondition(new AppearanceOfRecipient("Planing add to queue.", blood_bank, time+ blood_bank->calendar_->get_time_system()));
}
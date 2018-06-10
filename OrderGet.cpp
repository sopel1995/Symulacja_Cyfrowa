#include "stdafx.h"
#include "OrderGet.h"
#include "Calendar.h"
#include "DEBUG.h"
#include <string>
#include <iostream>


OrderGet::OrderGet(string name, BloodBank* blood_bank, int t0, int q, bool normal) :TimeCondition(name, blood_bank, t0), Q_(q),normal_(normal)
{
}

void OrderGet::Execute(BloodBank* blood_bank) {
  for (int i = 0; i<Q_; i++)
  {
	  blood_bank->AddingBloodUnits(T0_); //zwiêkszenie iloœci krwi  T0-czas wa¿noœci krwi
  }

  if(DEBUG)std::cout << "Add " << to_string(Q_) << " unit of blood to bank." << std::endl;
  //usuniêcie zamówienia z kalendarza
  if (normal_) blood_bank->NO = false;   //usuniêcie flagi normalnego zamówienia pod warunkiem ¿e nie ma awaryjnego zamówienia
  else blood_bank->EO = false;   //usuniêcie flagi od zamówienia awaryjnego 
  blood_bank->calendar_->calendar.pop_front();	//usuwanie zamównia z kalendarza
}

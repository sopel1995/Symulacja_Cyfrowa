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
	  blood_bank->AddingBloodUnits(T0_); //zwi�kszenie ilo�ci krwi  T0-czas wa�no�ci krwi
  }

  if(DEBUG)std::cout << "Add " << to_string(Q_) << " unit of blood to bank." << std::endl;
  //usuni�cie zam�wienia z kalendarza
  if (normal_) blood_bank->NO = false;   //usuni�cie flagi normalnego zam�wienia pod warunkiem �e nie ma awaryjnego zam�wienia
  else blood_bank->EO = false;   //usuni�cie flagi od zam�wienia awaryjnego 
  blood_bank->calendar_->calendar.pop_front();	//usuwanie zam�wnia z kalendarza
}

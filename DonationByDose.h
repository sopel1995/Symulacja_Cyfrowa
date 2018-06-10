#pragma once
#include "TimeCondition.h"

class DonationByDose :  //klasa odpowiedzialna za dostarczneie krwi przez lokalnych dawców
  public TimeCondition
{
public:
	virtual void Execute(BloodBank* blood_bank) override;
	DonationByDose(BloodBank* blood_bank, int t0);
	 ~DonationByDose()=default;
private:
	int T1_=500;	//czas wa¿noœci krwi od lokalnego dawcy
	int l_g_=900;
};


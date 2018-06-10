#include "stdafx.h"
#include "DonationByDose.h"
#include "DEBUG.h"
#include <iostream>
#include "Calendar.h"




DonationByDose::DonationByDose(BloodBank* blood_bank, int t0) : TimeCondition("Donor's blood", blood_bank,t0)
{

}

void DonationByDose::Execute(BloodBank* blood_bank) {
  int t0= static_cast<int>(round(blood_bank->get_generate()->ExponentialGenerator(l_g_)))+blood_bank->calendar_->get_time_system();
  if(DEBUG)std::cout << "Blood supply by dose with validity " <<T1_<<". Next donor is planing at: "<<t0<<"."<<std::endl;
  blood_bank->AddingBloodUnits(T1_);
  blood_bank->calendar_->AddSortTimeCondition(new DonationByDose(blood_bank, t0));
}

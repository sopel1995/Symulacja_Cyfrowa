#include "stdafx.h"
#include "SendingBloodOrder.h"
#include "Calendar.h"
#include "OrderGet.h"
#include <string>
#include "DEBUG.h"


SendingBloodOrder::SendingBloodOrder(string name, BloodBank* blood_bank, int execution_time, bool normal) :TimeCondition(name, blood_bank, execution_time), normal(normal) {
	int delivery_time;
	
	if (normal)
	{
		TN_ = static_cast<int>(round(blood_bank->get_generate()->ExponentialGenerator(n_g_)));
		if (TN_ == 0)TN_++;
		delivery_time = TN_ + blood_bank->calendar_->get_time_system();
		if (DEBUG)std::cout << "NORMAL" << endl;
		blood_bank->calendar_->AddSortTimeCondition(new OrderGet("Order", blood_bank, delivery_time,Q_N_, true));
	}
	else
	{
		TE_ = static_cast<int>(round(blood_bank->get_generate()->NormalGenerator(e_m_g_, e_d_g_)));
		if (TE_ == 0)TE_++;
		delivery_time = TE_ + blood_bank->calendar_->get_time_system();
		if (DEBUG)std::cout << "EMERGENCY" << endl;
		blood_bank->calendar_->AddSortTimeCondition(new OrderGet("Order", blood_bank, delivery_time, Q_E_,false));
	}
	if (DEBUG)std::cout << "Sending Blood Order to " + std::to_string(Q_E_) + " units of blood. Delivery time is: " << delivery_time << "." << std::endl;
}

int SendingBloodOrder::get_TE()
{
	return TE_;
}
int SendingBloodOrder::get_TN()
{
	return TN_;
}


void SendingBloodOrder::Execute(BloodBank* blood_bank) {
  if (normal) {
	  blood_bank->NO = true;
	//  TN_=static_cast<int>(round(blood_bank->get_generate()->ExponentialGenerator(n_g_)));
   // blood_bank->calendar_->AddSortTimeCondition(new OrderGet("OrderGet", blood_bank, TN_+blood_bank->calendar_->get_time_system(), Q_N_));
  }
  else {
	  blood_bank->EO = true;
	//  TE_ = static_cast<int>(round(blood_bank->get_generate()->NormalGenerator(e_m_g_, e_d_g_)));
	//  blood_bank->calendar_->AddSortTimeCondition(new OrderGet("OrderGet", blood_bank, TE_ + blood_bank->calendar_->get_time_system(), Q_E_));
  }
}

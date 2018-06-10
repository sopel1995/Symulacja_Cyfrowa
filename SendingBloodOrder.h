#pragma once

#include "TimeCondition.h"
#include "OrderGet.h"

class SendingBloodOrder ://klasa odpowiedzialna za wysy�anie zam�wienia awaryjne
  public TimeCondition
{

public:
  bool normal;
  int get_TE();
  int get_TN();

  virtual void Execute(BloodBank* blood_bank) override;
  SendingBloodOrder(string name, BloodBank* blood_bank, int execution_time, bool normal);
  ~SendingBloodOrder()=default;
private:
	int TN_;	//czas na przybycie zam�wienia
	int TE_;
	int Q_N_ = 30;
	int Q_E_ = 14;
	int n_g_ = 3000;	//zmieni�em na cele wyznaczenia fazy pocz�tkowej
	int e_m_g_ = 300;	//warto�� �rednia
	double e_d_g_ = 0.1;	//wariancja
	
};


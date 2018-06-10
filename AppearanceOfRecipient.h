#pragma once
#include "TimeCondition.h"
class AppearanceOfRecipient :
	public TimeCondition
{
public:
	 void Execute(BloodBank* blood_bank) override;
	AppearanceOfRecipient(string name, BloodBank* blood_bank, int t0);
	~AppearanceOfRecipient()=default;
private:
	double t_g_=0.22;	
	int p_g_ = 150;
};


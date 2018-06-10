#include "stdafx.h"
#include "Utilization.h"
#include "DEBUG.h"


Utilization::Utilization(string name, BloodBank* blood_bank, int execution_time, int id) :TimeCondition(name, blood_bank, execution_time), id_(id)
{
}

void Utilization::Execute(BloodBank* blood_bank) {

	blood_bank->DeleteIdUnitsOfBlood(id_);
	blood_bank->inc_s_u();
	if(DEBUG)std::cout << "Utilization." << std::endl;
}

int Utilization::get_id() {
	return id_;
}


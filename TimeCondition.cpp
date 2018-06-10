#include "stdafx.h"
#include "TimeCondition.h"
#include "BloodBank.h"
#include "DEBUG.h"
#include <iostream>


TimeCondition::TimeCondition(const string name, BloodBank* blood_bank, int execution_time) : name_(name), blood_bank_(blood_bank), time_Execute_(execution_time)
{
}


void TimeCondition::Execute(BloodBank* blood_bank) {
  if (DEBUG)cout << "TimeCondition::Execute(BloodBank* blood_bank)" << endl;
}

 string TimeCondition::ReadName() const
{
	return  name_;
}
int TimeCondition::get_execution_time() const
{
	return time_Execute_;
}

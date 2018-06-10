#pragma once

#include "stdafx.h"
#include "BloodBank.h"
#include "TimeCondition.h"


class Utilization : //klasa odpowiedzialna za utylizacjê krwi
  public TimeCondition
{
public: 
  virtual void Execute(BloodBank* blood_bank);
  int get_id();
  Utilization(string name, BloodBank* blood_bank, int execution_time, int id);
  ~Utilization()=default;
private:
	int id_;
};


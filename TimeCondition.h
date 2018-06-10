#pragma once
#include "stdafx.h"
#include "BloodBank.h"

using namespace std;

class TimeCondition //klasa bazowa wszystkich zdarzeñ czasowych
{
private:
	string name_;
	BloodBank* blood_bank_;
	int time_Execute_;
public:
  int get_execution_time() const;
  string ReadName() const;
  virtual void Execute(BloodBank* blood_bank) = 0;
  TimeCondition(const string name, BloodBank* blood_bank, const int execution_time); //USUN¥C tylko na cele testowe
  ~TimeCondition() = default;


};

#pragma once
#include "TimeCondition.h"
#include "BloodBank.h"


class OrderGet :
	public TimeCondition
{
public:
	virtual void Execute(BloodBank* blood_bank) override;
	OrderGet(string name, BloodBank* blood_bank, int t0, int q,bool normal);
	~OrderGet()=default;
private:
	int Q_;  //ilosc jednostek krwi zam�wiona w zam�wieniu
	int T0_=300; //czas wa�no�ci krwi
	bool normal_;

};
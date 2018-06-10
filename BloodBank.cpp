#include "stdafx.h"
#include "BloodBank.h"
#include <iostream>
#include  "UnitOfBlood.h"
#include <queue>
#include <list>
#include "Calendar.h"
#include "Utilization.h"
#include "DEBUG.h"


BloodBank::BloodBank(int r, int j, int z, int kernel ) : R_(r), J(j), Z_(z), pool_ID(0), EO(false), NO(false), s_e_(0),s_c_(0),s_u_(0) {
  if(DEBUG)std::cout << "Made a new blood bank" << std::endl;
  calendar_ = new Calendar(this);
  generate_ = new Distribution(kernel);
  number_of_blood_spent = 0;
  number_of_recipients_served=0;
  length_of_longest_recipient_queue=0;
}
BloodBank::~BloodBank()
{
	delete calendar_;
	delete generate_;
}
void BloodBank::inc_s_c()
{
	s_c_++;
}
void BloodBank::inc_s_e()
{
	s_e_++;
}
int BloodBank::get_s_e()
{
	return s_e_;
}
int BloodBank::get_s_c()
{
	return s_c_;
}
void BloodBank::inc_s_u()
{
	s_u_++;
}
int BloodBank::get_s_u()
{
	return s_u_;
}


int BloodBank::get_R() const
{
	return R_;
}
Distribution* BloodBank::get_generate() const 
{
	return generate_;
}

void BloodBank::AddingBloodUnits(int t0) {
  AddBloodUnitsSort(UnitOfBlood(pool_ID, t0));
  int time_Execute = calendar_->get_time_system() + t0;
  J++;
  calendar_->AddSortTimeCondition(new Utilization("Utilization", this, time_Execute, pool_ID));	//automatyczne zaplanowanie utylizacji
  if (DEBUG)std::cout << "Planing Utilization at " << time_Execute << std::endl;
  pool_ID++;
	
}
void BloodBank::ReadList() {
  if(DEBUG)std::cout << "Read list units of blood:" << std::endl;
  for (list<UnitOfBlood>::iterator i = queue_blood.begin(); i != queue_blood.end(); ++i)
  {
    if(DEBUG)std::cout << int((*i).ID) << "  " << int((*i).T0) << std::endl;
  }
}
void  BloodBank::AddBloodUnitsSort(UnitOfBlood unit_of_blood) {
  if (queue_blood.empty() == true)  queue_blood.push_front(unit_of_blood);
  else
  {
    for (list<UnitOfBlood>::iterator i = queue_blood.begin(); i != queue_blood.end(); ++i)
    {
      if (int((*i).T0) > unit_of_blood.T0)
      {
        queue_blood.insert(i, unit_of_blood);
        return;
      }
    }
    queue_blood.push_back(unit_of_blood);
  }
}
bool BloodBank::DeleteIdUnitsOfBlood(int id) { //usuwanie jednostki krwi z listy po ID
  for (list<UnitOfBlood>::iterator i = queue_blood.begin(); i != queue_blood.end(); ++i)
  {
    if ((*i).ID == id)
    {
      queue_blood.erase(i);
	  J--;
      if(DEBUG)std::cout << "Find and delete search unit of blood" << endl;
	  calendar_->DeleteTimeConditionUtilization(id);
      return true;
    }
  }
  if (DEBUG) cout << "No find search unit of blood" << endl;
  return false;
}



void BloodBank::GettingToQueue(Recipients* recipients)
{
	queue_of_recipients_.push(recipients);
}
void BloodBank::ReadQueue()
{
	if (DEBUG) std::cout << "First patient on queue need:" << queue_of_recipients_.front()->A << " units of blood" << std::endl;
}
void BloodBank::DeleteFirstQueue()
{
	queue_of_recipients_.pop();
	if (DEBUG) std::cout << "Delete first patient on queue" << std::endl;
}


Recipients* BloodBank::get_first_recipient() const
{
	return queue_of_recipients_.front();
}

bool BloodBank::deleteFirstUnitsOfBlood()
{
	J--;
	if (queue_blood.empty()) return false;
	if(calendar_->DeleteTimeConditionUtilization(queue_blood.front().ID))
	{
		queue_blood.pop_front();
		return true;
	}
	if (DEBUG)std::cout << "ERROR. Not find Utilization on calender." << std::endl;
	return false;
}
int BloodBank::get_id_FirstUnitOfBlood() const
{
	return queue_blood.front().ID;
}

int BloodBank::get_size_blood_in_bank() const
{
	return queue_blood.size();
}

int BloodBank::get_handled_recipients() const
{
	return handled_recipients_;
}

void BloodBank::inc_handled_recipients()
{
	handled_recipients_++;
}
int BloodBank::queue_recipients_size() const
{
	return queue_of_recipients_.size();
}
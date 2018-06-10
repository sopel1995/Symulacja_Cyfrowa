#pragma once

#include "TimeCondition.h"
#include <list>
#include "BloodBank.h"

class BloodHospital;

class Calendar
{
public:
  Calendar* wsk_calendar = this;
  int get_time_system();
  void set_time_System(int time);
  bool EVENT_TRIG;
  list<TimeCondition*> calendar;
  void AddSortTimeCondition(TimeCondition* event);
  bool DeleteTimeConditionFirst();
  bool DeleteTimeConditionUtilization(int id);
  void ReadCalendar();
  int CalendarSize();

  Calendar(BloodBank *blood_bank);
  ~Calendar() = default;
private:
	int act_time_;
	BloodBank* blood_bank_;
};


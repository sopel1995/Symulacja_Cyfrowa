#include "stdafx.h"
#include "Calendar.h"
#include "TimeCondition.h"
#include <list>
#include "Utilization.h"
#include "DEBUG.h"



Calendar::Calendar(BloodBank* blood_bank) : act_time_(0), EVENT_TRIG(true)
{
	blood_bank_ = blood_bank;
}

void Calendar::AddSortTimeCondition(TimeCondition* event)
{

  if (calendar.empty() == true)  calendar.push_front(event);
  else
  {
    for (list<TimeCondition*>::iterator i = calendar.begin(); i != calendar.end(); ++i)
    {
      if ((*i)->get_execution_time() >= event->get_execution_time())
      {
        calendar.insert(i, event);
        return;
      }
    }
    calendar.push_back(event);
  }
}

int Calendar::get_time_system()
{
	return act_time_;
}
void Calendar::set_time_System(int time)
{
	act_time_ = time;
}
bool Calendar::DeleteTimeConditionFirst()
{
	calendar.pop_front();
	return true;
}
int Calendar::CalendarSize()
{
	return calendar.size();
}
void Calendar::ReadCalendar()
{
	if (DEBUG)std::cout << "Read calendar:" << std::endl;
	for (list<TimeCondition*>::iterator i = calendar.begin(); i != calendar.end(); ++i)
	{
		std::cout << ((*i)->ReadName()).c_str() << std::endl;
	}
}
bool Calendar::DeleteTimeConditionUtilization(int id)
{
	for (list<TimeCondition*>::iterator i = calendar.begin(); i != calendar.end(); ++i)
	{
		if ((*i)->ReadName() == "Utilization" && (static_cast<Utilization*>(*i)->get_id() == id)) {

			
			if (DEBUG)std::cout << "Delete planing Utilization unit of blood: " << id << "and time Execute: " << (*i)->get_execution_time() << "." << std::endl;
			if(get_time_system()<(*i)->get_execution_time())calendar.erase(i);
			
			return true;
		}
	}
	return false;
}


#include <queue>
#include "Recipients.h"
#pragma once

class QueueOfRecipients
{
public:
  void GettingToQueue(Recipients* recipients);
  void ReadQueue();
  void DeleteFirstQueue();
  void RandRecipientQueue();
  QueueOfRecipients();
  ~QueueOfRecipients();
private:
	
};


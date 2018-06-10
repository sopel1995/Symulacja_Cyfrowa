#include "stdafx.h"
#include "QueueOfRecipients.h"
#include <iostream>

#include "Recipients.h"
#include "DEBUG.h"

QueueOfRecipients::QueueOfRecipients()
{
}


QueueOfRecipients::~QueueOfRecipients()
{
}
void QueueOfRecipients::GettingToQueue(Recipients* recipients) {
	queue_of_recipients_.push(recipients);
}
void QueueOfRecipients::ReadQueue() {
	if (DEBUG) std::cout << "First patient on queue need:" << queue_of_recipients_.front()->A << " units of blood" << std::endl;
}
void QueueOfRecipients::DeleteFirst() {
  queue_of_recipients_.pop();
  if (DEBUG) std::cout << "Delete first patient on queue" << std::endl;
}
void QueueOfRecipients::RandRecipient() {
  GettingToQueue(new Recipients(5));
  if (DEBUG) std::cout << "Rand recipients" << std::endl;
}

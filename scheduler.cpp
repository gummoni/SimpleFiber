#include "scheduler.h"

void sc::attach(fiber* fiber)
{
	if (NULL == first) {
		first = current = fiber;
	}
	else {
		last->next = fiber;
	}
	last = fiber;
	last->next = first;
}

void sc::start() {
	for (;;)
	{
		current->dispatch();
		current = current->next;
	}
}

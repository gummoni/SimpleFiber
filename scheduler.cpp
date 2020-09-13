#include "scheduler.h"

void scheduler::attach(fiber* fiber)
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

void scheduler::start() {
	for (;;)
	{
		current->dispatch();
		current = current->next;
	}
}

void scheduler::yield() {
	current->yield();
}

scheduler* sc = new scheduler();

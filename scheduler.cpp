#include "scheduler.h"

int task_id;
fiber* fibers[4];

void scheduler_init() {
	fibers[0] = new fiber();
	fibers[1] = new fiber();
	fibers[2] = new fiber();
	fibers[3] = new fiber();
}

void scheduler_start() {
	while (true)
	{
		fibers[task_id]->dispatch();
		task_id = (task_id + 1) & 3;
	}
}

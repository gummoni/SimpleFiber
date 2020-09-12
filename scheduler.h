#pragma once
#include "fiber.h"

extern int task_id;
extern fiber* fibers[4];
extern void scheduler_init();
extern void scheduler_start();


#define  yield \
if (0 == setjmp(fibers[task_id]->jmpbuf)) {\
	int tid = task_id;\
	do {\
		task_id = (task_id + 1) & 3;\
		fibers[task_id]->dispatch();\
	} while (tid != task_id);\
}\

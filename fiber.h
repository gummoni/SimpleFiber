#pragma once
#include "func.h"
#include <setjmp.h>

class fiber {
public:
	func* invoke(void(*invoke)(void*), void* arg);
	void dispatch();
	void yield();
	jmp_buf jmpbuf;
	fiber* next;

private:
	func dummy;
	func queue[4];
	bool is_busy;
	int ridx;
	int widx;
};

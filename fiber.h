#pragma once
#include <setjmp.h>

typedef struct func {
	void (*invoke)(void* arg);
	void* arg;
} func;

class fiber {
public:
	void invoke(void(*invoke)(void*), void* arg);
	void dispatch();
	void yield();
	jmp_buf jmpbuf;
	fiber* next;

private:
	func queue[4];
	int ridx;
	int widx;
};

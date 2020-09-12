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
	jmp_buf jmpbuf;

private:
	func queue[4];
	int ridx;
	int widx;
};

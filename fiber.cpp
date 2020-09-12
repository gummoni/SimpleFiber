#include "fiber.h"

void fiber::invoke(void(*invoke)(void*), void* arg) {
	func* f = &(this->queue[this->widx]);
	f->invoke = invoke;
	f->arg = arg;
	this->widx = (this->widx + 1) & 3;
}

void fiber::dispatch() {
	if (*this->jmpbuf != 0) {
		longjmp(this->jmpbuf, 1);
	}
	else  if (this->ridx != this->widx) {
		func* f = &(this->queue[this->ridx]);
		if (NULL != f) {
			f->invoke(f->arg);
			f->invoke = NULL;
			*this->jmpbuf = 0;
		}
		this->ridx = (this->ridx + 1) & 3;
	}
}

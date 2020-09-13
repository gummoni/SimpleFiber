#include "fiber.h"

func* fiber::invoke(void(*invoke)(void*), void* arg) {
	if (is_busy) {
		//reentrant
		dummy.invoke = invoke;
		dummy.arg = arg;
		dummy.state = 1;
		invoke(arg);
		dummy.state = 2;
		return &dummy;
	}
	else {
		//invoke
		func* f = &(queue[widx]);
		f->invoke = invoke;
		f->arg = arg;
		widx = (widx + 1) & 3;
		return f;
	}
}

void fiber::dispatch() {
	if (*jmpbuf != 0) {
		//yield
		longjmp(jmpbuf, 1);
	}
	else  if (ridx != widx) {
		//dispatch
		func* f = &(queue[ridx]);
		if (NULL != f) {
			is_busy = true;
			f->state = 1;
			f->invoke(f->arg);
			f->state = 2;
			f->invoke = NULL;
			*jmpbuf = 0;
			is_busy = false;
		}
		ridx = (ridx + 1) & 3;
	}
}

void fiber::yield() {
	for (fiber* current = next; current != this; current = current->next) {
		current->dispatch();
	}
}

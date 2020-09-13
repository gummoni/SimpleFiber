/*
The MIT License (MIT)
Copyright (c) 2020 Koichi Nishino
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "fiber.h"

func* fiber::invoke(void(*invoke)(void*), void* arg) {
	if (is_busy) {
		//reentrant
		invoke(arg);
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
	else if (is_busy) {
		//busy (not yield)
		return;
	}
	else  if (ridx != widx) {
		//dispatch
		func* f = &(queue[ridx]);
		if (NULL != f) {
			is_busy = true;
			f->invoke(f->arg);
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

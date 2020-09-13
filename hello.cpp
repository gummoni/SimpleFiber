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
#include <stdio.h>
#include "fiber.h"
#include "scheduler.h"

fiber* f1 = new fiber();
fiber* f2 = new fiber();
fiber* f3 = new fiber();
fiber* f4 = new fiber();

static void foo(void* arg) {
	printf("foo\n");
}

static void bar(void* arg) {
	sc->yield();
	printf("bar\n");
}

static void world() {
	int retry = 3;

	while (0 < retry--) {
		printf("world:%d\n", retry);
		sc->yield();
	}
	func* func1 = f1->invoke(foo, NULL);
	func1->wait();

	func* func2 = f3->invoke(bar, NULL);
	func2->wait();
}

static void hello(void* arg) {
	int retry = 5;

	while (0 < retry--) {
		printf("hello:%d\n", retry);
		world();
	}

	printf("finish\n");
}


int main(void) {

	sc->attach(f1);
	sc->attach(f2);
	sc->attach(f3);
	sc->attach(f4);
	f1->invoke(hello, NULL);
	sc->start();

	//scheduler_init();
	//fibers[0]->invoke(hello, NULL);
	//scheduler_start();

	return 0;
}

#include <stdio.h>
#include "fiber.h"
#include "scheduler.h"

fiber* f1 = new fiber();
fiber* f2 = new fiber();
fiber* f3 = new fiber();
fiber* f4 = new fiber();

static void foobar(void* arg) {
	printf("foo bar\n");
}

static void world() {
	int retry = 3;

	while (0 < retry--) {
		printf("world:%d\n", retry);
		sc->yield();
	}
	func* func = f1->invoke(foobar, NULL);
	func->wait();
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

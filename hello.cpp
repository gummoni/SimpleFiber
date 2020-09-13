#include <stdio.h>
#include "fiber.h"
#include "scheduler.h"

static sc* sc1;

static void world(void) {
	int retry = 3;
	while (0 < retry--) {
		printf("world:%d\n", retry);
		sc1->current->yield();
	}
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

	sc1 = new sc();

	fiber* f1 = new fiber();
	fiber* f2 = new fiber();
	fiber* f3 = new fiber();
	fiber* f4 = new fiber();

	sc1->attach(f1);
	sc1->attach(f2);
	sc1->attach(f3);
	sc1->attach(f4);
	f1->invoke(hello, NULL);
	sc1->start();

	//scheduler_init();
	//fibers[0]->invoke(hello, NULL);
	//scheduler_start();

	return 0;
}

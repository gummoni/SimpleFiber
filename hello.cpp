#include <stdio.h>
#include "fiber.h"
#include "scheduler.h"

static void world(void) {
	int retry = 3;
	while (0 < retry--) {
		printf("world:%d\n", retry);
		yield;
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
	scheduler_init();
	fibers[0]->invoke(hello, NULL);
	scheduler_start();

	return 0;
}

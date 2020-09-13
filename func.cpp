#include "func.h"
#include "scheduler.h"

void func::wait() {
	while (2 > state) {
		sc->yield();
	}
}


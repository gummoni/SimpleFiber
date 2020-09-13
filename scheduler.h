#pragma once
#include "fiber.h"

class scheduler {
public:
	scheduler() {
		first = NULL;
		current = NULL;
		last = NULL;
	}

	~scheduler() {
	}

	void start();
	void attach(fiber* fiber);
	void yield();
	fiber* current;

private:
	fiber* first;
	fiber* last;
};

extern scheduler* sc;

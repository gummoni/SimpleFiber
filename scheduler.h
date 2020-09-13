#pragma once
#include "fiber.h"

class sc {
public:
	sc() {
		first = NULL;
		current = NULL;
		last = NULL;
	}

	~sc() {
	}

	void start();
	void attach(fiber* fiber);
	fiber* current;

private:
	fiber* first;
	fiber* last;
};

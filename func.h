#pragma once
class func {
public:
	void (*invoke)(void* arg);
	void* arg;
	void wait();
	int state;		//0= not start, 1=budy, 2=completed
};


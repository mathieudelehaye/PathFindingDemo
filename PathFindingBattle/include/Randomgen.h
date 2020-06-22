#pragma once

class Randint {	// uniform distribution in the interval [0, max]
	unsigned long randx;
public:
	Randint(long s = 0);
	void seed(long);
	int abs(int);
	static double max();
	int draw();
	double fdraw();
	int operator()();
}; 

class Urand : public Randint {	// uniform distribution in the interval [0, n[
	int n; 
public:
	Urand (int);
	int operator()();
};

class Erand : public Randint {	// exponential distribution random number generator
	int mean; 
public: 
	Erand(int);
	int operator()(); 
}; 
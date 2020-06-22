#include "Randomgen.h"

Randint::Randint(long s) { randx = s; }
void Randint::seed(long s) { randx = s; }
// magic numbers nmbers chosen to use 31 bits of a 32-bit long: 
int Randint::abs(int x) { return x&0x7fffffff; }
double Randint::max() { return 2147483648.0; }	// note: a double 
int Randint::draw() { return randx = randx * 1103515245 + 12345; }
double Randint::fdraw() { return abs(draw())/max(); }
int Randint::operator()() { return abs(draw()); }

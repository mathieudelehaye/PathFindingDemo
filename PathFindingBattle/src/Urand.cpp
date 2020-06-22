#include "Randomgen.h"

Urand::Urand(int nn) { n = nn; }
int Urand::operator()() { int r = n*fdraw(); return (r == n) ? n-1 : r; }

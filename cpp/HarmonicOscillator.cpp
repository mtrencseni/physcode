#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === 1D Harmonic oscillator === */

MAKE_ALL_TYPES(double);
typedef Quantity<0,  1, -2, double> SpringConstant;

struct Configuration {
   Length   x;
   Velocity v;
};

struct Parameters {
   Mass           m;
   SpringConstant k;
};

Energy lagrangian(Parameters p, Configuration c) {
   assert(p.k.value > 0);
   return p.m * c.v * c.v / 2.0 - p.k * c.x * c.x / 2.0;
}

Force force(Parameters p, Configuration c1, Length dx) {
   Configuration c2 = { c1.x + dx, c1.v };
   return (lagrangian(p, c2) - lagrangian(p, c1)) / dx;
}

int main()
{
   Parameters     p = { 1.0 * kilo * gram, 3.0 * kilo * gram / (second * second) };
   Configuration  c = { 5.0 * meter, 9.0 * meter / second };
   Length        dx = 0.001 * meter;
   
   std::cout << force(p, c, dx).str() << std::endl;
   
   return 0;
}

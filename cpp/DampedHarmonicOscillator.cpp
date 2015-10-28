#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === 1D Damped harmonic oscillator === */

MAKE_ALL_TYPES(double);
typedef Quantity<0,  1, -2, double> SpringConstant;
typedef Quantity<0,  1, -1, double> DampingConstant;

struct Configuration {
   Length   x;
   Velocity v;
};

struct Parameters {
   Mass            m;
   SpringConstant  k;
   DampingConstant c;
};

Force force(Parameters p, Configuration c) {
   return -1.0 * p.k * c.x - p.c * c.v;
}

Acceleration acceleration(Parameters p, Configuration c) {
   return force(p, c) / p.m;
}

Configuration step(Parameters p, Configuration c, Time dt) {
   Length   dx = c.v * dt;
   Velocity dv = acceleration(p, c) * dt;
   Configuration cp =  { c.x + dx, c.v + dv };
   return cp;
}

int main()
{
   Parameters     p = { 1.0 * kilo * gram,
                        3.0 * kilo * gram / (second * second),
                        5.0 * kilo * gram / second };
   Configuration  c = { 5.0 * meter, 9.0 * meter / second };
   Time          dt = 0.001 * second;
   
   for (auto i = 0; i < 5; i++) {
       std::cout << c.x.str() << ", " << c.v.str() << std::endl;
       c = step(p, c, dt);
   }
   
   return 0;
}

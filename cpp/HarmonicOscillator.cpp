#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === 1D Harmonic oscillator === */

typedef Quantity<1,  0,  0, 0, 0, 0, 0, double> Length;
typedef Quantity<0,  1,  0, 0, 0, 0, 0, double> Mass;
typedef Quantity<0,  0,  1, 0, 0, 0, 0, double> Time;
typedef Quantity<1,  0, -1, 0, 0, 0, 0, double> Velocity;
typedef Quantity<1,  0, -2, 0, 0, 0, 0, double> Acceleration;
typedef Quantity<1,  1, -2, 0, 0, 0, 0, double> Force;
typedef Quantity<2,  1, -2, 0, 0, 0, 0, double> Energy;
typedef Quantity<0,  1, -2, 0, 0, 0, 0, double> SpringConstant;

struct Configuration {
    Length   position;
    Velocity velocity;
};

struct Parameters {
    Mass           m;
    SpringConstant k;
};

Energy lagrangian(Parameters p, Configuration c) {
    assert(p.m.value() > 0);
    assert(p.k.value() > 0);
    return p.m * (c.velocity * c.velocity) / 2.0 - p.k * (c.position * c.position) / 2.0;
}

Force force(Parameters p, Configuration c, Length dx) {
   Configuration cx = { c.position + dx, c.velocity };
   return (lagrangian(p, cx) - lagrangian(p, c)) / dx;
}

int main()
{
   Parameters     p = { 1.0 * kilogram, 3.0 * kilogram / (second * second) };
   Configuration  c = { 5.0 * meter, 9.0 * meter / second };
   Length        dx = 0.001 * meter;
   
   std::cout << force(p, c, dx).str() << std::endl;
   
   return 0;
}


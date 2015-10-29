#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === 1D Damped harmonic oscillator === */


typedef Quantity<1,  0,  0, double> Length;
typedef Quantity<0,  1,  0, double> Mass;
typedef Quantity<0,  0,  1, double> Time;
typedef Quantity<1,  0, -1, double> Velocity;
typedef Quantity<1,  0, -2, double> Acceleration;
typedef Quantity<1,  1, -2, double> Force;
typedef Quantity<2,  1, -2, double> Energy;
typedef Quantity<0,  1, -2, double> SpringConstant;
typedef Quantity<0,  1, -1, double> DampingConstant;

struct Configuration {
    Length   position;
    Velocity velocity;
};

struct Parameters {
    Mass            m;
    SpringConstant  k;
    DampingConstant c;
};

Force force(Parameters p, Configuration c) {
    assert(p.m.value() > 0);
    assert(p.k.value() > 0);
    assert(p.c.value() > 0);
    return -1.0 * (p.k * c.position) - (p.c * c.velocity);
}

Acceleration acceleration(Parameters p, Configuration c) {
    return force(p, c) / p.m;
}

Configuration step(Parameters p, Configuration c, Time dt) {
    Length   dx = c.velocity * dt;
    Velocity dv = acceleration(p, c) * dt;
    Configuration cp =  { c.position + dx, c.velocity + dv };
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
        std::cout << c.position.str() << ", " << c.velocity.str() << std::endl;
        c = step(p, c, dt);
    }

    return 0;
}

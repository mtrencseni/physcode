#include <iostream>
#include <assert.h>
#include "VecQuantity.h"

/* === 2D Damped harmonic oscillator === */

typedef Vec<2, double> Vec2;
Vec2 ex = {1, 0};
Vec2 ey = {0, 1};

typedef    Quantity<1,  0,  0,    double> Length;
typedef VecQuantity<1,  0,  0, 2, double> Length2;
typedef    Quantity<0,  1,  0,    double> Mass;
typedef    Quantity<0,  0,  1,    double> Time;
typedef VecQuantity<1,  0, -1, 2, double> Velocity2;
typedef VecQuantity<1,  0, -2, 2, double> Acceleration2;
typedef    Quantity<1,  1, -2,    double> Force;
typedef VecQuantity<1,  1, -2, 2, double> Force2;
typedef    Quantity<2,  1, -2,    double> Energy;
typedef    Quantity<0,  1, -2,    double> SpringConstant;
typedef    Quantity<0,  1, -1,    double> DampingConstant;

struct Configuration {
    Length2   position;
    Velocity2 velocity;
};

struct Parameters {
    Mass            m;
    SpringConstant  k;
    DampingConstant c;
};

Force2 force(Parameters p, Configuration c) {
   return -1.0 * (p.k * c.position) - p.c * c.velocity;
}

Acceleration2 acceleration(Parameters p, Configuration c) {
   return force(p, c) / p.m;
}

Configuration step(Parameters p, Configuration c, Time dt) {
   
   Configuration cp =  { c.position + c.velocity * dt,
                         c.velocity + acceleration(p, c) * dt };
   return cp;
}

int main()
{
    Parameters    p = { 1.0  * kilo * gram,
                        50.0 * kilo * gram / (second * second),
                        5.0  * kilo * gram / second };
    Configuration c = { (2.0 * ex + 2.0 * ey) * meter,
                        (0.0 * ex + 0.0 * ey) * meter / second };
    Time          dt = 0.001 * second;
    for (double i = 0; i < 10000; i++) {
        std::cout << (i * dt).str() << ", " << c.position.str() << std::endl;
        c = step(p, c, dt);
    }
    return 0;
}

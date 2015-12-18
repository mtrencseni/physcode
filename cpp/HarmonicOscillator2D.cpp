#include <iostream>
#include <assert.h>
#include "VecQuantity.h"

/* === 2D Harmonic oscillator === */

typedef Vec<2, double> Vec2;
Vec2 ex = {1, 0};
Vec2 ey = {0, 1};

typedef    Quantity<1,  0,  0, 0, 0, 0, 0,    double> Length;
typedef VecQuantity<1,  0,  0, 0, 0, 0, 0, 2, double> Length2;
typedef    Quantity<0,  1,  0, 0, 0, 0, 0,    double> Mass;
typedef    Quantity<0,  0,  1, 0, 0, 0, 0,    double> Time;
typedef VecQuantity<1,  0, -1, 0, 0, 0, 0, 2, double> Velocity2;
typedef VecQuantity<1,  0, -2, 0, 0, 0, 0, 2, double> Acceleration2;
typedef    Quantity<1,  1, -2, 0, 0, 0, 0,    double> Force;
typedef VecQuantity<1,  1, -2, 0, 0, 0, 0, 2, double> Force2;
typedef    Quantity<2,  1, -2, 0, 0, 0, 0,    double> Energy;
typedef    Quantity<0,  1, -2, 0, 0, 0, 0,    double> SpringConstant;

struct Configuration {
    Length2   position;
    Velocity2 velocity;
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

Force2 force(Parameters p, Configuration c, Length dx) {
    Configuration cx = { c.position + dx * ex, c.velocity };
    Configuration cy = { c.position + dx * ey, c.velocity };
    Force fx = (lagrangian(p, cx) - lagrangian(p, c)) / dx;
    Force fy = (lagrangian(p, cy) - lagrangian(p, c)) / dx;
    Force2 f = fx * ex + fy * ey;
    return f;
}

Acceleration2 acceleration(Parameters p, Configuration c, Length dx) {
    return force(p, c, dx) / p.m;
}

Configuration step(Parameters p, Configuration c, Length dx, Time dt) {
    Configuration cp =  { c.position + c.velocity * dt,
                          c.velocity + acceleration(p, c, dx) * dt };
    return cp;
}

int main()
{
    Parameters    p = { 1.0  * kilogram,
                        50.0 * kilogram / (second * second) };
    Configuration c = { (2.0 * ex + 2.0 * ey) * meter,
                        (0.0 * ex + 0.0 * ey) * meter / second };
    Length        dx = 0.001 * meter;
    Time          dt = 0.001 * second;
    for (double i = 0; i < 10000; i++) {
        std::cout << (i * dt).str() << ", " << c.position.str() << std::endl;
        c = step(p, c, dx, dt);
    }
    return 0;
}

#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === Simple thermodynamics === */

typedef Quantity< 1,  0,  0, 0,  0, 0,  0, double> Length;
typedef Quantity< 2,  0,  0, 0,  0, 0,  0, double> Area;
typedef Quantity< 3,  0,  0, 0,  0, 0,  0, double> Volume;
typedef Quantity< 0,  1,  0, 0,  0, 0,  0, double> Mass;
typedef Quantity< 0,  0,  1, 0,  0, 0,  0, double> Time;
typedef Quantity< 1,  0, -1, 0,  0, 0,  0, double> Velocity;
typedef Quantity< 1,  0, -2, 0,  0, 0,  0, double> Acceleration;
typedef Quantity< 1,  1, -2, 0,  0, 0,  0, double> Force;
typedef Quantity< 2,  1, -2, 0,  0, 0,  0, double> Energy;
typedef Quantity<-1,  1, -2, 0,  0, 0,  0, double> Pressure;
typedef Quantity< 0,  0,  0, 0,  1, 0,  0, double> Temperature;
typedef Quantity< 0,  0,  0, 0,  0, 0,  1, double> Moles;
typedef Quantity< 0,  1,  0, 0,  0, 0, -1, double> MolarMass;
typedef Quantity< 2,  1, -2, 0, -1, 0, -1, double> GasConstant;

struct Configuration {
    Pressure    P; // pressure of the gas
    Length      h; // height of the gas
    Velocity    velocity; // velocity of the piston
};

struct Parameters {
    Area        A; // area of the piston and gas chamber
    Temperature T; // isotherm temperature of the gas
    Mass        pistonMass; // mass of the piston
    Mass        gasMass; // mass of the gas
    MolarMass   gasMolarMass; // molar mass of the gas
    GasConstant R; // ideal gas constant
};

void solveForIdealGasPressure(const Parameters& p, Configuration& c)
{
    Moles  n = p.gasMass / p.gasMolarMass;
    Volume V = p.A * c.h;
    c.P = n * p.R * p.T / V; // PV = nRT
}

Acceleration acceleration(const Parameters& p, const Configuration& c)
{
    Acceleration g  = -9.8 * meter / (second * second);
    Force fGravity  = p.pistonMass * g;
    Force fPressure = c.P * p.A;
    Force fTotal    = fGravity + fPressure;
    Acceleration a  = fTotal / p.pistonMass;
    std::cout << a.str() << std::endl;
    return a;
}

Configuration step(const Parameters& p, const Configuration& c, const Length& dx, const Time& dt)
{
    Configuration cp = c;
    cp.h   = c.h + c.velocity * dt;
    cp.velocity = c.velocity + acceleration(p, cp) * dt;
    solveForIdealGasPressure(p, cp);
    return cp;
}

int main()
{
    Length         dx = 0.0001 * meter;
    Time           dt = 0.0001 * second;
    Parameters     p = { 1.0 * meter * meter,
                         300.0 * kelvin,
                         1000.0 * kilo * gram,
                         1.0 * kilo * gram,
                         39.948 * gram / mol, // Argon
                         8.314 * kilo * gram * meter * meter / (second * second * kelvin * mol) // R
                       };
    Configuration  c = { 0.0 * pascal, // solve for this in the first step
                         1.0 * meter,
                         0.0 * meter / second
                       };
    
    solveForIdealGasPressure(p, c);

    for (unsigned i = 0; i < 1000; i++)
    {
        c = step(p, c, dx, dt);
        std::cout << c.h.str() << std::endl;
    }
    
    return 0;
}


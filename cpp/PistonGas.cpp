#include <iostream>
#include <assert.h>
#include "Quantity.h"

/* === Piston + gas thermodynamics === */

typedef Quantity< 1,  0,  0, 0,  0,  0, 0, double> Length;
typedef Quantity< 2,  0,  0, 0,  0,  0, 0, double> Area;
typedef Quantity< 3,  0,  0, 0,  0,  0, 0, double> Volume;
typedef Quantity< 0,  1,  0, 0,  0,  0, 0, double> Mass;
typedef Quantity< 0,  0,  1, 0,  0,  0, 0, double> Time;
typedef Quantity< 1,  0, -1, 0,  0,  0, 0, double> Velocity;
typedef Quantity< 1,  0, -2, 0,  0,  0, 0, double> Acceleration;
typedef Quantity< 1,  1, -2, 0,  0,  0, 0, double> Force;
typedef Quantity< 2,  1, -2, 0,  0,  0, 0, double> Energy;
typedef Quantity<-1,  1, -2, 0,  0,  0, 0, double> Pressure;
typedef Quantity< 0,  0,  0, 0,  1,  0, 0, double> Temperature;
typedef Quantity< 0,  0,  0, 0,  0,  1, 0, double> Moles;
typedef Quantity< 0,  1,  0, 0,  0, -1, 0, double> MolarMass;
typedef Quantity< 2,  1, -2, 0, -1, -1, 0, double> GasConstant;

struct Configuration {
    Pressure    gasPressure;    // pressure of the gas
    Length      gasHeight;      // height of the gas
    Velocity    pistonVelocity; // velocity of the piston
};

struct Parameters {
    Area        pistonArea;     // area of the piston and gas chamber
    Temperature gasTemperature; // isotherm temperature of the gas
    Mass        pistonMass;     // mass of the piston
    Mass        gasMass;        // mass of the gas
    MolarMass   gasMolarMass;   // molar mass of the gas
    GasConstant R;              // ideal gas constant
};

void solveForIdealGasPressure(const Parameters& p, Configuration& c)
{
    Moles  n = p.gasMass / p.gasMolarMass;
    Volume gasVolume = p.pistonArea * c.gasHeight;
    c.gasPressure = n * p.R * p.gasTemperature / gasVolume; // PV = nRT
}

Acceleration acceleration(const Parameters& p, const Configuration& c)
{
    Acceleration g  = -9.8 * meter / (second * second);
    Force fGravity  = p.pistonMass * g;
    Force fPressure = c.gasPressure * p.pistonArea;
    Force fTotal    = fGravity + fPressure;
    Acceleration a  = fTotal / p.pistonMass;
    //std::cout << a.str() << std::endl;
    return a;
}

Configuration step(const Parameters& p, const Configuration& c, const Length& dx, const Time& dt)
{
    Configuration cp = c;
    cp.gasHeight   = c.gasHeight + c.pistonVelocity * dt;
    cp.pistonVelocity = c.pistonVelocity + acceleration(p, cp) * dt;
    solveForIdealGasPressure(p, cp);
    return cp;
}

int main()
{
    Length         dx = 0.0001 * meter;
    Time           dt = 0.0001 * second;
    Parameters     p = { 1.0 * meter * meter,
                         300.0 * kelvin,
                         1000.0 * kilogram,
                         1.0 * kilogram,
                         (39.948/1000.0) * kilogram / mole, // Argon
                         8.314 * kilogram * meter * meter / (second * second * kelvin * mole) // R
                       };
    Configuration  c = { 0.0 * pascal, // solve for this in the first step
                         1.0 * meter,
                         0.0 * meter / second
                       };
    
    solveForIdealGasPressure(p, c);

    for (unsigned i = 0; i < 1000*1000; i++)
    {
        c = step(p, c, dx, dt);
        std::cout << c.gasHeight.val << std::endl;
    }
    
    return 0;
}

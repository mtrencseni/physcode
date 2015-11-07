#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "VecQuantity.h"

/* === Newtonian gravity in 3D, with N bodies === */

typedef Vec<3, double> Vec3;
Vec3 ex = {1, 0, 0};
Vec3 ey = {0, 1, 0};
Vec3 ez = {0, 0, 1};

typedef    Quantity<1,  0,  0, 0, 0, 0, 0,    double> Length;
typedef VecQuantity<1,  0,  0, 0, 0, 0, 0, 3, double> Length3;
typedef    Quantity<0,  1,  0, 0, 0, 0, 0,    double> Mass;
typedef    Quantity<0,  0,  1, 0, 0, 0, 0,    double> Time;
typedef VecQuantity<1,  0, -1, 0, 0, 0, 0, 3, double> Velocity3;
typedef VecQuantity<1,  0, -2, 0, 0, 0, 0, 3, double> Acceleration3;
typedef    Quantity<1,  1, -2, 0, 0, 0, 0,    double> Force;
typedef VecQuantity<1,  1, -2, 0, 0, 0, 0, 3, double> Force3;
typedef    Quantity<2,  1, -2, 0, 0, 0, 0,    double> Energy;
typedef    Quantity<3, -1, -2, 0, 0, 0, 0,    double> GravitationalConstant;

const Force Newton = 1 * kilo * gram * meter / (second * second);

struct Configurations
{
    std::vector<Length3>    position;
    std::vector<Velocity3>  velocity;
};

struct Parameters
{
    std::vector<Mass>       m;
    GravitationalConstant   G;
};

Energy lagrangian(unsigned i, Parameters ps, Configurations cs)
{
    Energy l = ps.m[i] * (cs.velocity[i] * cs.velocity[i]) / 2.0;
    for (unsigned j = 0; j < cs.position.size(); j++)
    {
        if (i == j)
            continue;
        l += ps.G * ps.m[i] * ps.m[j] / sqrt((cs.position[i] - cs.position[j]) * (cs.position[i] - cs.position[j]));
    }
    return l;
}

Force3 force(unsigned i, Parameters ps, Configurations c, Length dx)
{
    Configurations cx = c;
    Configurations cy = c;
    Configurations cz = c;
    cx.position[i] = c.position[i] + dx * ex;
    cy.position[i] = c.position[i] + dx * ey;
    cz.position[i] = c.position[i] + dx * ez;
    Force fx = (lagrangian(i, ps, cx) - lagrangian(i, ps, c)) / dx;
    Force fy = (lagrangian(i, ps, cy) - lagrangian(i, ps, c)) / dx;
    Force fz = (lagrangian(i, ps, cz) - lagrangian(i, ps, c)) / dx;
    Force3 f = fx * ex + fy * ey + fz * ez;
    return f;
}

Acceleration3 acceleration(unsigned i, Parameters ps, Configurations cs, Length dx)
{
    return force(i, ps, cs, dx) / ps.m[i];
}

Configurations step(Parameters ps, Configurations cs, Length dx, Time dt)
{
    assert(ps.m.size()        == cs.position.size());
    assert(cs.position.size() == cs.velocity.size());
    Configurations csp = cs;
    for (unsigned i = 0; i < cs.position.size(); i++)
    {
        csp.position[i] = cs.position[i] + cs.velocity[i] * dt;
        csp.velocity[i] = cs.velocity[i] + acceleration(i, ps, cs, dx) * dt;
    }
    return csp;
}

int main()
{
    Parameters     ps;
    Configurations cs;

    const unsigned  N = 2;
    Length         dx = 0.00001 * meter;
    Time           dt = 0.00001 * second;
                 ps.G = 6.674 * pow(10, -11) * Newton * meter * meter / (kilo * gram * kilo * gram);

    std::uniform_real_distribution<double>  uni(0.0, 1.0);
    std::random_device                      rd;
    std::mt19937                            re(rd());

    // test
    // ps.G = 1.0 * (gram * meter / (second * second)) * meter * meter / (kilo * gram * kilo * gram);
    // ps.m.push_back(10.0 * kilo * gram);
    // ps.m.push_back(1.0 * kilo * gram);
    // cs.position.push_back((0.0 * ex + 0.0 * ey + 0.0 * ez) * meter);
    // cs.position.push_back((1.0 * ex + 0.0 * ey + 0.0 * ez) * meter);
    // cs.velocity.push_back((uni(re) * ex + uni(re) * ey + uni(re) * ez) * meter / second);
    // cs.velocity.push_back((uni(re) * ex + uni(re) * ey + uni(re) * ez) * meter / second);
    // std::cout << "forces:" << std::endl;
    // std::cout << force(0, ps, cs, dx).str() << std::endl;
    // std::cout << force(1, ps, cs, dx).str() << std::endl;
    // std::cout << "accelerations:" << std::endl;
    // std::cout << acceleration(0, ps, cs, dx).str() << std::endl;
    // std::cout << acceleration(1, ps, cs, dx).str() << std::endl;

    for (unsigned i = 0; i < N; i++)
    {
        ps.m.push_back(uni(re)* kilo * gram);
        cs.position.push_back((uni(re) * ex + uni(re) * ey + uni(re) * ez) * meter);
        cs.velocity.push_back((uni(re) * ex + uni(re) * ey + uni(re) * ez) * meter / second);
    }
    
    for (unsigned i = 0; i < 10; i++)
    {
        std::cout << i << std::endl;
        cs = step(ps, cs, dx, dt);
    }

    return 0;
}

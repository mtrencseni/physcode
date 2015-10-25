#include <string>
#include <sstream>
#include <iostream>

std::string format(std::string base, int exponent) {
    std::ostringstream s;
    if (exponent != 0) {    
        s << base;
        if (exponent != 1) {
            s << "^";
            s << exponent;
        }
    }
    return s.str();
}

template<int l, int m, int t>
struct Unit {
    operator std::string() {
        std::ostringstream s;
        if (l != 0) {
            s << format("meter", l);
            s << " ";
        }
        if (m != 0) {
            s << format("gram", m);
            s << " ";
        }
        if (s != 0) {
            s << format("second", t);
        }
        return s.str();
    }
    friend std::ostream& operator<<(std::ostream& o, Unit<l, m, t>& u) {
        o << (std::string)u;
        return o;
    }
};

Unit<1, 0, 0> meter;
Unit<0, 1, 0> gram;
Unit<0, 0, 1> second;

template<int l, int m, int t, class T>
struct Quantity {
	T value;
	Quantity (T v) : value(v) {}
	Quantity () : value(0) {}
	Quantity& operator=(T v) { value = v; }
    operator std::string() {
        Unit<l, m, t> u;
        std::ostringstream s;
        s << value;
        s << " ";
        s << (std::string)u;
        return s.str();
    }
    friend std::ostream& operator<<(std::ostream& o, Quantity<l, m, t, T>& q) {
        o << (std::string)q;
        return o;
    }
};

/* multiply a Unit by a Unit, eg. meter*gram */
template<int l1, int m1, int t1, int l2, int m2, int t2>
Unit<l1+l2, m1+m2, t1+t2> operator*(Unit<l1, m1, t1> u1, Unit<l2, m2, t2> u2)
{
    return Unit<l1+l2, m1+m2, t1+t2>();
}

/* divide a Unit by a Unit, eg. meter/second */
template<int l1, int m1, int t1, int l2, int m2, int t2>
Unit<l1-l2, m1-m2, t1-t2> operator/(Unit<l1, m1, t1> u1, Unit<l2, m2, t2> u2)
{
    return Unit<l1-l2, m1-m2, t1-t2>();
}

/* multiply a Quantity by a Unit, eg. (1*meter)*meter */
template<int l1, int m1, int t1, int l2, int m2, int t2, class T>
Quantity<l1+l2, m1+m2, t1+t2, T> operator*(Quantity<l1, m1, t1, T> q1, Unit<l2, m2, t2> u2)
{
    return Quantity<l1+l2, m1+m2, t1+t2, T>(q1.value);
}

/* divide a Quantity by a Unit, eg. (1*meter)/second */
template<int l1, int m1, int t1, int l2, int m2, int t2, class T>
Quantity<l1-l2, m1-m2, t1-t2, T> operator/(Quantity<l1, m1, t1, T> q1, Unit<l2, m2, t2> u2)
{
    return Quantity<l1-l2, m1-m2, t1-t2, T>(q1.value);
}

/* multiply a T by a Unit to get a Quantity, eg. 5.0 * meter */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator*(T val, Unit<l, m, t> u)
{
    return Quantity<l, m, t, T>(val);
}

/* divide a T by a Unit to get a Quantity, eg. 5.0 / second */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator/(T val, Unit<l, m, t> u)
{
    return Quantity<-l, -m, -t, T>(val);
}

/* multiply a T by a Quantity to get a Quantity */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator*(T val, Quantity<l, m, t, T> q)
{
    return Quantity<l, m, t, T>(val * q.value);
}

/* multiply a Quantity by a T to get a Quantity */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator*(Quantity<l, m, t, T> q, T val)
{
    return Quantity<l, m, t, T>(val * q.value);
}

/* divide a Quantity by T to get a Quantity */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator/(Quantity<l, m, t, T> q, T val)
{
    return Quantity<l, m, t, T>(q.value / val);
}

/* divide a T by a Quantity to get a Quantity */
template<int l, int m, int t, class T>
Quantity<-l, -m, -t, T> operator/(T val, Quantity<l, m, t, T> q)
{
    return Quantity<-l, *m, *t, T>(val / q.value);
}

/* multiply two quantities */
template<int l1, int m1, int t1, int l2, int m2, int t2, class T, class R>
Quantity<l1+l2, m1+m2, t1+t2, R> operator*(Quantity<l1, m1, t1, T> q1, Quantity<l2, m2, t2, T> q2)
{
    R res = q1.value * q2.value;
    return Quantity<l1+l2, m1+m2, t1+t2, R>(res);
}

/* divide two quantities */
template<int l1, int m1, int t1, int l2, int m2, int t2, class T>
Quantity<l1-l2, m1-m2, t1-t2, T> operator/(Quantity<l1, m1, t1, T> q1, Quantity<l2, m2, t2, T> q2)
{
    return Quantity<l1-l2, m1-m2, t1-t2, T>(q1.value / q2.value);
}

/* add two quantities */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator+(Quantity<l, m, t, T> q1, Quantity<l, m, t, T> q2)
{
    return Quantity<l, m, t, T>(q1.value + q2.value);
}

/* divide two quantities */
template<int l, int m, int t, class T>
Quantity<l, m, t, T> operator-(Quantity<l, m, t, T> q1, Quantity<l, m, t, T> q2)
{
    return Quantity<l, m, t, T>(q1.value - q2.value);
}

/* common multipliers */
double kilo = 1000;

#define LENGTH_TYPE(T, n)       typedef Quantity<1,  0,  0, T> n;
#define MASS_TYPE(T, n)         typedef Quantity<0,  1,  0, T> n;
#define TIME_TYPE(T, n)         typedef Quantity<0,  0,  1, T> n;
#define VELOCITY_TYPE(T, n)     typedef Quantity<1,  0, -1, T> n;
#define ACCELERATION_TYPE(T, n) typedef Quantity<1,  0, -2, T> n;
#define FORCE_TYPE(T, n)        typedef Quantity<1,  1, -2, T> n;
#define ENERGY_TYPE(T, n)       typedef Quantity<2,  1, -2, T> n;
#define SPRING_CONSTANT(T, n)   typedef Quantity<0,  1, -2, T> n;

#define MAKE_ALL_TYPES(T)               \
    LENGTH_TYPE(T, Length)              \
    MASS_TYPE(T, Mass)                  \
    TIME_TYPE(T, Time)                  \
    VELOCITY_TYPE(T, Velocity)          \
    ACCELERATION_TYPE(T, Acceleration)  \
    FORCE_TYPE(T, Force)                \
    ENERGY_TYPE(T, Energy)

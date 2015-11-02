#include <string>
#include <sstream>
#include "Unit.h"

/* === Quantity === */
/*
 *
 * A quantity represent a physical quantity: a numeric value (like 1.2) and a dimension (like m/s).
 *  l   -- Length
 *  m   -- Mass
 *  t   -- Time
 *  i   -- Electric current
 *  th  -- Thermodynamic temperature
 *  n   -- Amount of substance
 *  j   -- Luminous intensity
 *
 */

template<int l, int m, int t, int i, int th, int n, int j, class T>
struct Quantity {
	T val;
	Quantity (T val_) : val(val_) {}
	Quantity () : val(0) {}
    T value() const { return val; }
	Quantity& operator=(T val_) { val = val_; }
    std::string str() const {
        Unit<l, m, t, i, th, n, j> u;
        std::ostringstream s;
        s << val;
        s << " ";
        s << u.str();
        return s.str();
    }
};

/* multiply a Quantity by a Unit, eg. (1*meter)*meter */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, class T>
Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>
    operator*(
    const Quantity<l1, m1, t1, i1, th1, n1, j1, T>& q1,
    const Unit<    l2, m2, t2, i2, th2, n2, j2>& u2)
{
    return Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>(q1.value());
}

/* divide a Quantity by a Unit, eg. (1*meter)/second */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, class T>
Quantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, T>
    operator/(
    const Quantity<l1, m1, t1, i1, th1, n1, j1, T>& q1,
    const Unit<    l2, m2, t2, i2, th2, n2, j2>& u2)
{
    return Quantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, T>(q1.value());
}

/* multiply a T by a Unit to get a Quantity, eg. 5.0 * meter */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator*(
    const T& val,
    const Unit<l, m, t, i, th, n, j>& u)
{
    return Quantity<l, m, t, i, th, n, j, T>(val);
}

/* divide a T by a Unit to get a Quantity, eg. 5.0 / second */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator/(
    const T& val,
    const Unit<l, m, t, i, th, n, j>& u)
{
    return Quantity<-l, -m, -t, -i, -th, -n, -j, T>(val);
}

/* multiply a T by a Quantity to get a Quantity */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator*(
    const T& val,
    const Quantity<l, m, t, i, th, n, j, T>& q)
{
    return Quantity<l, m, t, i, th, n, j, T>(val * q.value());
}

/* multiply a Quantity by a T to get a Quantity */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator*(
    const Quantity<l, m, t, i, th, n, j, T>& q,
    const T& val)
{
    return Quantity<l, m, t, i, th, n, j, T>(val * q.value());
}

/* divide a Quantity by T to get a Quantity */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator/(
    const Quantity<l, m, t, i, th, n, j, T>& q,
    const T& val)
{
    return Quantity<l, m, t, i, th, n, j, T>(q.value() / val);
}

/* divide a T by a Quantity to get a Quantity */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<-l, -m, -t, -i, -th, -n, -j, T>
    operator/(
    const T& val,
    const Quantity<l, m, t, i, th, n, j, T>& q)
{
    return Quantity<-l, -m, -t, -i, -th, -n, -j, T>(val / q.value());
}

/* multiply two quantities */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, class T>
Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>
    operator*(
    const Quantity<l1, m1, t1, i1, th1, n1, j1, T>& q1,
    const Quantity<l2, m2, t2, i2, th2, n2, j2, T>& q2)
{
    T res = q1.value() * q2.value();
    return Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>(res);
}

/* divide two quantities */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, class T>
Quantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, T>
    operator/(
    const Quantity<l1, m1, t1, i1, th1, n1, j1, T>& q1,
    const Quantity<l2, m2, t2, i2, th2, n2, j2, T>& q2)
{
    return Quantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, T>(q1.val / q2.value());
}

/* add two quantities */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator+(
    const Quantity<l, m, t, i, th, n, j, T>& q1,
    const Quantity<l, m, t, i, th, n, j, T>& q2)
{
    return Quantity<l, m, t, i, th, n, j, T>(q1.value() + q2.value());
}

/* divide two quantities */
template<int l, int m, int t, int i, int th, int n, int j, class T>
Quantity<l, m, t, i, th, n, j, T>
    operator-(
    const Quantity<l, m, t, i, th, n, j, T>& q1,
    const Quantity<l, m, t, i, th, n, j, T>& q2)
{
    return Quantity<l, m, t, i, th, n, j, T>(q1.value() - q2.value());
}

/* common multipliers */
double kilo = 1000;

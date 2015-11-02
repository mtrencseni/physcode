
/* === Unit === */
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

 std::string format(const std::string base, const int exponent) {
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

template<int l, int m, int t, int i, int th, int n, int j>
struct Unit {
    const std::string str() {
        std::ostringstream s;
        if (l != 0) {
            s << format("meter", l);
            s << " ";
        }
        if (m != 0) {
            s << format("gram", m);
            s << " ";
        }
        if (t != 0) {
            s << format("second", t);
            s << " ";
        }
        if (i != 0) {
            s << format("ampere", i);
            s << " ";
        }
        if (th != 0) {
            s << format("kelvin", th);
            s << " ";
        }
        if (n != 0) {
            s << format("mole", n);
            s << " ";
        }
        if (j != 0) {
            s << format("candela", j);
        }
        return s.str();
    }
};

Unit<1, 0, 0, 0, 0, 0, 0> meter;
Unit<0, 1, 0, 0, 0, 0, 0> gram;
Unit<0, 0, 1, 0, 0, 0, 0> second;

/* multiply a Unit by a Unit, eg. meter*gram */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2>
Unit<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2>
    operator*(
    const Unit<l1, m1, t1, i1, th1, n1, j1>& u1,
    const Unit<l2, m2, t2, i2, th2, n2, j2>& u2)
{
    return Unit<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2>();
}

/* divide a Unit by a Unit, eg. meter/second */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2>
Unit<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2>
    operator/(
    const Unit<l1, m1, t1, i1, th1, n1, j1>& u1,
    const Unit<l2, m2, t2, i2, th2, n2, j2>& u2)
{
    return Unit<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2>();
}


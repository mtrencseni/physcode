
/* === Unit === */
/*
 *
 *  l   meter       m       length
 *  m   kilogram    kg      mass
 *  t   second      s       time
 *  i   ampere      A       electric current
 *  th  kelvin      K       thermodynamic temperature
 *  n   mole        mol     amount of substance
 *  j   candela     cd      luminous intensity
 *
 *  https://en.wikipedia.org/wiki/SI_base_unit
 *
 */

template<int l, int m, int t, int i, int th, int n, int j>
class Unit {
    public:
    const std::string str() {
        std::ostringstream s;
        if (l != 0) {
            s << format("m", l);
            s << " ";
        }
        if (m != 0) {
            s << format("kg", m);
            s << " ";
        }
        if (t != 0) {
            s << format("s", t);
            s << " ";
        }
        if (i != 0) {
            s << format("A", i);
            s << " ";
        }
        if (th != 0) {
            s << format("K", th);
            s << " ";
        }
        if (n != 0) {
            s << format("mol", n);
            s << " ";
        }
        if (j != 0) {
            s << format("cd", j);
        }
        return s.str();
    }
    
    private:
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
};

/* base SI units */
Unit< 1,  0,  0,  0,  0,  0,  0> meter;
Unit< 0,  1,  0,  0,  0,  0,  0> kilogram;
Unit< 0,  0,  1,  0,  0,  0,  0> second;
Unit< 0,  0,  0,  1,  0,  0,  0> ampere;
Unit< 0,  0,  0,  0,  1,  0,  0> kelvin;
Unit< 0,  0,  0,  0,  0,  1,  0> mole;
Unit< 0,  0,  0,  0,  0,  0,  1> candela;

/* derived SI units */
Unit<-1,  1, -2,  0,  0,  0,  0> pascal;
Unit< 1,  1, -2,  0,  0,  0,  0> newton;
Unit< 0,  0,  1,  1,  0,  0,  0> coulomb;

/* multiply a Unit by a Unit, eg. meter*kilogram */
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


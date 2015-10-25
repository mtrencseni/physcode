#include "Quantity.h"
#include "Vec.h"

template<int l, int m, int t, unsigned int n, class T>
struct VecQuantity {
    Vec<n, T> value;
    Quantity (Vec<n, T> v) : value(v) {}
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

/* multiply a VecQuantity by a Unit, eg. (1*meter)*meter */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, n, T> operator*(VecQuantity<l1, m1, t1, n, T> q1, Unit<l2, m2, t2> u2)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, n, T>(q1.value);
}

/* divide a VecQuantity by a Unit, eg. (1*meter)/second */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
Quantity<l1-l2, m1-m2, t1-t2, n, T> operator/(VecQuantity<l1, m1, t1, n, T> q1, Unit<l2, m2, t2> u2)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, n, T>(q1.value);
}

/* multiply a Vec by a Unit to get a VecQuantity, eg. 5.0 * meter */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(Vec<n, T> val, Unit<l, m, t> u)
{
    return VecQuantity<l, m, t, n, T>(val);
}

/* divide a Vec by a Unit to get a VecQuantity, eg. 5.0 / second */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator/(Vec<n, t> val, Unit<l, m, t> u)
{
    return VecQuantity<-l, -m, -t, n, T>(val);
}

/* multiply a T by a VecQuantity to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(T val, VecQuantity<l, m, t, n, T> q)
{
    return VecQuantity<l, m, t, n, T>(val * q.value);
}

/* multiply a VecQuantity by a T to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(VecQuantity<l, m, t, n, T> q, T val)
{
    return VecQuantity<l, m, t, n, T>(val * q.value);
}

/* divide a VecQuantity by T to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator/(VecQuantity<l, m, t, n, T> q, T val)
{
    return VecQuantity<l, m, t, n, T>(q.value / val);
}

/* multiply two VecQuantities */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
Quantity<l1+l2, m1+m2, t1+t2, T> operator*(VecQuantity<l1, m1, t1, n, T> q1, Quantity<l2, m2, t2, n, T> q2)
{
    T res = q1.value * q2.value; // this is scalar product of two Vec<n, T>s
    return VecQuantity<l1+l2, m1+m2, t1+t2, R>(res);
}

/* divide a VecQuantity by a Quantity */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1-l2, m1-m2, t1-t2, n, T> operator/(VecQuantity<l1, m1, t1, n, T> q1, Quantity<l2, m2, t2, T> q2)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, n, T>(q1.value / q2.value);
}

/* add two VecQuantities */
template<int l, int m, int t, class T>
VecQuantity<l, m, t, n, T> operator+(VecQuantity<l, m, t, n, T> q1, VecQuantity<l, m, t, n, T> q2)
{
    return VecQuantity<l, m, t, n, T>(q1.value + q2.value);
}

/* divide two VecQuantities */
template<int l, int m, int t, class T>
VecQuantity<l, m, t, n, T> operator-(VecQuantity<l, m, t, n, T> q1, VecQuantity<l, m, t, n, T> q2)
{
    return VecQuantity<l, m, t, n, T>(q1.value - q2.value);
}

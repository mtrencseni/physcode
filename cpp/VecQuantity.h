#include "Quantity.h"
#include "Vec.h"

/* === VecQuantity === */
/*
 *
 * A quantity represent a physical quantity with a magnitude:
 * a numeric vector (like <1.2, 5.5>) and a dimension (like m/s).
 * Right now it supports length, mass and time.
 *
 */

template<int l, int m, int t, unsigned int n, class T>
struct VecQuantity {
    Vec<n, T> val;
    VecQuantity (const Vec<n, T>& val_) : val(val_) {}
    VecQuantity () : val(0) {}
    VecQuantity& operator=(const T& v) {
        for (auto i = 0; i < n; i++)
        val[i] = v;
        return *this;
    }
    Vec<n, T> value() const { return val; }
    std::string str() const {
        Unit<l, m, t> u;
        std::ostringstream s;
        s << val.str();
        s << " ";
        s << u.str();
        return s.str();
    }
    friend std::ostream& operator<<(std::ostream& o, Quantity<l, m, t, T>& q) {
        o << (std::string)q;
        return o;
    }
};

/* multiply a VecQuantity by a Quantity to get a VecQuantity*/
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, n, T> operator*(const VecQuantity<l1, m1, t1, n, T>& vq1,
                                                 const Quantity<l2, m2, t2, T>& q2)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, n, T>(vq1.value() * q2.value());
}

/* multiply a Quantity by a VecQuantity to get a VecQuantity*/
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, n, T> operator*(const Quantity<l2, m2, t2, T>& q1,
                                                 const VecQuantity<l1, m1, t1, n, T>& vq2)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, n, T>(q1.value() * vq2.value());
}

/* multiply a VecQuantity by a Unit, eg. (1*meter)*meter */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, n, T> operator*(const VecQuantity<l1, m1, t1, n, T>& vq1,
                                                 const Unit<l2, m2, t2>&)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, n, T>(vq1.value());
}

/* divide a VecQuantity by a Unit, eg. (1*meter)/second */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1-l2, m1-m2, t1-t2, n, T> operator/(const VecQuantity<l1, m1, t1, n, T>& vq1,
                                                 const Unit<l2, m2, t2>&)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, n, T>(vq1.value());
}

/* multiply a Vec by a Unit to get a VecQuantity, eg. 5.0 * meter */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(const Vec<n, T>& val1,
                                     const Unit<l, m, t>&)
{
    return VecQuantity<l, m, t, n, T>(val1);
}

/* divide a Vec by a Unit to get a VecQuantity, eg. 5.0 / second */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator/(const Vec<n, T>& val1,
                                     const Unit<l, m, t>&)
{
    return VecQuantity<-l, -m, -t, n, T>(val1);
}

/* multiply a Quantity by a Vec to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(const Quantity<l, m, t, T>& q1,
                                     const Vec<n, T>& v2)
{
    return VecQuantity<l, m, t, n, T>(q1.value() * v2);
}

/* multiply a T by a VecQuantity to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(const T& val1,
                                     const VecQuantity<l, m, t, n, T>& vq2)
{
    return VecQuantity<l, m, t, n, T>(val1 * vq2.value());
}

/* multiply a VecQuantity by a T to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator*(const VecQuantity<l, m, t, n, T>& vq1,
                                     const T& val2)
{
    return VecQuantity<l, m, t, n, T>(val2 * vq1.value());
}

/* divide a VecQuantity by T to get a VecQuantity */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator/(const VecQuantity<l, m, t, n, T>& vq1,
                                     const T& val2)
{
    return VecQuantity<l, m, t, n, T>(vq1.value() / val2);
}

/* multiply two VecQuantities */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
Quantity<l1+l2, m1+m2, t1+t2, T> operator*(const VecQuantity<l1, m1, t1, n, T>& vq1,
                                           const VecQuantity<l2, m2, t2, n, T>& vq2)
{
    T res = vq1.value() * vq2.value(); // this is scalar product of two Vec<n, T>s
    return Quantity<l1+l2, m1+m2, t1+t2, T>(res);
}

/* divide a VecQuantity by a Quantity */
template<int l1, int m1, int t1, int l2, int m2, int t2, unsigned int n, class T>
VecQuantity<l1-l2, m1-m2, t1-t2, n, T> operator/(const VecQuantity<l1, m1, t1, n, T>& vq1,
                                                 const Quantity<l2, m2, t2, T>& q2)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, n, T>(vq1.value() / q2.value());
}

/* add two VecQuantities */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator+(const VecQuantity<l, m, t, n, T>& vq1,
                                     const VecQuantity<l, m, t, n, T>& vq2)
{
    return VecQuantity<l, m, t, n, T>(vq1.value() + vq2.value());
}

/* subtract two VecQuantities */
template<int l, int m, int t, unsigned int n, class T>
VecQuantity<l, m, t, n, T> operator-(const VecQuantity<l, m, t, n, T>& vq1,
                                     const VecQuantity<l, m, t, n, T>& vq2)
{
    return VecQuantity<l, m, t, n, T>(vq1.value() - vq2.value());
}

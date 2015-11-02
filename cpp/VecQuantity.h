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

template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
struct VecQuantity {
    Vec<dim, T> val;
    VecQuantity (const Vec<dim, T>& val_) : val(val_) {}
    VecQuantity () : val(0) {}
    VecQuantity& operator=(const T& v) {
        for (auto k = 0; k < dim; k++)
        val[k] = v;
        return *this;
    }
    Vec<dim, T> value() const { return val; }
    std::string str() const {
        Unit<l, m, t, i, th, n, j> u;
        std::ostringstream s;
        s << val.str();
        s << " ";
        s << u.str();
        return s.str();
    }
    friend std::ostream& operator<<(std::ostream& o, Quantity<l, m, t, i, th, n, j, T>& q) {
        o << (std::string)q;
        return o;
    }
};

/* multiply a VecQuantity by a Quantity to get a VecQuantity*/
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>
    operator*(
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq1,
    const Quantity<   l2, m2, t2, i2, th2, n2, j2, T>& q2)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>(vq1.value() * q2.value());
}

/* multiply a Quantity by a VecQuantity to get a VecQuantity*/
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>
    operator*(
    const Quantity<   l2, m2, t2, i2, th2, n2, j2, T>& q1,
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq2)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>(q1.value() * vq2.value());
}

/* multiply a VecQuantity by a Unit, eg. (1*meter)*meter */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>
    operator*(
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq1,
    const Unit<       l2, m2, t2, i2, th2, n2, j2>&)
{
    return VecQuantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, dim, T>(vq1.value());
}

/* divide a VecQuantity by a Unit, eg. (1*meter)/second */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
VecQuantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, dim, T>
    operator/(
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq1,
    const Unit<       l2, m2, t2, i2, th2, n2, j2>&)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, dim, T>(vq1.value());
}

/* multiply a Vec by a Unit to get a VecQuantity, eg. 5.0 * meter */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator*(
    const Vec<dim, T>& val1,
    const Unit<l, m, t, i, th, n, j>&)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(val1);
}

/* divide a Vec by a Unit to get a VecQuantity, eg. 5.0 / second */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator/(
    const Vec<dim, T>& val1,
    const Unit<l, m, t, i, th, n, j>&)
{
    return VecQuantity<-l, -m, -t, -i, -th, -n, -j, dim, T>(val1);
}

/* multiply a Quantity by a Vec to get a VecQuantity */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator*(
    const Quantity<l, m, t, i, th, n, j, T>& q1,
    const Vec<dim, T>& v2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(q1.value() * v2);
}

/* multiply a T by a VecQuantity to get a VecQuantity */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator*(const T& val1,
    const VecQuantity<l, m, t, i, th, n, j, dim,
    T>& vq2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(val1 * vq2.value());
}

/* multiply a VecQuantity by a T to get a VecQuantity */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator*(
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq1,
    const T& val2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(val2 * vq1.value());
}

/* divide a VecQuantity by T to get a VecQuantity */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator/(
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq1,
    const T& val2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(vq1.value() / val2);
}

/* multiply two VecQuantities */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>
    operator*(
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq1,
    const VecQuantity<l2, m2, t2, i2, th2, n2, j2, dim, T>& vq2)
{
    T res = vq1.value() * vq2.value(); // this is scalar product of two Vec<n, T>s
    return Quantity<l1+l2, m1+m2, t1+t2, i1+i2, th1+th2, n1+n2, j1+j2, T>(res);
}

/* divide a VecQuantity by a Quantity */
template<int l1, int m1, int t1, int i1, int th1, int n1, int j1,
         int l2, int m2, int t2, int i2, int th2, int n2, int j2, unsigned int dim, class T>
VecQuantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, dim, T>
    operator/(
    const VecQuantity<l1, m1, t1, i1, th1, n1, j1, dim, T>& vq1,
    const Quantity<   l2, m2, t2, i2, th2, n2, j2, T>& q2)
{
    return VecQuantity<l1-l2, m1-m2, t1-t2, i1-i2, th1-th2, n1-n2, j1-j2, dim, T>(vq1.value() / q2.value());
}

/* add two VecQuantities */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator+(
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq1,
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(vq1.value() + vq2.value());
}

/* subtract two VecQuantities */
template<int l, int m, int t, int i, int th, int n, int j, unsigned int dim, class T>
VecQuantity<l, m, t, i, th, n, j, dim, T>
    operator-(
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq1,
    const VecQuantity<l, m, t, i, th, n, j, dim, T>& vq2)
{
    return VecQuantity<l, m, t, i, th, n, j, dim, T>(vq1.value() - vq2.value());
}

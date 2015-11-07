#include <assert.h>
#include <string>
#include <sstream>

/* === Vec === */
/*
 *
 * A very simple vector class to store n values each of type T.
 *
 */

template<unsigned int dim, class T>
struct Vec {
    T val[dim];
    std::string str() const {
        std::ostringstream s;
        s << "(";
        for (auto i = 0; i < dim; i++) {
            s << val[i];
            if (i < (dim-1))
                s << ", ";
        }
        s << ")";
        return s.str();
    }
    T& operator[](unsigned int i) {
        assert(i < dim);
        return val[i];
    }
};

/* add two Vecs */
template<unsigned int dim, class T>
Vec<dim, T> operator+(const Vec<dim, T>& a, const Vec<dim, T>& b) {
    Vec<dim, T> res;
    for (auto i = 0; i < dim; i++)
        res.val[i] = a.val[i] + b.val[i];
    return res;
}

/* subtract two Vecs */
template<unsigned int dim, class T>
Vec<dim, T> operator-(const Vec<dim, T>& a, const Vec<dim, T>& b) {
    Vec<dim, T> res;
    for (auto i = 0; i < dim; i++)
        res.val[i] = a.val[i] - b.val[i];
    return res;
}

/* multiply two Vecs */
template<unsigned int dim, class T>
T operator*(const Vec<dim, T>& a, const Vec<dim, T>& b) {
    T res = 0;
    for (auto i = 0; i < dim; i++)
        res += (a.val[i] * b.val[i]);
    return res;
}

/* multiply Vec by a scalar */
template<unsigned int dim, class T>
Vec<dim, T> operator*(const Vec<dim, T>& a, const T& b) {
    Vec<dim, T> res;
    for (auto i = 0; i < dim; i++)
        res.val[i] = a.val[i] * b;
    return res;
}

/* multiply a scalar by a Vec */
template<unsigned int dim, class T>
Vec<dim, T> operator*(const T& b, const Vec<dim, T>& a) {
    Vec<dim, T> res;
    for (auto i = 0; i < dim; i++)
        res.val[i] = a.val[i] * b;
    return res;
}

/* divide a Vec by a scalar */
template<unsigned int dim, class T>
Vec<dim, T> operator/(const Vec<dim, T>& a, const T& b) {
    Vec<dim, T> res;
    for (auto i = 0; i < dim; i++)
        res.val[i] = a.val[i] / b;
    return res;
}

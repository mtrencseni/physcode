#include <string>
#include <sstream>

template<unsigned int n, class T>
struct Vec {
    T val[n];
    const std::string str() {
        std::ostringstream s;
        s << "(";
        for (auto i = 0; i < n; i++) {
            s << val[i];
            if (i < (n-1))
                s << ", ";
        }
        s << ")";
        return s.str();
    }
};

/* add two Vecs */
template<unsigned int n, class T>
Vec<n, T> operator+(const Vec<n, T>& a, const Vec<n, T>& b) {
    Vec<n, T> res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] + b.val[i];
    return res;
}

/* subtract two Vecs */
template<unsigned int n, class T>
Vec<n, T> operator-(const Vec<n, T>& a, const Vec<n, T>& b) {
    Vec<n, T> res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] - b.val[i];
    return res;
}

/* multiply two Vecs */
template<unsigned int n, class T>
T operator*(const Vec<n, T>& a, const Vec<n, T>& b) {
    T res = 0;
    for (auto i = 0; i < n; i++)
        res += (a.val[i] * b.val[i]);
    return res;
}

/* multiply Vec by a scalar */
template<unsigned int n, class T>
Vec<n, T> operator*(const Vec<n, T>& a, const T& b) {
    Vec<n, T> res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] * b;
    return res;
}

/* multiply a scalar by a Vec */
template<unsigned int n, class T>
Vec<n, T> operator*(const T& b, const Vec<n, T>& a) {
    Vec<n, T> res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] * b;
    return res;
}

/* divide a Vec by a scalar */
template<unsigned int n, class T>
Vec<n, T> operator/(const Vec<n, T>& a, const T& b) {
    Vec<n, T> res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] / b;
    return res;
}

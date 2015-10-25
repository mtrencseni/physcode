
template<unsigned int n, class T>
struct Vec {
    T val[n];
};

/* add two Vecs */
template<unsigned int n, class T>
Vec<n, T> operator+(Vec<n, T> a, Vec<n, T> b) {
    T res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] + b.val[i];
    return res;
}

/* subtract two Vecs */
template<unsigned int n, class T>
Vec<n, T> operator-(Vec<n, T> a, Vec<n, T> b) {
    T res;
    for (auto i = 0; i < n; i++)
        res.val[i] = a.val[i] - b.val[i];
    return res;
}

/* multiply two Vecs */
template<unsigned int n, class T>
T operator*(Vec<n, T> a, Vec<n, T> b) {
    T res;
    for (auto i = 0; i < n; i++)
        res += (a.val[i] * b.val[i]);
    return res;
}

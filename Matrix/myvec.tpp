//
//  myvec.tpp
//  Matrix
//
//  Created by Sylvan Canales on 8/3/21.
//  Copyright © 2021 Sylvan Canales. All rights reserved.
//

#include <algorithm>
#include <numeric>
#include <cmath>
#include <type_traits>

template <typename T, size_t N>
MyVec<T,N>::MyVec() :
    data_(std::array<T,N>())
{
    static_assert (std::is_arithmetic_v<T>, "MyVec requires an arithmetic type");
}

template <typename T, size_t N>
MyVec<T,N>::MyVec(std::initializer_list<T> li) :
    data_(std::array<T,N>())
{
    static_assert (std::is_arithmetic_v<T>, "MyVec requires an arithmetic type");
    size_t count = std::min(N, li.size());
    std::copy_n(li.begin(), count, data_.begin());
}

template <typename T, size_t N>
template <typename Iter>
MyVec<T,N>::MyVec(Iter first, Iter last) :
    data_(std::array<T,N>())
{
    static_assert (std::is_arithmetic_v<typename std::iterator_traits<Iter>::value_type>, "MyVec requires an arithmetic type");
    auto n = static_cast<int>(N);
    auto rangeDist = static_cast<int>(std::distance(first, last));
    if (rangeDist > 0) {
        auto count = std::min(n, rangeDist);
        std::copy_n(first, count, data_.begin());
    }
}

template <typename T, size_t N>
T& MyVec<T,N>::operator[](size_t i)
{
    return data_[i];
}

template <typename T, size_t N>
const T& MyVec<T,N>::operator[](size_t i) const
{
    return data_[i];
}

template <typename T, size_t N>
MyVec<T,N>& MyVec<T,N>::operator+=(const MyVec &rhs)
{
    std::transform(rhs.data_.cbegin(), rhs.data_.cend(), data_.cbegin(), data_.begin(), std::plus<>());
    return *this;
}

template <typename T, size_t N>
MyVec<T,N>& MyVec<T,N>::operator-=(const MyVec &rhs)
{
    std::transform(rhs.data_.cbegin(), rhs.data_.cend(), data_.cbegin(), data_.begin(), std::minus<>());
    return *this;
}

template <typename T, size_t N>
MyVec<T,N>& MyVec<T,N>::operator*=(double rhs)
{
    std::for_each(data_.begin(), data_.end(), [rhs](double &v) { v *= rhs; });
    return *this;
}

template <typename T, size_t N>
double MyVec<T,N>::mag() const
{
    return sqrt(mag2());
}

template <typename T, size_t N>
T MyVec<T,N>::mag2() const
{
    return std::accumulate(data_.cbegin(), data_.cend(), 0, [](const T &sum, const T &el) {
        return sum + el * el;
    });
}

template <typename T, size_t N>
template <typename T2>
double MyVec<T,N>::dot(const MyVec<T2,N> &rhs) const
{
    double product = 0.0;
    for (size_t i = 0; i < N; ++i) {
        product += data_[i] * rhs[i];
    }
    return product;
}

template <typename T, size_t N>
template <typename T2, size_t N2>
MyVec<T,3> MyVec<T,N>::cross(const MyVec<T2,N2> &rhs) const
{
    static_assert (N == 2 || N == 3, "Vector cross product requires vector of length 2 or 3");
    T lz  = (N == 2)  ? 0 : data_[2];
    T2 rz = (N2 == 2) ? 0 : rhs[2];
    return {data_[1] * rz - lz * rhs[1],
            lz * rhs[0] - data_[0] * rz,
            data_[0] * rhs[1] - data_[1] * rhs[0]};
}

// Related non-members
template <typename T, size_t N>
MyVec<T,N> operator*(double scalar, const MyVec<T,N> &vec)
{
    MyVec<T,N> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return scalar * v;} );
    return result;
}

template <typename T, size_t N>
MyVec<T,N> operator*(const MyVec<T,N> &vec, double scalar)
{
    MyVec<T,N> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return scalar * v;} );
    return result;
}

template <typename T, size_t N>
MyVec<T,N> operator/(const MyVec<T,N> &vec, double scalar)
{
    MyVec<T,N> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return v / scalar;} );
    return result;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const MyVec<T,N> &v)
{
    for (const auto & val : v) {
        os << val << " ";
    }
    return os;
}


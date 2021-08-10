//
//  myvec.tpp
//  Matrix
//
//  Created by Sylvan Canales on 8/3/21.
//

#include <algorithm>
#include <numeric>
#include <cmath>
#include <type_traits>

namespace MyVector {

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
MyVec<T,N>& MyVec<T,N>::normalize()
{
    double mag = magnitude(*this);
    if (almost_equal(mag, 0.0, 2)) {
        return *this;
    }
    
    double invMagnitude = 1 / mag;
    std::for_each(data_.begin(), data_.end(), [invMagnitude](T &n) { n *= invMagnitude; });
    return *this;
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

// Related non-members

template <typename T, size_t N>
double magnitude(const MyVec<T,N> &vec)
{
    return sqrt(magnitude2(vec));
}

// Square of the magnitude
template <typename T, size_t N>
T magnitude2(const MyVec<T,N> &vec)
{
    return std::accumulate(vec.cbegin(), vec.cend(), 0, [](const T &sum, const T &el) {
        return sum + el * el;
    });
}

template <typename T, size_t N, typename T2, size_t N2>
double angle(const MyVec<T,N> &lhs, MyVec<T2,N2> &rhs)
{
    double magLhs = magnitude(lhs);
    double magRhs = magnitude(rhs);
    if (almost_equal(magLhs, 0., 2) ||
        almost_equal(magRhs, 0., 2)) {
        return M_PI_2;
    }
    
    return std::acos( dotProduct(lhs, rhs) / (magLhs * magRhs));
}

template <typename T, size_t N, typename T2>
double dotProduct(const MyVec<T,N> &lhs, const MyVec<T2,N> &rhs)
{
    double product = 0.0;
    for (size_t i = 0; i < N; ++i) {
        product += lhs[i] * rhs[i];
    }
    return product;
}

template <typename T, size_t N, typename T2, size_t N2>
MyVec<T,3> crossProduct(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs)
{
    static_assert (N == 2 || N == 3, "Vector cross product requires vector of length 2 or 3");
    static_assert (N2 == 2 || N2 == 3, "Vector cross product requires vector of length 2 or 3");
    T lz = 0;
    T rz = 0;
    if constexpr (N == 3) {
        lz = lhs[2];
    }
    if constexpr (N2 == 3) {
        rz = rhs[2];
    }
    MyVec<T,3> ret;
    ret[0] = lhs[1] * rz - lz * rhs[1];
    ret[1] = lz * rhs[0] - lhs[0] * rz;
    ret[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return ret;
}

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

template <typename T, size_t N, typename T2, size_t N2>
bool operator==(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs)
{
    if constexpr (N != N2) {
        return false;
    }
    if constexpr (std::is_integral_v<T> || std::is_integral_v<T2>) {
        for (size_t i = 0; i < N; ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    else {
        for (size_t i = 0; i < N; ++i) {
            if (!almost_equal(lhs[i], rhs[i], 2)) {
                return false;
            }
        }
        return true;
    }
}

template <typename T, size_t N, typename T2, size_t N2>
bool operator!=(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs)
{
    return !(lhs == rhs);
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const MyVec<T,N> &v)
{
    for (const auto & val : v) {
        os << val << " ";
    }
    return os;
}

} // namespace MyVector

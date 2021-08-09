//
//  myvec.h
//  Matrix
//
//  Created by Sylvan Canales on 8/3/21.
//

#ifndef MYVEC_H
#define MYVEC_H

#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include "utils.h"

/*!
 * \brief A container abstraction that represents a Euclidean vector
 * \details MyVec represents a vector, typically having some magnitude and direction.
 * Although typically used to represent a 2D or 3D direction (position),
 * there isn't an imposed limit on the number of elements in this container.
 * Using the template parameters, you can specify different arithmetic value types, and the number of components of the vector.
 * By default, the vector is a 3D vector of type double. Using the default
 * template parameters, here are a few examples of instantiation:
 *
 * \verbatim
 * MyVec<> vec;   // 3-component vector, type double
 * MyVec<int> vec;  // 3-component vector, type int
 * MyMat<int, 2> mat;   // 2-component vector, type int
 * \endverbatim
 *
 * A limited set of vector operations is supported. These include basic arithmetic such as
 * addition, subtraction, scalar multiply/divide. Also available are vector dot product,
 * cross product (for 2 or 3D vectors only), and the vectors can be queried for magnitude.
 */
namespace MyVector {

template <typename T = double, size_t N = 3>
class MyVec {
public:
    MyVec();
    MyVec(std::initializer_list<T>);

    template <typename Iter>
    MyVec(Iter first, Iter last);

    ~MyVec() = default;

    MyVec(const MyVec &) = default;
    MyVec& operator=(const MyVec &) = default;

    MyVec(MyVec &&) noexcept = default;
    MyVec& operator=(MyVec &&) noexcept = default;
    
    MyVec& normalize();

    constexpr auto begin() noexcept { return data_.begin(); }
    constexpr auto begin() const noexcept { return data_.begin(); }
    constexpr auto cbegin() const noexcept { return data_.cbegin(); }

    constexpr auto end() noexcept { return data_.end(); }
    constexpr auto end() const noexcept { return data_.end(); }
    constexpr auto cend() const noexcept { return data_.cend(); }

    constexpr size_t size() const noexcept { return data_.size(); }
    constexpr bool empty() const noexcept { return data_.empty(); }

          T& operator[](size_t i);
    const T& operator[](size_t i) const;

    MyVec& operator+=(const MyVec &);
    MyVec& operator-=(const MyVec &);
    MyVec& operator*=(double);

    friend MyVec operator+(MyVec lhs, const MyVec &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend MyVec operator-(MyVec lhs, const MyVec &rhs)
    {
        lhs -= rhs;
        return lhs;
    }
    
private:
    std::array<T, N> data_;
};

// Vector magnitude
// 2 versions: magnitude
// magnitude2: square of the magnitude to avoid unnecessary sqrt calculation
template <typename T, size_t N>
T magnitude2(const MyVec<T,N> &);
template <typename T, size_t N>
double magnitude(const MyVec<T,N> &);

template <typename T, size_t N, typename T2, size_t N2>
double angle(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs);

template <typename T, size_t N, typename T2>
double dotProduct(const MyVec<T,N> &lhs, const MyVec<T2,N> &rhs);

template <typename T, size_t N, typename T2, size_t N2>
MyVec<T,3> crossProduct(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs);

// Scalar multiplication and division
template <typename T, size_t N>
MyVec<T,N> operator*(double, const MyVec<T,N> &);
template <typename T, size_t N>
MyVec<T,N> operator*(const MyVec<T,N> &, double);
template <typename T, size_t N>
MyVec<T,N> operator/(const MyVec<T,N> &, double);

// Comparison operators
template <typename T, size_t N, typename T2, size_t N2>
bool operator==(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs);
template <typename T, size_t N, typename T2, size_t N2>
bool operator!=(const MyVec<T,N> &lhs, const MyVec<T2,N2> &rhs);

// Render the vector contents to the output stream
template <typename T, size_t N>
std::ostream& operator<<(std::ostream &, const MyVec<T,N> &);

} // namespace MyVector

#include "myvec.tpp"

#endif // MYVEC_H

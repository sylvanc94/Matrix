//
//  mymat.h
//  Matrix
//
//  Created by Sylvan Canales on 8/3/21.
//

#ifndef MYMAT_H
#define MYMAT_H

#include <iostream>
#include <array>
#include <initializer_list>

/*!
 * \brief A container abstraction that represents a matrix in linear algebra
 * \details MyMat represents a mathematical matrix. Using the template parameters,
 * you can specify different arithmetic value types, and the dimension of the matrix.
 * By default, the matrix is a 3x3 square matrix of type double. Using the default
 * template parameters, here are a few examples of instantiation:
 *
 * \verbatim
 * MyMat<> mat;   // 3x3 matrix, type double
 * MyMat<int> mat;  // 3x3 matrix, type int
 * MyMat<int, 2> mat;   // 2x2 matrix, type int
 * MyMat<double, 2, 3> mat; // 2x3 matrix, type double
 * \endverbatim
 *
 * A limited set of matrix operations is supported. These include basic arithmetic such as
 * addition, subtraction, scalar multiply/divide. Also available are modifers to make
 * the matrix diagonal, or upper/lower triangular.
 *
 * A set of static factory functions can create an identity matrix, or upper/lower triangular
 * matrices with 1/0 values.
 */
namespace MyMatrix {

template <typename T = double, size_t R = 3, size_t C = R>
class MyMat {
public:
    MyMat();
    MyMat(std::initializer_list<T>);

    ~MyMat() = default;

    MyMat(const MyMat &) = default;
    MyMat& operator=(const MyMat &) = default;

    MyMat(MyMat &&) noexcept = default;
    MyMat& operator=(MyMat &&) noexcept = default;
    
    MyMat<T,C,R> copyTransposed() const;
    
    MyMat& toDiagonal();
    MyMat& toUpperTriangular();
    MyMat& toLowerTriangular();
    MyMat& transpose();

    constexpr auto begin() noexcept { return data_.begin(); }
    constexpr auto begin() const noexcept { return data_.begin(); }
    constexpr auto cbegin() const noexcept { return data_.cbegin(); }

    constexpr auto end() noexcept { return data_.end(); }
    constexpr auto end() const noexcept { return data_.end(); }
    constexpr auto cend() const noexcept { return data_.cend(); }

    constexpr size_t size() const noexcept { return data_.size(); }
    constexpr bool  empty() const noexcept { return data_.empty(); }
    size_t rows() const noexcept;
    size_t cols() const noexcept;
    constexpr bool square() const { return R == C; }

          T& operator() (size_t row, size_t col);
    const T& operator() (size_t row, size_t col) const;

    MyMat& operator+=(const MyMat &);
    MyMat& operator-=(const MyMat &);
    MyMat& operator*=(double);

    friend MyMat operator+(MyMat lhs, const MyMat &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    friend MyMat operator-(MyMat lhs, const MyMat &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    std::ostream& renderToStream(std::ostream &) const;

private:
    std::array<T,R*C> data_;
    bool transposed_ = false;
};

// Factory methods
template <typename T = double, size_t R = 3, size_t C = R>
MyMat<T,R,C> makeIdentity();
template <typename T = double, size_t R = 3, size_t C = R>
MyMat<T,R,C> makeUpperTriangular();
template <typename T = double, size_t R = 3, size_t C = R>
MyMat<T,R,C> makeLowerTriangular();

// Scalar multiplication and division
template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator*(double, const MyMat<T,R,C> &);
template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator*(const MyMat<T,R,C> &, double);
template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator/(const MyMat<T,R,C> &, double);

// Comparison
// Note that the matrices may be of different template dimension, but if transposed they can still be logically equal
template <typename T, size_t R, size_t C, size_t R2, size_t C2>
bool operator==(const MyMat<T,R,C> &lhs, const MyMat<T,R2,C2> &rhs);
template <typename T, size_t R, size_t C, size_t R2, size_t C2>
bool operator!=(const MyMat<T, R, C> &, const MyMat<T, R2, C2> &);

// Render the vector contents to the output stream
template <typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream &, const MyMat<T,R,C> &);

} // namespace MyMatrix

#include "mymat.tpp"

#endif // MYMAT_H

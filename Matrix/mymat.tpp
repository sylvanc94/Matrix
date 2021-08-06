//
//  mymat.tpp
//  Matrix
//
//  Created by Sylvan Canales on 8/3/21.
//

#include <algorithm>

template <typename T, size_t R, size_t C>
MyMat<T,R,C>::MyMat() :
    data_(std::array<T, R*C>())
{
    static_assert (std::is_arithmetic_v<T>, "MyMat requires an arithmetic type");
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>::MyMat(std::initializer_list<T> li) :
    data_(std::array<T, R*C>())
{
    static_assert (std::is_arithmetic_v<T>, "MyMat requires an arithmetic type");
    size_t count = std::min(R*C, li.size());
    std::copy_n(li.begin(), count, data_.begin());
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C> MyMat<T,R,C>::identity()
{
    static_assert (R == C, "Identity matrix must be square");
    static_assert (R > 0, "Identity matrix can't be empty");
    MyMat<T,R,C> id;
    for (size_t i = 0; i < R*C; i += C + 1) {
        id.data_[i] = 1;
    }
    return id;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C> MyMat<T,R,C>::upperTriangular()
{
    static_assert (R == C, "Triangular matrix must be square");
    static_assert (R > 0, "Triangular matrix can't be empty");
    MyMat<T,R,C> ut;
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            ut(j,i) = 1;
        }
    }
    return ut;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C> MyMat<T,R,C>::lowerTriangular()
{
    static_assert (R == C, "Triangular matrix must be square");
    static_assert (R > 0, "Triangular matrix can't be empty");
    MyMat<T,R,C> lt;
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            lt(i,j) = 1;
        }
    }
    return lt;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::toDiagonal()
{
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            if (i != j) {
                (*this)(i,j) = 0;
            }
        }
    }
    return *this;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::toUpperTriangular()
{
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < i; ++j) {
            (*this)(i,j) = 0;
        }
    }
    return *this;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::transpose()
{
    transposed_ = !transposed_;
    return *this;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::toLowerTriangular()
{
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < i; ++j) {
            (*this)(j,i) = 0;
        }
    }
    return *this;
}

template <typename T, size_t R, size_t C>
constexpr
size_t MyMat<T,R,C>::rows() const noexcept
{
    return transposed_ ? C : R;
}

template <typename T, size_t R, size_t C>
constexpr
size_t MyMat<T,R,C>::cols() const noexcept
{
    return transposed_ ? R : C;
}

template <typename T, size_t R, size_t C>
T& MyMat<T,R,C>::operator()(size_t row, size_t col)
{
    if (transposed_) {
        return data_[col * C + row];
    }
    else {
        return data_[row * C + col];
    }
}

template <typename T, size_t R, size_t C>
const T& MyMat<T,R,C>::operator()(size_t row, size_t col) const
{
    if (transposed_) {
        return data_[col * C + row];
    }
    else {
        return data_[row * C + col];
    }
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::operator+=(const MyMat &rhs)
{
    std::transform(rhs.cbegin(), rhs.cend(), cbegin(), begin(), std::plus<>());
    return *this;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::operator-=(const MyMat &rhs)
{
    std::transform(rhs.cbegin(), rhs.cend(), cbegin(), begin(), std::minus<>());
    return *this;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C>& MyMat<T,R,C>::operator*=(double rhs)
{
    std::for_each(begin(), end(), [rhs](double &v) { v *= rhs; });
    return *this;
}

template <typename T, size_t R, size_t C>
std::ostream& MyMat<T,R,C>::renderToStream(std::ostream &os) const
{
    auto numRows = rows();
    auto numCols = cols();
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            os << (*this)(i,j) << " ";
        }
        os << "\n";
    }

    return os;
}

// Related non-members
template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator*(double scalar, const MyMat<T,R,C> &vec)
{
    MyMat<T,R,C> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return scalar * v;} );
    return result;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator*(const MyMat<T,R,C> &vec, double scalar)
{
    MyMat<T,R,C> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return scalar * v;} );
    return result;
}

template <typename T, size_t R, size_t C>
MyMat<T,R,C> operator/(const MyMat<T,R,C> &vec, double scalar)
{
    MyMat<T,R,C> result;
    std::transform(vec.cbegin(), vec.cend(), result.begin(), [scalar](const T &v) { return v / scalar;} );
    return result;
}

template <typename T, size_t R, size_t C, size_t R2, size_t C2>
bool operator==(const MyMat<T,R,C> &lhs, const MyMat<T,R2,C2> &rhs)
{
    // Do the rows and columns match? (Taking into account whether the matrix is transposed internally)
    auto numRows = lhs.rows();
    auto numCols = lhs.cols();

    if (numRows != rhs.rows() ||
        numCols != rhs.cols()) {
        return false;
    }

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (lhs(i,j) != rhs(i,j)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream &os, const MyMat<T,R,C> &m)
{
    return m.renderToStream(os);
}

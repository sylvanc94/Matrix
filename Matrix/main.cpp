//
//  main.cpp
//  Matrix
//
//  Created by Sylvan on 8/4/21.
//

#include <iostream>
#include <vector>
#include "myvec.h"
#include "mymat.h"

using namespace std;
using namespace MyVector;
using namespace MyMatrix;

int main()
{
    cout << "Hello World!" << endl;
//    auto id = MyMat<double>::identity();
//    cout << id << endl;
//    auto id2 = makeIdentity();
    MyMat id2 = makeIdentity<double,3,3>();
    cout << id2 << endl;
    
    MyMat id3 = makeIdentity<double,5>();
    cout << id3 << endl;

//    cout << MyMat<double>::upperTriangular() << endl;
//    cout << MyMat<double>::lowerTriangular() << endl;
    cout << makeUpperTriangular() << endl;
    cout << makeLowerTriangular() << endl;

    MyMat<double> mat;
    cout << mat << endl;

    MyMat<double, 4> mat2;
    cout << mat2 << endl;

    MyMat<double, 4, 6> mat3;
    cout << mat3 << endl;

    MyMat matInit {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9};
    cout << matInit << endl;
//    cout << matInit.toDiagonal() << endl;
//    cout << matInit.toUpperTriangular() << endl;
    cout << matInit.toLowerTriangular() << endl;

    vector<int> v;
    v.push_back(1);
    MyVec<int> mv(v.begin(), v.end());
    vector<char> vs;
    MyVec<> mvs(vs.begin(), vs.end());
    cout << mv << endl;
    MyVec<int, 2> vecEmpty;
    cout << vecEmpty << endl;
    MyVec<double, 3> vec3{1, 2, 3};
    cout << vec3 << endl;

    MyVec<double, 2> vec2{1, 2};
    MyVec<int, 2> vecInt2{1, 2};
    cout << vec2 << endl;
    cout << "Vec compare" << endl;
    cout << std::boolalpha << (vec2 == vecInt2) << endl;

    MyVec defaultVec;

    MyVec<int, 3> vecInt{1, 2, 3};
    cout << magnitude2(vecInt) << endl;
    cout << magnitude(vecInt) << endl;
    MyVec<double, 3> vecDouble2{1.2, 3.5, 6.28};
    vecDouble2 = vec3;
    
    cout << "Dot product: " << dotProduct(vecInt, vecDouble2) << endl;

    cout << "2 * vec: " << 2 * vecDouble2 << endl;
    cout << "vec * 2: " << vecDouble2 * 2 << endl;
    cout << "vec / 2: " << vecDouble2 / 2 << endl;

//    vec2 = vec3;  // different length, shouldn't compile.
    MyVec<int, 3> crossA{1, 2};
    MyVec<int, 2> crossB{1, 5};
    cout << "Cross product:" << endl;
//    cout << crossA.cross(crossB) << endl;
    cout << crossProduct(crossA, crossB) << endl;

    MyMat<double, 2, 3> matOrig = {1, 3, 5,
                          2, 4, 6};

    cout << matOrig << endl;
    MyMat<double,2,3> matT = matOrig.transpose();
    cout << matT << endl;
    cout << matT.transpose() << endl;
    cout << matT.transpose() << endl;
//    cout << std::boolalpha << (matT == matT.transpose()) << endl;

    MyMat<double,1,3> exp = {1, 2, 3};
    MyMat<double,3,1> exp2 = {1,2,3};

    cout << exp << endl << exp2 << endl;
    cout << std::boolalpha << (exp == exp) << endl;
    cout << (exp == exp2) << endl;
    cout << (exp == exp2.transpose()) << endl;
    
    auto expT = exp.copyTransposed();
    cout << "exp" << endl;
    cout << exp << endl;
    cout << "exp Transposed" << endl;
    cout << expT << endl;

    MyMat matA = {1,2,3,
                 4,5,6,
                 7,8,9};
    MyMat matB = {1,2,3,
                 4,5,6,
                 7,8,9};

    cout << (matA == matB) << endl;
    cout << (matA == matB.transpose()) << endl;
    
    cout << "MatA" << endl;
    cout << matA << endl;
    
    cout << "MatA copy transposed" << endl;
    auto tc = matA.copyTransposed();
    cout << tc << endl;
    
    MyVec<double> normVec { 1, 1, 1};
    cout << normVec << ",  " << normVec.normalize() << endl;
    cout << (normVec == normVec) << endl;
    
    MyVec<double, 2> vec10 {1,0};
    MyVec<double, 2> vec11 {0,1};
//    cout << rad2deg(vec10.angleTo(vec11)) << endl;
    cout << rad2deg(angle(vec10, vec11)) << endl;
    return 0;
}

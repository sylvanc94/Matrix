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

int main()
{
    cout << "Hello World!" << endl;
    auto id = MyMat<double>::identity();
    cout << id << endl;

    cout << MyMat<double>::upperTriangular() << endl;
    cout << MyMat<double>::lowerTriangular() << endl;

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
    cout << vec2 << endl;

    MyVec<> defaultVec;

    MyVec<int, 3> vecInt{1, 2, 3};
    cout << vecInt.mag2() << endl;
    cout << vecInt.mag() << endl;
    MyVec<double, 3> vecDouble2{1.2, 3.5, 6.28};
    vecDouble2 = vec3;

    cout << "2 * vec: " << 2 * vecDouble2 << endl;
    cout << "vec * 2: " << vecDouble2 * 2 << endl;
    cout << "vec / 2: " << vecDouble2 / 2 << endl;

//    vec2 = vec3;  // different length, shouldn't compile.
    MyVec<int, 3> crossA{1, 2};
    MyVec<int, 2> crossB{1, 5};
    cout << crossA.cross(crossB) << endl;

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

    MyMat matA = {1,2,3,
                 4,5,6,
                 7,8,9};
    MyMat matB = {1,2,3,
                 4,5,6,
                 7,8,9};

    cout << (matA == matB) << endl;
    cout << (matA == matB.transpose()) << endl;
    
    MyVec<double> normVec { 1, 1, 1};
    cout << normVec << ",  " << normVec.normalize() << endl;
    cout << (normVec == normVec) << endl;
    
    return 0;
}

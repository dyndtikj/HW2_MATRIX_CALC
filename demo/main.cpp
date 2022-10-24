#include <iostream>
#include "m_vector.h"
#include "m_matrix.h"

int main(){

//    MVector vec({2, 112, 1, 111});
//    MVector vec2 = vec;
//    auto vec3 = vec2;
//    vec3[0] = 11111;
//    vec2.Print();
// MMatrix(MVector *vectors, const size_t &rows);
    MVector* vecs = new MVector[3]{MVector{12, 2}, MVector{2, 2}, MVector{2, 3}};
    MMatrix mat(vecs, 3);
//    EXPECT_EQ(mat.Rows(), 3);
//    EXPECT_EQ(mat.Cols(), 2);
//    EXPECT_EQ(mat.Capacity(), 3);
//    EXPECT_TRUE(CmpMat(mat,{{1, 1},{2, 2}, {3, 3}}));
    mat.Print();
//    delete[] vecs;
//    MVector test;
//    test.PushBack(1);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//    test.PushBack(2);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//    test.PushBack(3);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//
//
//    MMatrix test121;
//    test121.PushBackC({1,2 ,3});
//    test121.Print();
//    test121.PushBackC({11,21 ,13});
//    test121.Print();
//    test121.PushBackC({111,211 ,131});
//    test121.Print();
//
//    MMatrix mat({
//                        {1, 2, 3, 4},
//                        {5, 6, 7, 8},
//                        {9, 10, 11, 12},
//                });
//    auto res = mat.SliceC(0, 2, 1);
//    res.Print();
}
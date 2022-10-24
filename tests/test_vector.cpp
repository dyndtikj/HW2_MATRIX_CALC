#include <gtest/gtest.h>
#include "m_vector.h"
#include "m_matrix.h"
bool CmpVec(const MVector& vec, const std::initializer_list<double>& il){
    if (vec.Size() != il.size()) {
        return false;
    }
    for (size_t i = 0; i < vec.Size(); i++) {
        // double numbers compare ...
        if (std::abs(vec[i] - *(il.begin() + i)) > 0.00000001) {
            return false;
        }
    }
    return true;
}

TEST(TestConstructorsVector, Default) {
    MVector vec;
    EXPECT_EQ(vec.Size(), 0);
    EXPECT_EQ(vec.Capacity(), 0);
    EXPECT_TRUE(CmpVec(vec, {}));
}

TEST(TestConstructorsVector, WithParams) {
    MVector vec(10, 2);
    EXPECT_EQ(vec.Size(), 10);
    EXPECT_EQ(vec.Capacity(), 10);
    EXPECT_TRUE(CmpVec(vec, {2, 2, 2, 2, 2, 2, 2 , 2, 2, 2}));
}

TEST(TestConstructorsVector, InitialiserList) {
    MVector vec({2, 2, 2, 2, 1, 111});
    EXPECT_EQ(vec.Size(), 6);
    EXPECT_EQ(vec.Capacity(), 6);
    EXPECT_TRUE(CmpVec(vec, {2, 2, 2, 2, 1, 111}));
}

TEST(TestConstructorsVector, Copy) {
    MVector vec({2, 2, 112, 1, 111});
    MVector vec2(vec);
    EXPECT_EQ(vec2.Size(), 5);
    EXPECT_EQ(vec2.Capacity(), 5);
    EXPECT_TRUE(CmpVec(vec2, {2, 2, 112, 1, 111}));
}

TEST(TestConstructorsVector, CopyAssigment) {
    MVector vec({2, 112, 1, 111});
    MVector vec2 = vec;
    EXPECT_EQ(vec2.Size(), 4);
    EXPECT_EQ(vec2.Capacity(), 4);
    EXPECT_TRUE(CmpVec(vec2, {2, 112, 1, 111}));

}
TEST(TestFuncVector, PushBack) {
    MVector vec({2, 112});
    vec.PushBack(111);
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec.Capacity(), 4);
    EXPECT_TRUE(CmpVec(vec, {2, 112, 111}));
    vec.PushBack(222);
    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec.Capacity(), 4);
    EXPECT_TRUE(CmpVec(vec, {2, 112, 111, 222}));
    vec.PushBack(333);
    EXPECT_EQ(vec.Size(), 5);
    EXPECT_EQ(vec.Capacity(), 8);
    EXPECT_TRUE(CmpVec(vec, {2, 112, 111, 222, 333}));
}

TEST(TestFuncVector, PopBack) {
    MVector vec({2, 3, 4, 5, 6});
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 4);
    EXPECT_EQ(vec.Capacity(), 5);
    EXPECT_TRUE(CmpVec(vec, {2, 3, 4, 5}));
    vec.PopBack();
    EXPECT_EQ(vec.Size(), 3);
    EXPECT_EQ(vec.Capacity(), 5);
    EXPECT_TRUE(CmpVec(vec, {2, 3, 4}));
}

TEST(TestFuncVector, Front) {
    MVector vec({2, 3, 4, 5, 6});
    EXPECT_EQ(vec.Front(), 2);
}

TEST(TestFuncVector, Back) {
    MVector vec({2, 3, 4, 5, 6});
    EXPECT_EQ(vec.Back(), 6);
}


TEST(TestOperatorsVector, AccessInIndex)
{
    MVector vec{1, 2, 4, 5, 7, 8};
    EXPECT_EQ(vec[0], 1);
    vec[0] = 100;
    EXPECT_EQ(vec[0], 100);

    EXPECT_EQ(vec[3], 5);
    vec[3] = 200;
    EXPECT_EQ(vec[3], 200);

    EXPECT_THROW(vec[6], std::runtime_error);
    EXPECT_THROW(vec[7] = 0, std::runtime_error);
    EXPECT_THROW(vec[-2], std::runtime_error);
}

TEST(TestOperatorsVector, WithVectors) {
    MVector vec1{1, 2, 3, 4, 5};
    MVector vec2{11, 12, 13, 14, 15};
    MVector vec3{111, 112, 113, 114, 115, 116};
    MVector res1 = vec1 + vec2;

    EXPECT_TRUE(CmpVec(res1, {12, 14, 16, 18, 20}));
    EXPECT_EQ(res1.Size(), vec1.Size());
    EXPECT_THROW(vec1 + vec3, std::runtime_error);

    MVector res2 = vec2 - vec1;
    EXPECT_TRUE(CmpVec(res2, {10, 10, 10, 10, 10}));
    EXPECT_EQ(res2.Size(), vec1.Size());
    EXPECT_THROW(vec1 - vec3, std::runtime_error);

    MVector res3 = vec2 * vec1;
    EXPECT_TRUE(CmpVec(res3, {11, 24, 39, 56, 75}));
    EXPECT_EQ(res3.Size(), vec1.Size());
    EXPECT_THROW(vec1 - vec3, std::runtime_error);

    MVector res4(vec1.Size(), 0);
    res4 += vec1;
    EXPECT_TRUE(CmpVec(res4, {1, 2, 3, 4, 5}));

    MVector res5(vec1.Size(), 20);
    res5 -= vec1;
    EXPECT_TRUE(CmpVec(res5, {19, 18, 17, 16, 15}));

    MVector res6(vec1.Size(), 2);
    res6 *= vec1;
    EXPECT_TRUE(CmpVec(res6, {2, 4, 6, 8, 10}));
}

TEST(TestOperatorsVector, WithMatrixes) {
    MVector vec({1, 2, 3});
    MMatrix mat({{1, 2}, {3, 4}, {5, 6}});
    vec *= mat;
    EXPECT_TRUE(CmpVec(vec, {22, 28}));
//    MVector &operator*=(MVector &left, MMatrix &right);
}
TEST(TestOperatorsVector, WithValues) {
    MVector vec2{5, 6, 7, 8, 9, 10};
    MVector res1 = vec2 * 3;
    EXPECT_TRUE(CmpVec(res1, {15, 18, 21, 24, 27, 30}));

    MVector vec3{1, 2, 3};
    vec3*=2;
    EXPECT_TRUE(CmpVec(vec3, {2, 4, 6}));

    MVector res2 = vec2 + 2;
    EXPECT_TRUE(CmpVec(res2, {7, 8, 9, 10, 11, 12}));

    MVector vec4{1, 2, 3, 4, 5};
    vec4+=3;
    EXPECT_TRUE(CmpVec(vec4, {4, 5, 6, 7, 8}));

    vec4-=3;
    EXPECT_TRUE(CmpVec(vec4, {1, 2, 3, 4, 5}));
}

TEST(TestFuncVector, AddSub) {
    MVector vec{1, 2, 3, 4, 5, 6, 7};
    vec.AddValue(4);
    EXPECT_TRUE(CmpVec(vec, {5, 6, 7, 8, 9, 10, 11}));
    vec.SubValue(4);
    EXPECT_TRUE(CmpVec(vec, {1, 2, 3, 4, 5, 6, 7}));
}

TEST(TestFuncVector, Slices) {
    MVector vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MVector res = vec(1, 5);
    EXPECT_TRUE(CmpVec(res, {2, 3, 4, 5}));
    MVector res2 = vec(0, 8, 3);
    EXPECT_TRUE(CmpVec(res2, {1, 4, 7}));
}
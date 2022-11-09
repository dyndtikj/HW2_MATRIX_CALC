#include <gtest/gtest.h>
#include <math.h>

#include "m_matrix.h"

TEST(TestConstructorsMatrix, Default) {
    MMatrix mat;
    EXPECT_EQ(mat.Rows(), 0);
    EXPECT_EQ(mat.Cols(), 0);
    EXPECT_EQ(mat.Capacity(), 0);
}

TEST(TestConstructorsMatrix, WithParams) {
    MMatrix mat(3, 4, 12);
    EXPECT_EQ(mat.Rows(), 3);
    EXPECT_EQ(mat.Cols(), 4);
    EXPECT_EQ(mat.Capacity(), 3);
    EXPECT_TRUE(
        CmpMat(mat, {{12, 12, 12, 12}, {12, 12, 12, 12}, {12, 12, 12, 12}}));
    MMatrix mat2(3, 4, 12);
    EXPECT_TRUE(mat == mat2);
}
TEST(TestConstructorsMatrix, FromVectorsPointer) {
    MVector* vecs =
        new MVector[3]{MVector{12, 2}, MVector{2, 2}, MVector{2, 3}};
    MMatrix mat(vecs, 3);
    EXPECT_EQ(mat.Rows(), 3);
    EXPECT_EQ(mat.Cols(), 2);
    EXPECT_EQ(mat.Capacity(), 3);
    EXPECT_TRUE(CmpMat(mat, {{12, 2}, {2, 2}, {2, 3}}));
}

// vector - row by default
TEST(TestConstructorsMatrix, FromVectorRow) {
    MVector vec({1, 2, 3, 4});
    MMatrix mat(vec, Orientation::Row);
    EXPECT_EQ(mat.Rows(), 1);
    EXPECT_EQ(mat.Cols(), 4);
    EXPECT_EQ(mat.Capacity(), 1);
    EXPECT_TRUE(CmpMat(mat, {{1, 2, 3, 4}}));
}

TEST(TestConstructorsMatrix, FromVectorCol) {
    MVector vec({1, 2, 3, 4});
    MMatrix mat(vec, Orientation::Col);
    EXPECT_EQ(mat.Rows(), 4);
    EXPECT_EQ(mat.Cols(), 1);
    EXPECT_EQ(mat.Capacity(), 4);
    EXPECT_TRUE(CmpMat(mat, {{1}, {2}, {3}, {4}}));
}

TEST(TestConstructorsMatrix, CopyOther) {
    MMatrix mat1({{1, 2, 3}, {4, 5, 6}});
    MMatrix mat2(mat1);
    EXPECT_EQ(mat2.Rows(), 2);
    EXPECT_EQ(mat2.Cols(), 3);
    EXPECT_EQ(mat2.Capacity(), 2);
    EXPECT_TRUE(CmpMat(mat2, {{1, 2, 3}, {4, 5, 6}}));
    EXPECT_TRUE(CmpMat(mat1, {{1, 2, 3}, {4, 5, 6}}));
}

TEST(TestConstructorsMatrix, AssignCopyOther) {
    MMatrix mat1({{1, 2, 3}, {4, 5, 6}});
    MMatrix mat2 = mat1;
    EXPECT_EQ(mat2.Rows(), 2);
    EXPECT_EQ(mat2.Cols(), 3);
    EXPECT_EQ(mat2.Capacity(), 2);
    EXPECT_TRUE(CmpMat(mat1, {{1, 2, 3}, {4, 5, 6}}));
}
TEST(TestConstructorsMatrix, InitialiserList) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    EXPECT_EQ(mat.Rows(), 2);
    EXPECT_EQ(mat.Cols(), 3);
    EXPECT_EQ(mat.Capacity(), 2);
    EXPECT_TRUE(CmpMat(mat, {{1, 2, 3}, {4, 5, 6}}));
}

TEST(TestFuncMatrix, PushBackRaw) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat.PushBackR({7, 8, 9});
    EXPECT_EQ(mat.Rows(), 3);
    EXPECT_EQ(mat.Cols(), 3);
    EXPECT_EQ(mat.Capacity(), 4);
    EXPECT_TRUE(CmpMat(mat, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
}

TEST(TestFuncMatrix, PushBackColumn) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat.PushBackC({40, 41});
    EXPECT_EQ(mat.Rows(), 2);
    EXPECT_EQ(mat.Cols(), 4);
    EXPECT_EQ(mat.Capacity(), 2);
    EXPECT_TRUE(CmpMat(mat, {{1, 2, 3, 40}, {4, 5, 6, 41}}));
}

TEST(TestGetFuncMatrix, GetOnIndex) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][2], 6);
    EXPECT_THROW(mat[2][0], std::runtime_error);
}

TEST(TestGetFuncMatrix, GetOnIndexConst) {
    const MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][2], 6);
    EXPECT_THROW(mat[2][0], std::runtime_error);
}

TEST(TestGetFuncMatrix, GetRow) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    EXPECT_TRUE(CmpVec(mat.GetRow(0), {1, 2, 3}));
    EXPECT_THROW(mat.GetRow(2), std::runtime_error);
}

TEST(TestGetFuncMatrix, GetCol) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    EXPECT_TRUE(CmpVec(mat.GetCol(2), {3, 6}));
    EXPECT_THROW(mat.GetCol(3), std::runtime_error);
}

TEST(TestGetFuncMatrix, GetDiag) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    EXPECT_TRUE(CmpVec(mat.GetDiag(), {1, 5, 9}));
}

TEST(TestOperatorsMatrixMatrix, OpPlus) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    MMatrix mat3 = mat1 + mat2;
    EXPECT_TRUE(CmpMat(mat3, {{12, 14}, {16, 18}}));
}

TEST(TestOperatorsMatrixMatrix, OpMinus) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    MMatrix mat3 = mat2 - mat1;
    EXPECT_TRUE(CmpMat(mat3, {{10, 10}, {10, 10}}));
}
TEST(TestOperatorsMatrixMatrix, OpMul) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    MMatrix mat3 = mat2 * mat1;
    EXPECT_TRUE(CmpMat(mat3, {{11, 24}, {39, 56}}));
}
TEST(TestOperatorsMatrixMatrix, OpPlusAssign) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    mat1 += mat2;
    EXPECT_TRUE(CmpMat(mat1, {{12, 14}, {16, 18}}));
}

TEST(TestOperatorsMatrixMatrix, OpMinusAssign) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    mat2 -= mat1;
    EXPECT_TRUE(CmpMat(mat2, {{10, 10}, {10, 10}}));
}
TEST(TestOperatorsMatrixMatrix, OpMulAssign) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2({{11, 12}, {13, 14}});
    mat1 *= mat2;
    EXPECT_TRUE(CmpMat(mat1, {{11, 24}, {39, 56}}));
}
TEST(TestOperatorsMatrixNum, OpMulValMatrix) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MMatrix mat2 = 2 * mat1;
    EXPECT_TRUE(CmpMat(mat2, {{2, 4}, {6, 8}}));
}

TEST(TestOperatorsMatrixVec, OpMulMatrixVec) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MVector vec({10, 20});
    MVector res = mat1 * vec;
    EXPECT_TRUE(CmpVec(res, {50, 110}));
}

TEST(TestOperatorsMatrixVec, OpMulVecMatrix) {
    MMatrix mat1({{1, 2}, {3, 4}});
    MVector vec({10, 20});
    MVector res = vec * mat1;
    EXPECT_TRUE(CmpVec(res, {70, 100}));
}
TEST(TestFuncMatrix, MatMul) {
    MMatrix mat1({{1, 2, 3}, {4, 5, 6}});
    MMatrix mat2({{1, 2}, {3, 4}, {5, 6}});
    auto mul = MatMul(mat1, mat2);
    EXPECT_TRUE(CmpMat(mul, {{22, 28}, {49, 64}}));
}
TEST(TestOperatorsMatrixNum, OpPlusMatVal) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    auto res = mat + 10;
    EXPECT_TRUE(CmpMat(res, {{11, 12, 13}, {14, 15, 16}}));
}
TEST(TestOperatorsMatrixNum, OpMinusMatVal) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    auto res = mat - 1;
    EXPECT_TRUE(CmpMat(res, {{0, 1, 2}, {3, 4, 5}}));
}
TEST(TestOperatorsMatrixNum, OpPlusAssignMatVal) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat += 10;
    EXPECT_TRUE(CmpMat(mat, {{11, 12, 13}, {14, 15, 16}}));
}
TEST(TestOperatorsMatrixNum, OpMinusAssignMatVal) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat -= 1;
    EXPECT_TRUE(CmpMat(mat, {{0, 1, 2}, {3, 4, 5}}));
}

TEST(TestFuncMatrix, AddValue) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat.AddValue(10);
    EXPECT_TRUE(CmpMat(mat, {{11, 12, 13}, {14, 15, 16}}));
}
TEST(TestFuncMatrix, SubValue) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat.SubValue(1);
    EXPECT_TRUE(CmpMat(mat, {{0, 1, 2}, {3, 4, 5}}));
}
TEST(TestFuncMatrix, MulValue) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}});
    mat.MulValue(2);
    EXPECT_TRUE(CmpMat(mat, {{2, 4, 6}, {8, 10, 12}}));
}

// With choose opportunity rows/cols;
TEST(TestFuncMatrix, AdMVector) {

    MMatrix mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    MVector vec({1, 2, 3});
    mat.AddVector(vec, 0);
    // ROW
    EXPECT_TRUE(CmpMat(mat, {{2, 4, 6}, {4, 5, 6}, {7, 8, 9}}));
    MMatrix mat1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    MVector vec1({1, 2, 3});
    mat1.AddVector(vec, 0, Orientation::Col);
    EXPECT_TRUE(CmpMat(mat1, {{2, 2, 3}, {6, 5, 6}, {10, 8, 9}}));
}
TEST(TestFuncMatrix, SubVector) {
    MMatrix mat({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    MVector vec({1, 2, 3});
    mat.SubVector(vec, 0);
    // ROW
    EXPECT_TRUE(CmpMat(mat, {{0, 0, 0}, {4, 5, 6}, {7, 8, 9}}));
    MMatrix mat1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    MVector vec1({1, 2, 3});
    mat1.SubVector(vec, 0, Orientation::Col);
    EXPECT_TRUE(CmpMat(mat1, {{0, 2, 3}, {2, 5, 6}, {4, 8, 9}}));
}
TEST(TestGetFuncMatrix, GetTransposed) {
    MMatrix mat({{1, 2}, {3, 4}});
    EXPECT_TRUE(CmpMat(mat.GetTransponsed(), {{1, 3}, {2, 4}}));
}
TEST(TestGetFuncMatrix, GetInverted) {
    MMatrix mat({{1, 6, 1}, {1, 2, 5}, {1, 3, 5}});

    MMatrix mat2 = mat.GetIverted();
    EXPECT_TRUE(
        CmpMat(mat2, {{1.25, 6.75, -7}, {0, -1, 1}, {-0.25, -0.75, 1}}));
}
TEST(TestGetFuncMatrix, GetAdded) {
    MMatrix mat({{1, 6, 1}, {1, 2, 5}, {1, 3, 5}});

    auto mat2 = mat.GetAdded();
    EXPECT_TRUE(CmpMat(mat2, {{-5, 0, 1}, {-27, 4, 3}, {28, -4, -4}}));
}
TEST(TestGetFuncMatrix, GetMinor) {
    MMatrix mat({{1, 6, 1}, {1, 2, 5}, {1, 3, 5}});
    EXPECT_EQ(-5, mat.GetMinor(0, 0));
}
TEST(TestFuncMatrix, DelRowCol) {
    MMatrix mat({{1, 6, 1}, {1, 2, 5}, {1, 3, 5}});
    mat = mat.DelRowCol(1, 1);
    EXPECT_TRUE(CmpMat(mat, {{1, 1}, {1, 5}}));
}

TEST(TestGetFuncMatrix, GetDet) {
    MMatrix mat({{1, 6, 1}, {1, 2, 5}, {1, 3, 5}});
    EXPECT_EQ(-4, mat.GetDet());
}

// extra (1)
// BES = begin end step
TEST(TestFuncMatrix, SliceBES) {
    MMatrix mat(10, 2, 2);
    auto res = mat(0, 10, 4);
    EXPECT_TRUE(CmpMat(res, {{2, 2}, {2, 2}, {2, 2}}));
}

TEST(TestFuncMatrix, SliceRowCol) {
    MMatrix mat({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    });
    auto res = mat({1, 3}, {1, 4, 2});
    EXPECT_TRUE(CmpMat(res, {{6, 8}, {10, 12}}));
}

TEST(TestFuncMatrix, SliceRow) {
    MMatrix mat({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    });
    auto res = mat.SliceR(0, 3, 2);
    EXPECT_TRUE(CmpMat(res, {{1, 2, 3, 4}, {9, 10, 11, 12}}));
}

TEST(TestFuncMatrix, SliceCol) {
    MMatrix mat({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    });
    auto res = mat.SliceC(0, 2, 1);
    EXPECT_TRUE(CmpMat(res, {{1, 2}, {5, 6}, {9, 10}}));
}


#include <gtest/gtest.h>
#include <math.h>
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

bool CmpMatrix(const MMatrix& mat, std::initializer_list<std::initializer_list<double>> & il){
    if (mat.Rows() != il.size()) {
        return false;
    }
    for (size_t i = 0; i < mat.Rows(); i++) {
        for (size_t j = 0; j < mat.Cols(); j++) {
            // double numbers compare ...
            if (std::abs(mat[i][j]- *((il.begin() + i)->begin() +j)) > 0.00000001) {
                return false;
            }
        }
    }
    return true;
}
TEST(TestConstructorsMatrix, Default) {
//    MMatrix();
}
// 2
TEST(TestConstructorsMatrix, WithParams) {
    //MMatrix(const size_t &rows, const size_t &cols, const int &val = 0);
}
TEST(TestConstructorsMatrix, FromVectorsPointer) {
//MMatrix(MVector *vectors, const size_t &rows);
}
// vector - row by default
TEST(TestConstructorsMatrix, FromVectorRow){
    //MMatrix(const MVector &vec, Orientation orient = Orientation::Row);
}

TEST(TestConstructorsMatrix, FromVectorCol){

}
TEST(TestConstructorsMatrix, CopyOther){
//    MMatrix(MMatrix &other);
}
TEST(TestConstructorsMatrix, AssignCopyOther) {
//MMatrix &operator=(const MMatrix &other);
}
TEST(TestConstructorsMatrix, InitialiserList) {
//MMatrix(const std::initializer_list<std::initializer_list<double>> &list);
}

TEST(TestFuncMatrix, PushBackRaw){
//    void PushBackR(const MVector &row);
}
TEST(TestFuncMatrix, PushBackColumn){
//    void PushBackC(const MVector &col);
}

TEST(TestGetFuncMatrix, GetOnIndex){

//    MVector &operator[](const size_t &idx);
}
TEST(TestGetFuncMatrix, GetOnIndexConst) {
//    MVector &operator[](const size_t &idx) const;
}

TEST(TestGetFuncMatrix, GetRow){
//    MVector GetRow(const size_t &idx) const;
}


TEST(TestGetFuncMatrix, GetCol){

}

TEST(TestGetFuncMatrix, GetDiag){

}

TEST(TestOperatorsMatrixMatrix, OpPlus){

}

TEST(TestOperatorsMatrixMatrix, OpMinus){

}
TEST(TestOperatorsMatrixMatrix, OpMul){

}
TEST(TestOperatorsMatrixMatrix, OpPlusAssign){

}

TEST(TestOperatorsMatrixMatrix, OpMinusAssign){

}
TEST(TestOperatorsMatrixMatrix, OpMulAssign){

}
TEST(TestOperatorsMatrixNum, OpMulValMatrix){
//    MMatrix operator*(const double &left, const MMatrix &right);
}

TEST(TestOperatorsMatrixVec, OpMulMatrixVec) {
//    MVector operator*(const MMatrix &left, const MVector &right);
}
TEST(TestOperatorsMatrixVec, OpMulVecMatrix) {
    //   MVector operator*(const MVector &left, const  &right);
}
TEST(TestFuncMatrix, MatMul){
//    MMatrix MatMul(const MMatrix &left, const MMatrix &right);
}
TEST(TestOperatorsMatrixNum, OpPlusMatVal) {
//MMatrix operator+(const MMatrix &left, const double &right);
}
TEST(TestOperatorsMatrixNum, OpMinusMatVal) {
//    MMatrix operator-(const MMatrix &left, const double &right);
}
TEST(TestOperatorsMatrixNum, OpPlusAssignMatVal) {
//    MMatrix &operator+=(MMatrix &left, const double &right);
}
TEST(TestOperatorsMatrixNum, OpMinusAssignMatVal) {
//MMatrix &operator-=(MMatrix &left, const double &right);
}

TEST(TestGetFuncMatrix, AddValue){

//    void AddValue(const double &val);
}
TEST(TestGetFuncMatrix, SubValue) {
//void SubValue(const double &val);
}
TEST(TestGetFuncMatrix, MulValue) {
//    void MulValue(const double &val);
}
// With choose opportunity rows/cols;
TEST(TestGetFuncMatrix, AddVector){
//void AddVector(const MVector &v, size_t idx,
//               Orientation orient = Orientation::Row);
}
TEST(TestGetFuncMatrix, SubVector) {
//void SubVector(const MVector &v, size_t idx,
//               Orientation orient = Orientation::Row);
}
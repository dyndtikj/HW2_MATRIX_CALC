#include <gtest/gtest.h>

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

bool CmpMatrix(const MMatrix& mat, const std::initializer_list<double>& il){
    if (mat.Rows() != il.size()) {
        return false;
    }
    for (size_t i = 0; i < mat.Rows(); i++) {
        for (size_t j = 0; j < mat.Cols(); j++) {
        // double numbers compare ...
        if (std::abs(vec[i] - *(il.begin() + i)) > 0.00000001) {
            return false;
        }
    }
    return true;
}
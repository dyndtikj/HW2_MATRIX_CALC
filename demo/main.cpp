#include <iostream>
#include "m_vector.h"
#include "m_matrix.h"

int main(){
//
//    MVector test;
//    test.PushBack(1);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//    test.PushBack(2);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//    test.PushBack(3);
//    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
//    MVector test2({1, 2, 3, 4});
//    for (int i = 0; i < test2.Size(); i++){
//        std::cout << test2[i] << " ";
//    }
//    std::cout << std::endl;
//
//    //std::cout << test3.Size() << test3.Capacity()  << "wefwrf";
//    MMatrix test_matrix({{1, 2},{3, 4}, {5, 6}});
//
//
//    std::cout << test_matrix.Rows() << " : " << test_matrix.Cols() << std::endl;
//    for (size_t i = 0; i < test_matrix.Rows(); i++) {
//        for (size_t j = 0; j < test_matrix.Cols(); j++){
//            std::cout << test_matrix[i][j] << "__";
//        }
//        std::cout << std::endl;
//    }
//
//    MMatrix test5({{1, 2}, {3, 4}});
//    test5.Print();
//
//    MMatrix test6(test5);
//    test6.Print();
//    test6[1][1] = 100;
//    test6.Print();
//    test5.Print();
//    MVector test7({1,4, 6, 7});
//
//    MMatrix test8(test7, Orientation::Col);
//    test7[0] = 1101101;
//    test8.Print();
//    MMatrix test_methods({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
//    test_methods.Print();
//    test_methods.GetDiag().Print();
//    test_methods.GetCol(1).Print();
//    test_methods.GetRow(2).Print();
//    MVector test9({100, 200, 300});
//    test_methods.AddVector(test9, 1);
//    test_methods.Print();
//    test_methods.AddVector(test9, 2, Orientation::Col);
//    test_methods.Print();
//    MMatrix mat1({{1, 2, 3}, {4, 5, 6}});
//    MMatrix mat2({{1, 2}, {3,4}, {5, 6}});
//    auto mul = MatMul(mat1, mat2);;
//    mul.Print();
//
//    MMatrix test123{{1, 5, 2}, {7, 6, 8}, {12, 9, 10}};
//    test123.Print();
//
//    std::cout << "Det = " << test123.GetDet() << std::endl;
//    MMatrix test123_I = test123.GetIverted();
//    test123_I.Print();
//    MMatrix test123_T = test123.GetTransponsed();
//    test123_T.Print();
    MMatrix test121;
    test121.PushBackC({1,2 ,3});
    test121.Print();
    test121.PushBackC({11,21 ,13});
    test121.Print();
    test121.PushBackC({111,211 ,131});
    test121.Print();
//    MMatrix col = test121.GetCol(1);
//    col.Print();
    MMatrix slice = test121({0, 2 }, {0, 3, 2});
    slice.Print();
//    // Must fail
    // test121.PushBackR({1, 4,2 ,3});

    MVector vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MVector res2 = vec(0, 8, 3);
    res2.Print();
    return 0;
}
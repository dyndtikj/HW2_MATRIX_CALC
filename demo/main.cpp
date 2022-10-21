#include <iostream>
#include "m_vector.h"
#include "m_matrix.h"

int main(){

    MVector test;
    test.PushBack(1);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(2);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(3);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    MVector test2({1, 2, 3, 4});
    for (int i = 0; i < test2.Size(); i++){
        std::cout << test2[i] << " ";
    }
    std::cout << std::endl;

    //std::cout << test3.Size() << test3.Capacity()  << "wefwrf";
    MMatrix test_matrix({{1, 2},{3, 4}, {5, 6}});


    std::cout << test_matrix.Rows() << " : " << test_matrix.Cols() << std::endl;
    for (size_t i = 0; i < test_matrix.Rows(); i++) {
        for (size_t j = 0; j < test_matrix.Cols(); j++){
            std::cout << test_matrix[i][j] << "__";
        }
        std::cout << std::endl;
    }

    MMatrix test5({{1, 2}, {3, 4}});
    test5.Print();

    MMatrix test6(test5);
    test6.Print();
    test6[1][1] = 100;
    test6.Print();
    test5.Print();
    MVector test7({1,4, 6, 7});

    MMatrix test8(test7, Orientation::Col);
    test7[0] = 1101101;
    test8.Print();
    MMatrix test_methods({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    test_methods.Print();
    test_methods.GetDiag().Print();
    test_methods.GetCol(1).Print();
    test_methods.GetRow(2).Print();
    return 0;
}
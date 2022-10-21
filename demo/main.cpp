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
    MMatrix test4(test2, Orientation::Row);
    std::cout << test4.Rows() << "x" << test4.Cols() << std::endl;
    for (size_t i = 0; i < test4.Rows(); i++) {
        for (size_t j = 0; j < test4.Cols(); j++){
            std::cout << test_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
//    MMatrix test5(test2, Orientation::Col);
//    std::cout << test5.Rows() << "x" << test5.Cols() << std::endl;
//    for (size_t i = 0; i < test5.Rows(); i++) {
//        for (size_t j = 0; j < test5.Cols(); j++){
//            std::cout << test_matrix[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
    return 0;
}
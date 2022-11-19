#include <iostream>
#include "m_vector.h"
#include "m_matrix.h"

int main(){
    // some usage of written classes

    MVector test;
    test.PushBack(1);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(2);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(3);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;

    MMatrix mat2({
                        {1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                });
    auto res = mat2.SliceC(0, 2, 1);
    res.Print();
}
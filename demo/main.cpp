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


    MMatrix test121;
    test121.PushBackC({1,2 ,3});
    test121.Print();
    test121.PushBackC({11,21 ,13});
    test121.Print();
    test121.PushBackC({111,211 ,131});
    test121.Print();

    MMatrix mat({
                        {1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                });
    auto res = mat.SliceC(0, 2, 1);
    res.Print();
}
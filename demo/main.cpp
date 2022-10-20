#include <iostream>
#include "m_vector.h"

int main(){
    MVector test;
    test.PushBack(1);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(2);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    test.PushBack(3);
    std::cout << test.Size() << " : " << test.Capacity() << std::endl;
    return 0;
}
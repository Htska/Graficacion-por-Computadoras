#include <iostream>
#include "Vector3.h"

int main()
{
    Vector3 a{1.f,1.f,1.f};
    Vector3 b{2.f,2.f,2.f};
    Vector3 c = a+b;
    std::cout<<c<<std::endl;
    return 0;
}
#include <iostream>
#include "Vector2.h"

int main()
{
    Vector2 v1{1,1};
    Vector2 v2{2,2};
    Vector2 v3 = v1+v2;
    std::cout << v3 <<std::endl;
    return 0;
}
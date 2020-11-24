#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

int main(int argc, char **argv)
{
    Array<int, 3, 1> a;
    Array<int, 3, 1> b;

    a << 1, 2, 3;
    b << 1, 2, 3;
    

    std::cout << a + b << std::endl;
    
    return 0;
}
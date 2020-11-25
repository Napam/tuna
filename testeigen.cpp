#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

int main(int argc, char **argv)
{
    Array<int, 3, 1> a;
    Array<int, 3, 1> b;

    a << -4, 1, 4;
    b << 1, 2, 3;
    

    std::cout << a.min(3) << std::endl;
    
    return 0;
}
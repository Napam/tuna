#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Boi
{
public:
    int x;
};

class Girl
{
public: 
    Boi &boi;
    Girl(Boi &boi_)
        : boi(boi_)
    {
    }

    void getBoi()
    {
        std::cout << boi.x << std::endl;
    }
};


void test()
{
    Boi *boi = new Boi;
    boi->x = 10;

    Girl girl(*boi);
    girl.getBoi();

    std::cout << boi << std::endl;
    std::cout << &girl.boi << std::endl;
}


int main(int argc, char **argv)
{
    Array<int, 3, 1> a;
    Array<float, 3, 1> b;

    a << -4, 1, 4;
    b << 1.5, 2.2, 3.3;
    
    std::cout << b.cast<int>() << std::endl;

    // test();   
    return 0;
}
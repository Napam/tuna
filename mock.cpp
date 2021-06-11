#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef struct test {
    int x, y;
} WOA;

void printTest(WOA *a)
{
    std::cout << (*a).x << " " << (*a).y << "\n"; 
}

int main(int argc, char **argv)
{
    auto hehe = WOA({1,2});
    printTest(&WOA({1,2}));
    return 0;
}
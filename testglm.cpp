#include "include/tunapch.h"

int main(int argc, char **argv)
{
    glm::ivec3 vec(1,2,3);
    vec = vec + vec;
    vec = vec * 4 + vec;
    std::cout << vec << "\n";
    return 0;
} 
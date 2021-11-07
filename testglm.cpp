#include "include/tunapch.hpp"

int main(int argc, char **argv)
{
    glm::vec3 vec(1,1,1);
    std::cout << glm::length(vec) << "\n";
    vec = vec + vec;
    vec = vec * 4.0f + vec;
    std::cout << vec << "\n";
    return 0;
} 
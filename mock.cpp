#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    std::ifstream stream("config.json");
    json j3 = json::parse(stream);
    std::cout << j3["pi"].get<float>() << "\n";
    std::cout << j3["window"]["width"].get<float>() << "\n";
    return 0;
}
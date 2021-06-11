#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    std::ifstream stream("config.json");
    json j3 = json::parse(stream);
    std::cout << j3["boids"]["fpsMonitor"]["fontFile"] << "\n";
    std::cout << j3["boids"]["fpsMonitor"]["color"][0].get<int>() << "\n";
    return 0;
}
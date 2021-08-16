#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char **argv)
{
    std::ifstream stream("config.json");
    json j3 = json::parse(stream);
    std::cout << j3["boids"]["fpsMonitor"]["fontFile"].dump() << "\n";
    std::cout << static_cast<int>(j3["boids"]["fpsMonitor"]["color"][0].get<unsigned char>()) << "\n";
    std::cout << static_cast<int>(j3["boids"]["fpsMonitor"]["color"][1].get<unsigned char>()) << "\n";
    std::cout << static_cast<int>(j3["boids"]["fpsMonitor"]["color"][2].get<unsigned char>()) << "\n";
    std::cout << static_cast<int>(j3["boids"]["fpsMonitor"]["color"][3].get<unsigned char>()) << "\n";
    std::cout << j3["boids"]["misc"] << "\n";
    return 0;
}
#include "Random.hpp"

#include <random>

namespace Random
{

std::string getRandomElement(const std::vector<std::string>& vec)
{
    if (vec.empty())
        throw std::runtime_error("Vector is empty");

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(0, vec.size() - 1);

    return vec[dist(gen)];
}

}  // namespace Random

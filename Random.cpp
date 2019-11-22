#include "Random.hpp"

int Random::operator ()(int min, int max)
{
  return std::uniform_int_distribution<int>{min, max}(engine);
}

bool Random::operator ()(double p)
{
  return std::bernoulli_distribution{p}(engine);
}

#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>

using namespace std;

using Population = deque<uint64_t>;

void init_population(Population & pop, const vector<uint64_t> & initialPopulation)
{
  pop.resize(9);
  fill(pop.begin(), pop.end(), 0);

  for (auto fish : initialPopulation)
  {
    pop[fish]++;
  }
}

uint64_t total_pop_count(Population & population)
{
  return accumulate(population.begin(), population.end(), UINT64_C(0), plus<uint64_t>());
}

void simulate_day(Population & population)
{
  uint64_t reproducing = population.front();
  population.pop_front();
  population.push_back(0);
  population[6] += reproducing;
  population[8] = reproducing;
}

int main()
{
  ifstream         input("input.txt");
  vector<uint64_t> initialPopulation;

  int n = 0;
  while (input >> n)
  {
    initialPopulation.push_back(n);
    input.ignore();
  }

  constexpr const uint32_t daysPart1 = 80;
  {
    Population pop;
    init_population(pop, initialPopulation);

    for (uint32_t i = 0; i < daysPart1; i++)
      simulate_day(pop);
    cout << "Simulated population size of lanternfish after " << daysPart1 << " is "
         << total_pop_count(pop) << "\n";
  }

  constexpr const uint32_t daysPart2 = 256;
  {
    Population pop;
    init_population(pop, initialPopulation);
    for (uint32_t i = 0; i < daysPart2; i++)
      simulate_day(pop);
    cout << "Simulated population size of lanternfish after " << daysPart2 << " is "
         << total_pop_count(pop) << "\n";
  }
}

#include <benchmark/benchmark.h>
#include <random>


static void randomInit(benchmark::State& state) {
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);
  for (auto _ : state)
  {
    auto a = distrib(gen);
  }
}
BENCHMARK(randomInit);



// Register the function as a
// Register the function as a benchmark
BENCHMARK_MAIN();

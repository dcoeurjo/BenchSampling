#include <benchmark/benchmark.h>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

void SomeFunction()
{
  std::string init;
  benchmark::DoNotOptimize(init);
}

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    SomeFunction();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);



template <class T>
static void BM_ContainerDefaultConstructor(benchmark::State& state)
{
  for (auto _ : state) {
    T toto;
    benchmark::DoNotOptimize(toto);
  }
}
BENCHMARK(BM_ContainerDefaultConstructor<int>);
BENCHMARK(BM_ContainerDefaultConstructor<std::vector<int>>);
BENCHMARK(BM_ContainerDefaultConstructor<std::vector<std::string>>);


template <class T>
static void BM_insert_find(benchmark::State& state)
{
  //preparing the data
  T q;
  typename T::value_type v;
  std::vector<size_t> data(state.range(0));
  for (int i = 0 ; i < state.range(0); ++i)
    data[i] = std::rand();
  
  for (auto _ : state) {
    for (int i = 0 ; i < state.range(0); ++i)
      q.insert(data[i]);
    
    for (int i = state.range(0); i>0; --i)
    {
      auto res = q.find(data[i]);
      benchmark::DoNotOptimize(res);
    }
    
    benchmark::DoNotOptimize(q);
  }
}

BENCHMARK(BM_insert_find<std::set<int>>)->Range(2<<10,2<<12);
BENCHMARK(BM_insert_find<std::unordered_set<int>>)->Range(2<<10,2<<12);


// Run the benchmark
BENCHMARK_MAIN();

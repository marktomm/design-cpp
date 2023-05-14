#include "lib.h"
#include <benchmark/benchmark.h>

using namespace strategy;
using namespace std;

struct SomeType {};

// GEN_PROTO_BEGIN
static void BM_00_Strategy_Operation(benchmark::State& state);
static void BM_01_TC_Operation(benchmark::State& state);
// GEN_PROTO_END

static void BM_01_TC_Operation(benchmark::State& state) {
    std::vector<int> data{5, 2, 8, 1, 9, 3};
    TightlyCoupledContext context(SortingAlgorithm::BubbleSort);
    for (auto _ : state) {
        context.SortData(data);
    }
    benchmark::DoNotOptimize(context);
}

// Benchmark function for Context
static void BM_00_Strategy_Operation(benchmark::State& state) {
    vector<int> data{5, 2, 8, 1, 9, 3};
    Context context(make_unique<BubbleSortStrategy>());
    for (auto _ : state) {
        context.SortData(data);
    }
    benchmark::DoNotOptimize(context);
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Strategy_Operation);
BENCHMARK(BM_01_TC_Operation);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

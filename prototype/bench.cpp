#include "lib.h"
#include <benchmark/benchmark.h>

#include <chrono>

#include <memory>

using namespace prototype;

// GEN_PROTO_BEGIN
static void BM_0001_ManualBatch(benchmark::State& state);
static void BM_0001_Manual(benchmark::State& state);
static void BM_00_Noop(benchmark::State& state);
static void BM_00_X1(benchmark::State& state);
static void BM_01_PauseResume(benchmark::State& state);
static void BM_A1_CopyConstructor(benchmark::State& state);
static void BM_A1_NoopA1(benchmark::State& state);
static void BM_A1_NoopB1(benchmark::State& state);
static void BM_B1_PrototypePattern(benchmark::State& state);
// GEN_PROTO_END

static void BM_00_Noop(benchmark::State& state) {
    for (auto _ : state) {
    }
}

static void BM_00_X1(benchmark::State& state) {
    for (auto _ : state) {
        int x = 1;
        benchmark::DoNotOptimize(x);
    }
}

static void BM_01_PauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        state.ResumeTiming();
    }
}

static void BM_0001_Manual(benchmark::State& state) {
    for (auto _ : state) {

        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_0001_ManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_A1_NoopA1(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(concreteA);
}

static void BM_A1_CopyConstructor(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    for (auto _ : state) {
        ConcretePrototypeA concreteAB = concreteA;
        benchmark::DoNotOptimize(concreteAB);
    }
}

static void BM_A1_NoopB1(benchmark::State& state) {
    std::unique_ptr<Prototype> prototypeA =
        std::make_unique<ConcretePrototypeA>();
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(prototypeA);
}

static void BM_B1_PrototypePattern(benchmark::State& state) {
    std::unique_ptr<Prototype> prototypeA =
        std::make_unique<ConcretePrototypeA>();
    for (auto _ : state) {
        std::unique_ptr<Prototype> prototypeB = prototypeA->clone();
        benchmark::DoNotOptimize(prototypeB);
    }
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_0001_Manual)->UseManualTime();
BENCHMARK(BM_0001_ManualBatch)->UseManualTime();
BENCHMARK(BM_00_Noop);
BENCHMARK(BM_00_X1);
BENCHMARK(BM_01_PauseResume);
BENCHMARK(BM_A1_CopyConstructor);
BENCHMARK(BM_A1_NoopA1);
BENCHMARK(BM_A1_NoopB1);
BENCHMARK(BM_B1_PrototypePattern);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

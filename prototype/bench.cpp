#include "lib.h"
#include <benchmark/benchmark.h>

#include <chrono>

#include <memory>

using namespace prototype;

// GEN_PROTO_BEGIN
static void BM_00_Proto_Cr_Dr(benchmark::State& state);
static void BM_01_Proto_Clone(benchmark::State& state);
static void BM_A0_TC_Cr_Dr(benchmark::State& state);
static void BM_A1_TC_Clone(benchmark::State& state);
static void BM_D2_Proto_Operation(benchmark::State& state);
static void BM_D2_TC_Operation(benchmark::State& state);
static void BM_M0_Manual(benchmark::State& state);
static void BM_N0_ManualBatch(benchmark::State& state);
static void BM_Q1_Proto_Up_Operation(benchmark::State& state);
static void BM_X0_Noop(benchmark::State& state);
static void BM_X0_X1(benchmark::State& state);
static void BM_X1_NoopA1(benchmark::State& state);
static void BM_X1_NoopB1(benchmark::State& state);
static void BM_YY_Proto_Bp_Clone(benchmark::State& state);
static void BM_Z1_PauseResume(benchmark::State& state);
// GEN_PROTO_END

static void BM_00_Proto_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        ConcretePrototypeA concreteA;
        benchmark::DoNotOptimize(concreteA);
    }
}

static void BM_01_Proto_Clone(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    for (auto _ : state) {
        auto x = concreteA.clone();
        benchmark::DoNotOptimize(concreteA);
        benchmark::DoNotOptimize(x);
    }
}

static void BM_YY_Proto_Bp_Clone(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    Prototype* ptr = &concreteA;
    for (auto _ : state) {
        auto x = ptr->clone();
        benchmark::DoNotOptimize(concreteA);
        benchmark::DoNotOptimize(x);
    }
}

static void BM_D2_Proto_Operation(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    for (auto _ : state) {
        auto x = concreteA.clone();
        benchmark::DoNotOptimize(concreteA);
        benchmark::DoNotOptimize(x);
    }
}

static void BM_A0_TC_Cr_Dr(benchmark::State& state) {
    for (auto _ : state) {
        TightlyCoupledType concreteA;
        benchmark::DoNotOptimize(concreteA);
    }
}

static void BM_A1_TC_Clone(benchmark::State& state) {
    TightlyCoupledType concreteA;
    for (auto _ : state) {
        TightlyCoupledType concreteAB = concreteA;
        benchmark::DoNotOptimize(concreteA);
        benchmark::DoNotOptimize(concreteAB);
    }
}

static void BM_D2_TC_Operation(benchmark::State& state) {
    TightlyCoupledType concreteA;
    for (auto _ : state) {
        auto x = concreteA;
        benchmark::DoNotOptimize(concreteA);
        benchmark::DoNotOptimize(x);
    }
}

static void BM_Q1_Proto_Up_Operation(benchmark::State& state) {
    std::unique_ptr<Prototype> prototypeA =
        std::make_unique<ConcretePrototypeA>();
    for (auto _ : state) {
        std::unique_ptr<Prototype> prototypeB = prototypeA->clone();
        benchmark::DoNotOptimize(prototypeB);
    }
}

static void BM_X0_Noop(benchmark::State& state) {
    for (auto _ : state) {
    }
}

static void BM_X0_X1(benchmark::State& state) {
    for (auto _ : state) {
        int x = 1;
        benchmark::DoNotOptimize(x);
    }
}

static void BM_Z1_PauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        state.ResumeTiming();
    }
}

static void BM_M0_Manual(benchmark::State& state) {
    for (auto _ : state) {

        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_N0_ManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_X1_NoopA1(benchmark::State& state) {
    ConcretePrototypeA concreteA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(concreteA);
}

static void BM_X1_NoopB1(benchmark::State& state) {
    std::unique_ptr<Prototype> prototypeA =
        std::make_unique<ConcretePrototypeA>();
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(prototypeA);
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_00_Proto_Cr_Dr);
BENCHMARK(BM_01_Proto_Clone);
BENCHMARK(BM_A0_TC_Cr_Dr);
BENCHMARK(BM_A1_TC_Clone);
BENCHMARK(BM_D2_Proto_Operation);
BENCHMARK(BM_D2_TC_Operation);
BENCHMARK(BM_M0_Manual)->UseManualTime();
BENCHMARK(BM_N0_ManualBatch)->UseManualTime();
BENCHMARK(BM_Q1_Proto_Up_Operation);
BENCHMARK(BM_X0_Noop);
BENCHMARK(BM_X0_X1);
BENCHMARK(BM_X1_NoopA1);
BENCHMARK(BM_X1_NoopB1);
BENCHMARK(BM_YY_Proto_Bp_Clone);
BENCHMARK(BM_Z1_PauseResume);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

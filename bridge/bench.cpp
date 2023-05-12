#include "lib.h"

#include <benchmark/benchmark.h>

#include <chrono>

using namespace bridge;

// GEN_PROTO_BEGIN
static void BM_0001_ManualBatch(benchmark::State& state);
static void BM_0001_Manual(benchmark::State& state);
static void BM_00_Noop(benchmark::State& state);
static void BM_00_X1(benchmark::State& state);
static void BM_A1_BridgeObjectStack(benchmark::State& state);
static void BM_A2_BridgeCtorHeapManualBatch(benchmark::State& state);
static void BM_A2_BridgeCtorHeapManual(benchmark::State& state);
static void BM_A2_BridgeObjectHeap(benchmark::State& state);
static void BM_A3_BridgeDtorHeapManualBatch(benchmark::State& state);
static void BM_A3_BridgeDtorHeapManual(benchmark::State& state);
static void BM_A4_BridgeCopy(benchmark::State& state);
static void BM_A5_BridgeOperation(benchmark::State& state);
static void BM_E1_TightlyCoupledObjectStack(benchmark::State& state);
static void BM_E2_TightlyCoupledCtorHeapManualBatch(benchmark::State& state);
static void BM_E2_TightlyCoupledCtorHeapManual(benchmark::State& state);
static void BM_E2_TightlyCoupledObjectHeap(benchmark::State& state);
static void BM_E3_TightlyCoupledDtorHeapManualBatch(benchmark::State& state);
static void BM_E3_TightlyCoupledDtorHeapManual(benchmark::State& state);
static void BM_E4_TightlyCoupledCopy(benchmark::State& state);
static void BM_E5_TightlyCoupledOperation(benchmark::State& state);
static void BM_X1_PauseResume(benchmark::State& state);
static void BM_X2_BridgeCtorHeapPauseResume(benchmark::State& state);
static void BM_X3_BridgeDtorHeapPauseResume(benchmark::State& state);
static void BM_X4_TightlyCoupledCtorHeapPauseResume(benchmark::State& state);
static void BM_X5_TightlyCoupledDtorHeapPauseResume(benchmark::State& state);
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

static void BM_X1_PauseResume(benchmark::State& state) {
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

// Benchmarks for the Bridge pattern
static void BM_A1_BridgeObjectStack(benchmark::State& state) {
    for (auto _ : state) {
        ConcreteImplementationA implA;
        RefinedAbstraction abstraction(&implA);
        benchmark::DoNotOptimize(abstraction);
    }
}

static void BM_A2_BridgeCtorHeapManual(benchmark::State& state) {
    for (auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        delete abstraction;
        delete implA;

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_A2_BridgeCtorHeapManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto start = std::chrono::high_resolution_clock::now();
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        delete abstraction;
        delete implA;

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_X2_BridgeCtorHeapPauseResume(benchmark::State& state) {

    for (auto _ : state) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);

        state.PauseTiming();
        delete abstraction;
        delete implA;
        state.ResumeTiming();
    }
}

static void BM_A2_BridgeObjectHeap(benchmark::State& state) {
    for (auto _ : state) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        delete abstraction;
        delete implA;
    }
}

static void BM_A3_BridgeDtorHeapManual(benchmark::State& state) {
    for (auto _ : state) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        auto start = std::chrono::high_resolution_clock::now();
        delete abstraction;
        delete implA;
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_A3_BridgeDtorHeapManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        auto start = std::chrono::high_resolution_clock::now();
        delete abstraction;
        delete implA;
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_X3_BridgeDtorHeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        state.ResumeTiming();

        delete abstraction;
        delete implA;
    }
}

static void BM_A4_BridgeCopy(benchmark::State& state) {
    ConcreteImplementationA implA;
    RefinedAbstraction abstraction(&implA);
    for (auto _ : state) {
        RefinedAbstraction copiedAbstraction = abstraction;
        benchmark::DoNotOptimize(copiedAbstraction);
    }
}

static void BM_A5_BridgeOperation(benchmark::State& state) {
    ConcreteImplementationA implA;
    RefinedAbstraction abstraction(&implA);
    for (auto _ : state) {
        abstraction.operation();
    }
    benchmark::DoNotOptimize(abstraction);
}

// Benchmarks for the Tightly Coupled type
static void BM_E1_TightlyCoupledObjectStack(benchmark::State& state) {
    for (auto _ : state) {
        TightlyCoupledType type(TightlyCoupledType::ImplementationType::TypeA);
        benchmark::DoNotOptimize(type);
    }
}

static void BM_E2_TightlyCoupledCtorHeapManual(benchmark::State& state) {
    for (auto _ : state) {
        auto start = std::chrono::high_resolution_clock::now();
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        delete type;
        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_E2_TightlyCoupledCtorHeapManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto start = std::chrono::high_resolution_clock::now();
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        delete type;

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_X4_TightlyCoupledCtorHeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);

        state.PauseTiming();
        delete type;
        state.ResumeTiming();
    }
}

static void BM_E2_TightlyCoupledObjectHeap(benchmark::State& state) {
    for (auto _ : state) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        benchmark::DoNotOptimize(type);
        delete type;
    }
}

static void BM_E3_TightlyCoupledDtorHeapManual(benchmark::State& state) {
    for (auto _ : state) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);

        auto start = std::chrono::high_resolution_clock::now();
        delete type;
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_E3_TightlyCoupledDtorHeapManualBatch(benchmark::State& state) {
    while (state.KeepRunningBatch(1)) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);

        auto start = std::chrono::high_resolution_clock::now();
        delete type;
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count();

        state.SetIterationTime(static_cast<double>(elapsed) / 1e9);
    }
}

static void BM_X5_TightlyCoupledDtorHeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        state.ResumeTiming();

        delete type;
    }
}

static void BM_E4_TightlyCoupledCopy(benchmark::State& state) {
    TightlyCoupledType type(TightlyCoupledType::ImplementationType::TypeA);
    for (auto _ : state) {
        TightlyCoupledType copiedType = type;
        benchmark::DoNotOptimize(copiedType);
    }
}

static void BM_E5_TightlyCoupledOperation(benchmark::State& state) {
    TightlyCoupledType type(TightlyCoupledType::ImplementationType::TypeA);
    for (auto _ : state) {
        type.operation();
    }
    benchmark::DoNotOptimize(type);
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_0001_Manual)->UseManualTime();
BENCHMARK(BM_0001_ManualBatch)->UseManualTime();
BENCHMARK(BM_00_Noop);
BENCHMARK(BM_00_X1);
BENCHMARK(BM_A1_BridgeObjectStack);
BENCHMARK(BM_A2_BridgeCtorHeapManual)->UseManualTime();
BENCHMARK(BM_A2_BridgeCtorHeapManualBatch)->UseManualTime();
BENCHMARK(BM_A2_BridgeObjectHeap);
BENCHMARK(BM_A3_BridgeDtorHeapManual)->UseManualTime();
BENCHMARK(BM_A3_BridgeDtorHeapManualBatch)->UseManualTime();
BENCHMARK(BM_A4_BridgeCopy);
BENCHMARK(BM_A5_BridgeOperation);
BENCHMARK(BM_E1_TightlyCoupledObjectStack);
BENCHMARK(BM_E2_TightlyCoupledCtorHeapManual)->UseManualTime();
BENCHMARK(BM_E2_TightlyCoupledCtorHeapManualBatch)->UseManualTime();
BENCHMARK(BM_E2_TightlyCoupledObjectHeap);
BENCHMARK(BM_E3_TightlyCoupledDtorHeapManual)->UseManualTime();
BENCHMARK(BM_E3_TightlyCoupledDtorHeapManualBatch)->UseManualTime();
BENCHMARK(BM_E4_TightlyCoupledCopy);
BENCHMARK(BM_E5_TightlyCoupledOperation);
BENCHMARK(BM_X1_PauseResume);
BENCHMARK(BM_X2_BridgeCtorHeapPauseResume);
BENCHMARK(BM_X3_BridgeDtorHeapPauseResume);
BENCHMARK(BM_X4_TightlyCoupledCtorHeapPauseResume);
BENCHMARK(BM_X5_TightlyCoupledDtorHeapPauseResume);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

#include "lib.h"

#include <benchmark/benchmark.h>

#include <chrono>

using namespace bridge;

// GEN_PROTO_BEGIN
static void BM_0001_ManualBatch(benchmark::State& state);
static void BM_0001_Manual(benchmark::State& state);
static void BM_00_Noop(benchmark::State& state);
static void BM_00_X1(benchmark::State& state);
static void BM_A1_Bridge_ObjectStack(benchmark::State& state);
static void BM_A4_Bridge_Copy(benchmark::State& state);
static void BM_A5_Bridge_Operation(benchmark::State& state);
static void BM_E1_TightlyCoupled_Object_Stack(benchmark::State& state);
static void BM_E4_TightlyCoupled_Copy(benchmark::State& state);
static void BM_E5_TightlyCoupled_Operation(benchmark::State& state);
static void BM_H2_Bridge_ObjectHeap(benchmark::State& state);
static void BM_H2_TightlyCoupled_Object_Heap(benchmark::State& state);
static void BM_M0_Bridge_Dr_HeapManual(benchmark::State& state);
static void BM_M2_Bridge_Cr_HeapManual(benchmark::State& state);
static void BM_M2_TightlyCoupled_Cr_HeapManual(benchmark::State& state);
static void BM_M3_TightlyCoupled_Dr_HeapManual(benchmark::State& state);
static void BM_N0_Bridge_Dr_HeapManualBatch(benchmark::State& state);
static void BM_N2_Bridge_Cr_HeapManualBatch(benchmark::State& state);
static void BM_N2_TightlyCoupled_Cr_HeapManualBatch(benchmark::State& state);
static void BM_N3_TightlyCoupled_Dr_HeapManualBatch(benchmark::State& state);
static void BM_X1_PauseResume(benchmark::State& state);
static void BM_X2_Bridge_Cr_HeapPauseResume(benchmark::State& state);
static void BM_X3_Bridge_Dr_HeapPauseResume(benchmark::State& state);
static void BM_X4_TightlyCoupled_Cr_HeapPauseResume(benchmark::State& state);
static void BM_X5_TightlyCoupled_Dr_HeapPauseResume(benchmark::State& state);
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
static void BM_A1_Bridge_ObjectStack(benchmark::State& state) {
    for (auto _ : state) {
        ConcreteImplementationA implA;
        RefinedAbstraction abstraction(&implA);
        benchmark::DoNotOptimize(abstraction);
    }
}

static void BM_M2_Bridge_Cr_HeapManual(benchmark::State& state) {
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

static void BM_N2_Bridge_Cr_HeapManualBatch(benchmark::State& state) {
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

static void BM_X2_Bridge_Cr_HeapPauseResume(benchmark::State& state) {

    for (auto _ : state) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);

        state.PauseTiming();
        delete abstraction;
        delete implA;
        state.ResumeTiming();
    }
}

static void BM_H2_Bridge_ObjectHeap(benchmark::State& state) {
    for (auto _ : state) {
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        delete abstraction;
        delete implA;
    }
}

static void BM_M0_Bridge_Dr_HeapManual(benchmark::State& state) {
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

static void BM_N0_Bridge_Dr_HeapManualBatch(benchmark::State& state) {
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

static void BM_X3_Bridge_Dr_HeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto* implA = new ConcreteImplementationA();
        auto* abstraction = new RefinedAbstraction(implA);
        state.ResumeTiming();

        delete abstraction;
        delete implA;
    }
}

static void BM_A4_Bridge_Copy(benchmark::State& state) {
    ConcreteImplementationA implA;
    RefinedAbstraction abstraction(&implA);
    for (auto _ : state) {
        RefinedAbstraction copiedAbstraction = abstraction;
        benchmark::DoNotOptimize(copiedAbstraction);
    }
}

static void BM_A5_Bridge_Operation(benchmark::State& state) {
    ConcreteImplementationA implA;
    RefinedAbstraction abstraction(&implA);
    for (auto _ : state) {
        abstraction.operation();
    }
    benchmark::DoNotOptimize(abstraction);
}

// Benchmarks for the Tightly Coupled type
static void BM_E1_TightlyCoupled_Object_Stack(benchmark::State& state) {
    for (auto _ : state) {
        TightlyCoupledType type(TightlyCoupledType::ImplementationType::TypeA);
        benchmark::DoNotOptimize(type);
    }
}

static void BM_M2_TightlyCoupled_Cr_HeapManual(benchmark::State& state) {
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

static void BM_N2_TightlyCoupled_Cr_HeapManualBatch(benchmark::State& state) {
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

static void BM_X4_TightlyCoupled_Cr_HeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);

        state.PauseTiming();
        delete type;
        state.ResumeTiming();
    }
}

static void BM_H2_TightlyCoupled_Object_Heap(benchmark::State& state) {
    for (auto _ : state) {
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        benchmark::DoNotOptimize(type);
        delete type;
    }
}

static void BM_M3_TightlyCoupled_Dr_HeapManual(benchmark::State& state) {
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

static void BM_N3_TightlyCoupled_Dr_HeapManualBatch(benchmark::State& state) {
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

static void BM_X5_TightlyCoupled_Dr_HeapPauseResume(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto* type = new TightlyCoupledType(
            TightlyCoupledType::ImplementationType::TypeA);
        state.ResumeTiming();

        delete type;
    }
}

static void BM_E4_TightlyCoupled_Copy(benchmark::State& state) {
    TightlyCoupledType type(TightlyCoupledType::ImplementationType::TypeA);
    for (auto _ : state) {
        TightlyCoupledType copiedType = type;
        benchmark::DoNotOptimize(copiedType);
    }
}

static void BM_E5_TightlyCoupled_Operation(benchmark::State& state) {
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
BENCHMARK(BM_A1_Bridge_ObjectStack);
BENCHMARK(BM_A4_Bridge_Copy);
BENCHMARK(BM_A5_Bridge_Operation);
BENCHMARK(BM_E1_TightlyCoupled_Object_Stack);
BENCHMARK(BM_E4_TightlyCoupled_Copy);
BENCHMARK(BM_E5_TightlyCoupled_Operation);
BENCHMARK(BM_H2_Bridge_ObjectHeap);
BENCHMARK(BM_H2_TightlyCoupled_Object_Heap);
BENCHMARK(BM_M0_Bridge_Dr_HeapManual)->UseManualTime();
BENCHMARK(BM_M2_Bridge_Cr_HeapManual)->UseManualTime();
BENCHMARK(BM_M2_TightlyCoupled_Cr_HeapManual)->UseManualTime();
BENCHMARK(BM_M3_TightlyCoupled_Dr_HeapManual)->UseManualTime();
BENCHMARK(BM_N0_Bridge_Dr_HeapManualBatch)->UseManualTime();
BENCHMARK(BM_N2_Bridge_Cr_HeapManualBatch)->UseManualTime();
BENCHMARK(BM_N2_TightlyCoupled_Cr_HeapManualBatch)->UseManualTime();
BENCHMARK(BM_N3_TightlyCoupled_Dr_HeapManualBatch)->UseManualTime();
BENCHMARK(BM_X1_PauseResume);
BENCHMARK(BM_X2_Bridge_Cr_HeapPauseResume);
BENCHMARK(BM_X3_Bridge_Dr_HeapPauseResume);
BENCHMARK(BM_X4_TightlyCoupled_Cr_HeapPauseResume);
BENCHMARK(BM_X5_TightlyCoupled_Dr_HeapPauseResume);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

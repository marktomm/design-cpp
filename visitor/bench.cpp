#include "include/lib.h"
#include "lib.h"
#include <benchmark/benchmark.h>

using namespace visitor;

// GEN_PROTO_BEGIN
static void BM_01_TrivialStandardNoop(benchmark::State& state);
static void BM_01_TrivialStandardOperation(benchmark::State& state);
static void BM_A1_CoupledElementNoop(benchmark::State& state);
static void BM_A1_CoupledElementOperation(benchmark::State& state);
static void BM_B0_VisitorPatternNoop(benchmark::State& state);
static void BM_B1_VisitorPatternAccept(benchmark::State& state);
// GEN_PROTO_END

static void BM_01_TrivialStandardNoop(benchmark::State& state) {
    CoupledElementTrivialStandard coupledElementA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(coupledElementA);
}

static void BM_01_TrivialStandardOperation(benchmark::State& state) {
    CoupledElementTrivialStandard coupledElementA;
    for (auto _ : state) {
        coupledElementA.operation();
    }
    benchmark::DoNotOptimize(coupledElementA);
}

static void BM_A1_CoupledElementNoop(benchmark::State& state) {
    ConcreteCoupledElementA coupledElementA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(coupledElementA);
}

static void BM_A1_CoupledElementOperation(benchmark::State& state) {
    CoupledElement* coupledElementA = new ConcreteCoupledElementA;
    for (auto _ : state) {
        coupledElementA->operation();
    }
    benchmark::DoNotOptimize(coupledElementA);
    delete coupledElementA;
}

static void BM_B0_VisitorPatternNoop(benchmark::State& state) {
    ConcreteElementA elementA;
    ConcreteVisitor visitor;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(elementA);
}

static void BM_B1_VisitorPatternAccept(benchmark::State& state) {
    ConcreteElementA elementA;
    ConcreteVisitor visitor;
    for (auto _ : state) {
        elementA.accept(&visitor);
    }
    benchmark::DoNotOptimize(elementA);
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_01_TrivialStandardNoop);
BENCHMARK(BM_01_TrivialStandardOperation);
BENCHMARK(BM_A1_CoupledElementNoop);
BENCHMARK(BM_A1_CoupledElementOperation);
BENCHMARK(BM_B0_VisitorPatternNoop);
BENCHMARK(BM_B1_VisitorPatternAccept);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

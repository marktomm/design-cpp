#include "include/lib.h"
#include "lib.h"
#include <benchmark/benchmark.h>
#include <memory>

using namespace std;
using namespace visitor;

// GEN_PROTO_BEGIN
static void BM_01_Visit_Object_Stack(benchmark::State& state);
static void BM_05_Visit_Operation(benchmark::State& state);
static void BM_07_Visit_Operation_Up_Fn(benchmark::State& state);
static void BM_A0_TC_Object_Stack(benchmark::State& state);
static void BM_A2_TC_Operation(benchmark::State& state);
static void BM_A3_TC_Operation_Up(benchmark::State& state);
static void BM_F1_CoupledElementOperation(benchmark::State& state);
static void BM_G6_Visit_Operation_Up_Ctx_Known(benchmark::State& state);
static void BM_VV_TC_Copy(benchmark::State& state);
static void BM_VV_Visit_Copy(benchmark::State& state);
static void BM_VV_Visit_Copy_Up(benchmark::State& state);
static void BM_VV_Visit_Object_Up(benchmark::State& state);
static void BM_X0_VisitorPatternNoop(benchmark::State& state);
static void BM_X1_CoupledElementNoop(benchmark::State& state);
static void BM_X1_TrivialStandardNoop(benchmark::State& state);
// GEN_PROTO_END

static void BM_A0_TC_Object_Stack(benchmark::State& state) {
    for (auto _ : state) {
        CoupledElementTrivialStandard coupledElementA;
        benchmark::DoNotOptimize(coupledElementA);
    }
}

static void BM_VV_TC_Copy(benchmark::State& state) {
    CoupledElementTrivialStandard coupledElementA;
    for (auto _ : state) {
        CoupledElementTrivialStandard coupledElementB = coupledElementA;
        benchmark::DoNotOptimize(coupledElementB);
        benchmark::DoNotOptimize(coupledElementA);
    }
}

static void BM_A2_TC_Operation(benchmark::State& state) {
    CoupledElementTrivialStandard coupledElementA;
    for (auto _ : state) {
        coupledElementA.operation();
        benchmark::DoNotOptimize(coupledElementA);
    }
}

static void BM_A3_TC_Operation_Up(benchmark::State& state) {

    auto coupledElementA = make_unique<CoupledElementTrivialStandard>();
    for (auto _ : state) {
        coupledElementA->operation();
        benchmark::DoNotOptimize(coupledElementA);
    }
}

static void BM_01_Visit_Object_Stack(benchmark::State& state) {
    for (auto _ : state) {
        ConcreteElementA elementA;
        ConcreteVisitor visitor;
        benchmark::DoNotOptimize(elementA);
        benchmark::DoNotOptimize(visitor);
    }
}

static void BM_05_Visit_Operation(benchmark::State& state) {
    ConcreteElementA a;
    ConcreteVisitor v;
    fn1(state, &a, &v);
}

static void BM_G6_Visit_Operation_Up_Ctx_Known(benchmark::State& state) {
    auto elementA = make_unique<ConcreteElementA>();
    auto visitor = make_unique<ConcreteVisitor>();
    for (auto _ : state) {
        elementA->accept(visitor.get());
        benchmark::DoNotOptimize(elementA);
        benchmark::DoNotOptimize(visitor);
    }
}

static void BM_07_Visit_Operation_Up_Fn(benchmark::State& state) {
    unique_ptr<Element> a = make_unique<ConcreteElementA>();
    unique_ptr<Visitor> v = make_unique<ConcreteVisitor>();
    fn1up(state, a, v);
}

static void BM_F1_CoupledElementOperation(benchmark::State& state) {
    CoupledElement* coupledElementA = new ConcreteCoupledElementA;
    for (auto _ : state) {
        coupledElementA->operation();
    }
    benchmark::DoNotOptimize(coupledElementA);
    delete coupledElementA;
}

static void BM_VV_Visit_Copy(benchmark::State& state) {
    ConcreteElementA elementA;
    ConcreteVisitor visitor;
    for (auto _ : state) {
        ConcreteElementA elementB = elementA;
        benchmark::DoNotOptimize(elementA);
        benchmark::DoNotOptimize(elementB);
        benchmark::DoNotOptimize(visitor);
    }
}

static void BM_VV_Visit_Object_Up(benchmark::State& state) {
    for (auto _ : state) {
        auto elementA = make_unique<ConcreteElementA>();
        auto visitor = make_unique<ConcreteVisitor>();
        benchmark::DoNotOptimize(elementA);
        benchmark::DoNotOptimize(visitor);
    }
}

static void BM_VV_Visit_Copy_Up(benchmark::State& state) {
    auto elementA = make_unique<ConcreteElementA>();
    auto visitor = make_unique<ConcreteVisitor>();
    for (auto _ : state) {
        auto elementB = move(elementA);
        benchmark::DoNotOptimize(elementA);
        benchmark::DoNotOptimize(elementB);
        benchmark::DoNotOptimize(visitor);
    }
}

static void BM_X1_TrivialStandardNoop(benchmark::State& state) {
    CoupledElementTrivialStandard coupledElementA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(coupledElementA);
}

static void BM_X1_CoupledElementNoop(benchmark::State& state) {
    ConcreteCoupledElementA coupledElementA;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(coupledElementA);
}

static void BM_X0_VisitorPatternNoop(benchmark::State& state) {
    ConcreteElementA elementA;
    ConcreteVisitor visitor;
    for (auto _ : state) {
    }
    benchmark::DoNotOptimize(elementA);
}

// GEN_BENCHMARK_BEGIN
BENCHMARK(BM_01_Visit_Object_Stack);
BENCHMARK(BM_05_Visit_Operation);
BENCHMARK(BM_07_Visit_Operation_Up_Fn);
BENCHMARK(BM_A0_TC_Object_Stack);
BENCHMARK(BM_A2_TC_Operation);
BENCHMARK(BM_A3_TC_Operation_Up);
BENCHMARK(BM_F1_CoupledElementOperation);
BENCHMARK(BM_G6_Visit_Operation_Up_Ctx_Known);
BENCHMARK(BM_VV_TC_Copy);
BENCHMARK(BM_VV_Visit_Copy);
BENCHMARK(BM_VV_Visit_Copy_Up);
BENCHMARK(BM_VV_Visit_Object_Up);
BENCHMARK(BM_X0_VisitorPatternNoop);
BENCHMARK(BM_X1_CoupledElementNoop);
BENCHMARK(BM_X1_TrivialStandardNoop);
// GEN_BENCHMARK_END

// Run the benchmark
BENCHMARK_MAIN();

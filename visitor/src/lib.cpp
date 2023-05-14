#include "lib.h"

namespace visitor {

void fn1(benchmark::State& state, Element* eptr, Visitor* vptr) {
    for (auto _ : state) {
        eptr->accept(vptr);
        benchmark::DoNotOptimize(eptr);
        benchmark::DoNotOptimize(vptr);
    }
}

// clang-format off
void fn1up(benchmark::State& state, std::unique_ptr<Element>& eptr, std::unique_ptr<Visitor>& vptr) {
    // clang-format on
    for (auto _ : state) {
        eptr->accept(vptr.get());
        benchmark::DoNotOptimize(eptr);
        benchmark::DoNotOptimize(vptr);
    }
}

} // namespace visitor

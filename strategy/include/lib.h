#ifndef MACRO_strategy_LIB_H
#define MACRO_strategy_LIB_H

#include <memory>
#include <vector>

#include <cstdint>

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

namespace strategy {

// Strategy interface
class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void Sort(std::vector<int>& data) = 0;
};

// Concrete Strategy 1
class BubbleSortStrategy: public SortingStrategy {
public:
    void Sort([[maybe_unused]] std::vector<int>& data) override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

// Concrete Strategy 2
class QuickSortStrategy: public SortingStrategy {
public:
    void Sort([[maybe_unused]] std::vector<int>& data) override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

// Context
class Context {
    std::unique_ptr<SortingStrategy> strategy;

public:
    explicit Context(std::unique_ptr<SortingStrategy> initial_strategy)
        : strategy(std::move(initial_strategy)) {}

    void SetStrategy(std::unique_ptr<SortingStrategy> new_strategy) {
        strategy = std::move(new_strategy);
    }

    void SortData(std::vector<int>& data) { strategy->Sort(data); }
};

// Enum for coupled example
enum class SortingAlgorithm { BubbleSort, QuickSort };

class TightlyCoupledContext {
    SortingAlgorithm algorithm;

    void BubbleSort([[maybe_unused]] std::vector<int>& data) {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }

    void QuickSort([[maybe_unused]] std::vector<int>& data) {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }

public:
    explicit TightlyCoupledContext(SortingAlgorithm initial_algorithm)
        : algorithm(initial_algorithm) {}

    void SetAlgorithm(SortingAlgorithm new_algorithm) {
        algorithm = new_algorithm;
    }

    void SortData(std::vector<int>& data) {
        switch (algorithm) {
        case SortingAlgorithm::BubbleSort:
            BubbleSort(data);
            break;
        case SortingAlgorithm::QuickSort:
            QuickSort(data);
            break;
        default:
            break;
        }
    }
};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace strategy

#endif

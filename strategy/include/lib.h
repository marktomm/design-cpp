#ifndef MACRO_strategy_LIB_H
#define MACRO_strategy_LIB_H

#include <memory>
#include <vector>

#include <cstdint>
#include <iostream>

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

namespace strategy {

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual void Sort(std::vector<int>& data) = 0;
};

class BubbleSortStrategy: public SortingStrategy {
public:
    void Sort([[maybe_unused]] std::vector<int>& data) override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class QuickSortStrategy: public SortingStrategy {
public:
    void Sort([[maybe_unused]] std::vector<int>& data) override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class SortingStrategyCout: public SortingStrategy {
public:
    SortingStrategyCout() {
        std::cout << "SortingStrategyCout default constructor called.\n";
    }

    ~SortingStrategyCout() override {
        std::cout << "SortingStrategyCout destructor called.\n";
    }

    SortingStrategyCout(const SortingStrategyCout& other)
        : SortingStrategy(other) {
        std::cout << "SortingStrategyCout copy constructor called.\n";
    }

    SortingStrategyCout& operator=(const SortingStrategyCout& other) {
        std::cout << "SortingStrategyCout copy assignment operator called.\n";
        if (this != &other) {
            SortingStrategy::operator=(other);
        }
        return *this;
    }

    SortingStrategyCout(SortingStrategyCout&& other) noexcept
        : SortingStrategy(std::move(other)) {
        std::cout << "SortingStrategyCout move constructor called.\n";
    }

    SortingStrategyCout& operator=(SortingStrategyCout&& other) noexcept {
        std::cout << "SortingStrategyCout move assignment operator called.\n";
        if (this != &other) {
            SortingStrategy::operator=(std::move(other));
        }
        return *this;
    }

    void Sort([[maybe_unused]] std::vector<int>& data) override {
        std::cout << "SortingStrategyCout Sort called.\n";
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

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

class ContextCout {
    std::unique_ptr<SortingStrategy> strategy;

public:
    explicit ContextCout(std::unique_ptr<SortingStrategy> initial_strategy)
        : strategy(std::move(initial_strategy)) {
        std::cout << "ContextCout constructor called.\n";
    }

    ~ContextCout() { std::cout << "ContextCout destructor called.\n"; }

    void SetStrategy(std::unique_ptr<SortingStrategy> new_strategy) {
        std::cout << "ContextCout SetStrategy called.\n";
        strategy = std::move(new_strategy);
    }

    void SortData(std::vector<int>& data) {
        std::cout << "ContextCout SortData called.\n";
        strategy->Sort(data);
    }
};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace strategy

#endif

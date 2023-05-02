#include "lib.h"

using namespace strategy;
using namespace std;

int main() {
    vector<int> data{5, 2, 8, 1, 9, 3};

    Context context(std::make_unique<BubbleSortStrategy>());
    context.SortData(data);

    context.SetStrategy(std::make_unique<QuickSortStrategy>());
    context.SortData(data);

    TightlyCoupledContext context2(SortingAlgorithm::BubbleSort);
    context2.SortData(data);

    context2.SetAlgorithm(SortingAlgorithm::QuickSort);
    context2.SortData(data);

    return 0;
}

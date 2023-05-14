#include "lib.h"

using namespace strategy;
using namespace std;

int main() {
    vector<int> data{5, 2, 8, 1, 9, 3};

    ContextCout contextCout(std::make_unique<SortingStrategyCout>());
    contextCout.SortData(data);

    cout << "step 0 \n";

    Context context(make_unique<BubbleSortStrategy>());
    context.SetStrategy(make_unique<QuickSortStrategy>());
    context.SortData(data);

    cout << "step 1 \n";

    TightlyCoupledContext context2(SortingAlgorithm::BubbleSort);
    context2.SortData(data);

    context2.SetAlgorithm(SortingAlgorithm::QuickSort);
    context2.SortData(data);

    return 0;
}

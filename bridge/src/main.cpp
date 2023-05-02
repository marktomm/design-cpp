#include "lib.h"

#include <iostream>

using namespace bridge;
using namespace std;

int main() {
    Implementation* implA = new ConcreteImplementationA();
    Implementation* implB = new ConcreteImplementationB();

    Abstraction* abstraction1 = new RefinedAbstraction(implA);
    abstraction1->operation();

    Abstraction* abstraction2 = new RefinedAbstraction(implB);
    abstraction2->operation();

    delete implA;
    delete implB;
    delete abstraction1;
    delete abstraction2;

    TightlyCoupledType typeA(TightlyCoupledType::ImplementationType::TypeA);
    TightlyCoupledType typeB(TightlyCoupledType::ImplementationType::TypeB);

    typeA.operation();
    typeB.operation();

    return 0;
}
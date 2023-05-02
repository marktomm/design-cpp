// bridge, but Abstraction does not have a reference to Implementor iface
// Instead the third class that takes a set of base ptr to distinct type
// hierarchies and implements fns that provide required sequence of calls to the
// given ptrs

#include "lib.h"

#include <iostream>

using namespace alt_bridge;
using namespace std;

// Implementor A
class ImplementorA {
public:
    virtual ~ImplementorA() {}
    virtual void operationA() = 0;
};

class ConcreteImplementorA1: public ImplementorA {
public:
    void operationA() override {
        cout << "ConcreteImplementorA1 operation" << endl;
    }
};

// Implementor B
class ImplementorB {
public:
    virtual ~ImplementorB() {}
    virtual void operationB() = 0;
};

class ConcreteImplementorB1: public ImplementorB {
public:
    void operationB() override {
        cout << "ConcreteImplementorB1 operation" << endl;
    }
};

// Third type that interacts with both Implementor A and B
class ThirdType {
public:
    void createSequence(ImplementorA* implA, ImplementorB* implB) {
        implA->operationA();
        implB->operationB();
    }
};

int main() {
    ImplementorA* implA1 = new ConcreteImplementorA1();
    ImplementorB* implB1 = new ConcreteImplementorB1();

    ThirdType sequenceCreator;
    sequenceCreator.createSequence(implA1, implB1);

    delete implA1;
    delete implB1;

    return 0;
}
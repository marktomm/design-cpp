#include "lib.h"

using namespace visitor;
using namespace std;

int main() {
    ConcreteElementA elementA;
    ConcreteElementB elementB;

    ConcreteVisitor visitor;

    elementA.accept(&visitor); // Output: Operation A on ConcreteElementA
    elementB.accept(&visitor); // Output: Operation B on ConcreteElementB

    return 0;
}

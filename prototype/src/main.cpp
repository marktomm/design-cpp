#include "lib.h"
#include <memory>

using namespace prototype;
using namespace std;

int main() {

    ConcretePrototypeCout p;
    cout << "step1" << endl;
    std::unique_ptr<Prototype> x = p.clone();
    cout << "step2" << endl;
    return 0;
}

#ifndef MACRO_bridge_LIB_H
#define MACRO_bridge_LIB_H

#include <cstdint>

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

namespace bridge {

class Implementation {
public:
    virtual ~Implementation() = default;
    virtual void operationImpl() = 0;
};

class ConcreteImplementationA: public Implementation {
public:
    void operationImpl() override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class ConcreteImplementationB: public Implementation {
public:
    void operationImpl() override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class Abstraction {
protected:
    Implementation* implementor;

public:
    virtual ~Abstraction() = default;
    Abstraction(Implementation* impl) : implementor(impl) {}

    virtual void operation() { implementor->operationImpl(); }
};

class RefinedAbstraction: public Abstraction {
public:
    RefinedAbstraction(Implementation* impl) : Abstraction(impl) {}

    void operation() override { implementor->operationImpl(); }
};

// this is the code before refactoring
class TightlyCoupledType {
public:
    enum class ImplementationType { TypeA, TypeB };

private:
    ImplementationType implType;

public:
    TightlyCoupledType(ImplementationType type) : implType(type) {}

    void operation() {
        switch (implType) {
        case ImplementationType::TypeA:
            operationImplA();
            break;
        case ImplementationType::TypeB:
            operationImplB();
            break;
        }
    }

private:
    void operationImplA() {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }

    void operationImplB() {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};
// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace bridge

#endif

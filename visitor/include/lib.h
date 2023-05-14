#ifndef MACRO_visitor_LIB_H
#define MACRO_visitor_LIB_H

#include <benchmark/benchmark.h>
#include <cstdint>
#include <memory>

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

namespace visitor {

class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visitConcreteElementA(ConcreteElementA* element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB* element) = 0;
};

class Element {
public:
    virtual ~Element() = default;
    virtual void accept(Visitor* visitor) = 0;
};

class ConcreteElementA: public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementA(this);
    }

    void operationA() {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class ConcreteElementB: public Element {
public:
    void accept(Visitor* visitor) override {
        visitor->visitConcreteElementB(this);
    }

    void operationB() {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class ConcreteVisitor: public Visitor {
public:
    void visitConcreteElementA(ConcreteElementA* element) override {
        element->operationA();
    }

    void visitConcreteElementB(ConcreteElementB* element) override {
        element->operationB();
    }
};

class CoupledElement {
public:
    virtual ~CoupledElement() = default;
    virtual void operation() = 0;
};

class ConcreteCoupledElementA: public CoupledElement {
public:
    void operation() override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class ConcreteCoupledElementB: public CoupledElement {
public:
    void operation() override {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

class CoupledElementTrivialStandard {
public:
    std::uintptr_t a{};
    void operation() {
        [[maybe_unused]] int x = 1;
        escape(&x);
    }
};

// GEN_PROTO_BEGIN
void fn1(benchmark::State& state, Element* eptr, Visitor* vptr);
void fn1up(benchmark::State& state, std::unique_ptr<Element>& eptr, std::unique_ptr<Visitor>& vptr);
// GEN_PROTO_END

}; // namespace visitor

#endif

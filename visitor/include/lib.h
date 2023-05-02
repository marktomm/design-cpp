#ifndef MACRO_visitor_LIB_H
#define MACRO_visitor_LIB_H

#include <cstdint>

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

namespace visitor {

class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual void visitConcreteElementA(ConcreteElementA* element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB* element) = 0;
};

class Element {
public:
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

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace visitor

#endif

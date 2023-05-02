#ifndef MACRO_prototype_LIB_H
#define MACRO_prototype_LIB_H

#include <memory>

#include <cstdint>

namespace prototype {

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
};

class ConcretePrototypeA: public Prototype {
public:
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeA>(*this);
    }
};

class ConcretePrototypeB: public Prototype {
public:
    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototypeB>(*this);
    }
};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace prototype

#endif

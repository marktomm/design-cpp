#ifndef MACRO_prototype_LIB_H
#define MACRO_prototype_LIB_H

#include <memory>

#include <cstdint>

#include <iostream>

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

class ConcretePrototypeCout: public Prototype {
public:
    ConcretePrototypeCout() {
        std::cout << "ConcretePrototypeCout default constructor called.\n";
    }

    ~ConcretePrototypeCout() {
        std::cout << "ConcretePrototypeCout destructor called.\n";
    }

    ConcretePrototypeCout(const ConcretePrototypeCout& other)
        : Prototype(other) {
        std::cout << "ConcretePrototypeCout copy constructor called.\n";
    }

    ConcretePrototypeCout& operator=(const ConcretePrototypeCout& other) {
        std::cout << "ConcretePrototypeCout copy assignment operator called.\n";
        if (this != &other) {
            Prototype::operator=(other);
        }
        return *this;
    }

    ConcretePrototypeCout(ConcretePrototypeCout&& other) noexcept
        : Prototype(std::move(other)) {
        std::cout << "ConcretePrototypeCout move constructor called.\n";
    }

    ConcretePrototypeCout& operator=(ConcretePrototypeCout&& other) noexcept {
        std::cout << "ConcretePrototypeCout move assignment operator called.\n";
        if (this != &other) {
            Prototype::operator=(std::move(other));
        }
        return *this;
    }

    std::unique_ptr<Prototype> clone() const override {
        std::cout << "ConcretePrototypeCout clone called.\n";
        return std::make_unique<ConcretePrototypeCout>(*this);
    }
};

class TightlyCoupledType {
public:
    std::uintptr_t a{};
};

// GEN_PROTO_BEGIN

// GEN_PROTO_END

}; // namespace prototype

#endif

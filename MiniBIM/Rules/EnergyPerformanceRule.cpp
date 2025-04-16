#ifndef ENERGYRULE_H
#define ENERGYRULE_H

#include "RuleDecorator.h"

class EnergyPerformanceRule : public RuleDecorator {
public:
EnergyPerformanceRule(IElement* element)
    : RuleDecorator(element, nullptr) { }
    virtual ~EnergyPerformanceRule() { }
    virtual std::string getName() const override { return "Simulation de performances energetique"; }
    virtual std::string getDescription() const override {
        return "Cout estimé : $$$";
    }
    virtual IElement* clone() const override {
        return new EnergyPerformanceRule(getBaseElement());
    }
    virtual IElement* decorate(IElement* element, std::shared_ptr<Rule> self) const override {
        return new EnergyPerformanceRule(element);
    }
};

#endif
#ifndef COSTRULE_H
#define COSTRULE_H

#include "RuleDecorator.h"

class CostEstimationRule : public RuleDecorator {
public:
    CostEstimationRule(IElement* element)
    : RuleDecorator(element, nullptr) { }
    virtual ~CostEstimationRule() { }
    virtual std::string getName() const override { return "Estimation des couts"; }
    virtual std::string getDescription() const override {
        return "Cout estimé : $$$";
    }
    virtual IElement* clone() const override {
        return new CostEstimationRule(getBaseElement());
    }
    virtual IElement* decorate(IElement* element, std::shared_ptr<Rule> self) const override {
        return new CostEstimationRule(element);
    }
};

#endif
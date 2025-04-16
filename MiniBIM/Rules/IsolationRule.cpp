#ifndef ISOLATIONRULE_H
#define ISOLATIONRULE_H

#include "RuleDecorator.h"

class IsolationRule : public RuleDecorator {
public:
    IsolationRule(IElement* element)
    : RuleDecorator(element, nullptr) { }
    virtual ~IsolationRule() { }
    virtual std::string getName() const override { return "Isolation"; }
    virtual std::string getDescription() const override {
        return "Ameliore les performances thermiques.";
    }
    virtual IElement* decorate(IElement* element, std::shared_ptr<Rule> self) const override{
        return new IsolationRule(element);
    }
    virtual IElement* clone() const override {
        return new IsolationRule(getBaseElement());
    }
};

#endif
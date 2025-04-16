#ifndef CHARGERULE_H
#define CHARGERULE_H

#include "RuleDecorator.h"

class ChargeRule : public RuleDecorator {
public:
    ChargeRule(IElement* element)
    : RuleDecorator(element, nullptr) { }
    virtual std ::string getName() const override { return "Contraintes de charge"; }
    virtual std::string getDescription() const override {
        return "Spécifie les contraintes de charge maximales.";
    }
    virtual IElement* clone() const override {
        return new ChargeRule(getBaseElement());
    }
    virtual IElement* decorate(IElement* element, std::shared_ptr<Rule> self) const override {
        return (new ChargeRule(element));
    }
};

#endif
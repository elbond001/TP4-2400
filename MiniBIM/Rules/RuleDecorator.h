#ifndef RULEDECORATOR_H
#define RULEDECORATOR_H

#include "../Element.h"
#include "Rule.h"

class RuleDecorator : public IElement, Rule {
private:
    IElement* baseElement;
    Rule* rule;
public:
    RuleDecorator(IElement* element, Rule* rule);
    ~RuleDecorator();

    std::string getName() const override;
    std::string getElementType() const override;
    std::string getDescription() const override;

    IElement* getBaseElement() const;

    Rule* getRule() const;
};

#endif
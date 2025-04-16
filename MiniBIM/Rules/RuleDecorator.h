#ifndef RULEDECORATOR_H
#define RULEDECORATOR_H

#include "../Element.h"
#include <memory>
#include "Rule.h"

class RuleDecorator : public IElement, public Rule {
    private:
        IElement* baseElement;
        std::shared_ptr<Rule> rule;
    public:
        RuleDecorator(IElement* element, std::shared_ptr<Rule> rule);
    ~RuleDecorator();

    std::string getName() const override;
    std::string getElementType() const override;
    std::string getDescription() const override;

    IElement* getBaseElement() const;

    std::shared_ptr<Rule> getRule() const;
};

#endif
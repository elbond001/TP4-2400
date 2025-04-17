#ifndef ISOLATIONRULE_H
#define ISOLATIONRULE_H

#include "Rule.h"

class IsolationRule : public Rule {
public:
    IsolationRule(std::shared_ptr<IElement> element)
    : Rule(element) { }
    virtual ~IsolationRule() { }
    virtual std::string getDescription() const override {
        return "Isolation";
    }
    
    virtual std::shared_ptr<IElement> clone() const override {
        return std::make_shared<IsolationRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate() const override{
        return std::make_shared<IsolationRule>(getBaseElement());
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
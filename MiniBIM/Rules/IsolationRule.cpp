#ifndef ISOLATIONRULE_H
#define ISOLATIONRULE_H

#include "ElementDecorator.h"

class IsolationRule : public ElementDecorator, public Rule {
public:
    IsolationRule(std::shared_ptr<IElement> element)
    : ElementDecorator(element) { }
    virtual ~IsolationRule() { }
    virtual std::string getDescription() const override {
        return "Isolation";
    }
    
    virtual std::shared_ptr<IElement> clone() const override {
        return std::make_shared<IsolationRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate(std::shared_ptr<IElement> element) const override{
        return std::make_shared<IsolationRule>(element);
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
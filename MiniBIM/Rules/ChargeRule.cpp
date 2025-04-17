#ifndef CHARGERULE_H
#define CHARGERULE_H

#include "ElementDecorator.h"

class ChargeRule : public ElementDecorator, public Rule {
public:
    ChargeRule(std::shared_ptr<IElement> element)
    : ElementDecorator(element) { }
    virtual~ChargeRule() {}
    virtual std::string getDescription() const override {
        return "Contrainte de charge";
    }
    virtual std::shared_ptr<IElement> clone() const override {
        std::cout << "[clone] Clonage de ChargeRule" << std::endl;
        return std::make_shared<ChargeRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate(std::shared_ptr<IElement> element) const override {
        return std::make_shared<ChargeRule>(element);
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
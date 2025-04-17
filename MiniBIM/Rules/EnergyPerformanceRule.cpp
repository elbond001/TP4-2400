#ifndef ENERGYRULE_H
#define ENERGYRULE_H

#include "Rule.h"

class EnergyPerformanceRule : public Rule {
public:
EnergyPerformanceRule(std::shared_ptr<IElement> element)
    : Rule(element) { }
    virtual ~EnergyPerformanceRule() { }
    virtual std::string getDescription() const override {
        return "Simulation de performance energetique";
    }
    virtual std::shared_ptr<IElement> clone() const override {
        std::cout << "[clone] Clonage de EnergyRule" << std::endl;
        return std::make_shared<EnergyPerformanceRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate() const override {
        std::cout << "Regle [" << getDescription() << "] est ajoute a l'element " << getBaseElement()->getElementType() << " (" << getBaseElement()->getName() << ")" << std::endl;
        return std::make_shared<EnergyPerformanceRule>(getBaseElement());
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
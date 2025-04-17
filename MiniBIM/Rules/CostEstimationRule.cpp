#ifndef COSTRULE_H
#define COSTRULE_H

#include "Rule.h"

class CostEstimationRule : public Rule {
public:
    CostEstimationRule(std::shared_ptr<IElement> element)
    : Rule(element) { }
    virtual ~CostEstimationRule() { }
    virtual std::string getDescription() const override {
        return "Estimation des couts";
    }
    virtual std::shared_ptr<IElement> clone() const override {
        std::cout << "[clone] Clonage de CostRule" << std::endl;
        return std::make_shared<CostEstimationRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate() const override{
        return std::make_shared<CostEstimationRule>(getBaseElement());
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
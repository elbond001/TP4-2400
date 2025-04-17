#ifndef COSTRULE_H
#define COSTRULE_H

#include "ElementDecorator.h"

class CostEstimationRule : public ElementDecorator, public Rule {
public:
    CostEstimationRule(std::shared_ptr<IElement> element)
    : ElementDecorator(element) { }
    virtual ~CostEstimationRule() { }
    virtual std::string getDescription() const override {
        return "Estimation des couts";
    }
    virtual std::shared_ptr<IElement> clone() const override {
        std::cout << "[clone] Clonage de CostRule" << std::endl;
        return std::make_shared<CostEstimationRule>(getBaseElement()->clone());
    }
    virtual std::shared_ptr<IElement> decorate(std::shared_ptr<IElement> element) const override {
        return std::make_shared<CostEstimationRule>(element);
    }
    virtual void showDescription(int niveau) const override {
        std::string decalages = "";

        for(int i = 0; i < niveau; i++)
            decalages += "  ";

        std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
    }
};

#endif
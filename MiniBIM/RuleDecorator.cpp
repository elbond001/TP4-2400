#include "RuleDecorator.h"

RuleDecorator::RuleDecorator(IElement* element, const std::string& rule)
    : baseElement(element), rule(rule)
{
    // On peut afficher un message de debug si souhaité, par exemple :
    // std::cout << "Element " << baseElement->getElementType() << " (" << baseElement->getName()
    //           << ") est enrobe de la regle [" << rule << "]." << std::endl;
}

RuleDecorator::~RuleDecorator() {
    // Attention : ne pas supprimer baseElement si elle n'est pas allouée dynamiquement
}

std::string RuleDecorator::getName() const {
    return baseElement->getName();
}

std::string RuleDecorator::getElementType() const {
    return baseElement->getElementType();
}

std::string RuleDecorator::getRule() const {
    return rule;
}

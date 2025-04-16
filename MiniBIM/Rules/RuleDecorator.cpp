#include "RuleDecorator.h"

RuleDecorator::RuleDecorator(IElement* element, Rule* rule)
    : baseElement(element), rule(rule) {}

RuleDecorator::~RuleDecorator() {}

std::string RuleDecorator::getName() const {
    return baseElement->getName();
}

std::string RuleDecorator::getElementType() const {
    return baseElement->getElementType();
}

Rule* RuleDecorator::getRule() const {
    return rule;
}

IElement* RuleDecorator::getBaseElement() const {
    return baseElement;
}

std::string RuleDecorator::getDescription() const {
    return rule->getDescription();
}
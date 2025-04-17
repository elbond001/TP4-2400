#include "ElementDecorator.h"
#include <iostream>

ElementDecorator::ElementDecorator(std::shared_ptr<IElement> element)
    : baseElement(std::move(element)) {}

ElementDecorator::~ElementDecorator() {}

std::string ElementDecorator::getName() const {
    return baseElement->getName();
}

std::string ElementDecorator::getElementType() const {
    return baseElement->getElementType();
}

std::shared_ptr<IElement> ElementDecorator::getBaseElement() const {
    return baseElement;
}

void ElementDecorator::showDescription(int niveau) const {
    baseElement->showDescription(niveau);
    std::string indent(niveau * 3, ' ');
    std::cout << indent << "avec [" << getElementType() << "]" << std::endl;
}

std::shared_ptr<IElement> ElementDecorator::clone() const {
    return std::make_shared<ElementDecorator>(baseElement->clone());
}

void ElementDecorator::setBaseElement(std::shared_ptr<IElement> newBase) {
    this->baseElement = newBase;
}
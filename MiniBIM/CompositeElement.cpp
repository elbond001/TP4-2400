#include "CompositeElement.h"
#include <sstream>
#include <algorithm>
#include <iostream>

CompositeElement::CompositeElement(const std::string& name)
    : name(name)
{}

CompositeElement::~CompositeElement()
{
    // Rien à supprimer manuellement grâce à shared_ptr
}

void CompositeElement::add(std::shared_ptr<IElement> element)
{
    components.push_back(element);
}

void CompositeElement::remove(std::shared_ptr<IElement> element)
{
    auto it = std::find(components.begin(), components.end(), element);
    if (it != components.end())
    {
        components.erase(it);
    }
}

std::string CompositeElement::getName() const
{
    return name;
}

std::string CompositeElement::getElementType() const
{
    return "Combinaison";
}

void CompositeElement::showDescription(int niveau) const 
{
    std::string decalages = "";

    for(int i = 0; i < niveau; i++)
        decalages += "  ";

    std::cout << decalages << "- " << getElementType() << " (" << name << ")" << std::endl;

    for(std::shared_ptr<IElement> e : components)
    {
        e->showDescription(niveau + 1);
    }
}

std::shared_ptr<IElement> CompositeElement::clone() const {
    auto copy = std::make_shared<CompositeElement>(name);

    for (const auto& component : components) {
        copy->add(std::shared_ptr<IElement>(component->clone()));
    }

    return copy;
}

std::vector<std::shared_ptr<IElement>> CompositeElement::getComponents()
{
    return components;
}
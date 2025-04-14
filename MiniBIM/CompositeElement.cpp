#include "CompositeElement.h"
#include <sstream>

CompositeElement::CompositeElement(const std::string &name)
    : name(name)
{
}

CompositeElement::~CompositeElement()
{
    // Ici, on ne supprime pas les composants si nous ne sommes pas propriétaires
}

void CompositeElement::add(IElement *element)
{
    components.push_back(element);
}

void CompositeElement::remove(IElement *element)
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        if (*it == element)
        {
            components.erase(it);
            break;
        }
    }
}

std::string CompositeElement::getName() const
{
    return name;
}

std::string CompositeElement::getElementType() const
{
    // On peut indiquer que cet élément est une combinaison
    return "Composite";
}

std::vector<IElement *> CompositeElement::getComponents()
{
    return components;
}

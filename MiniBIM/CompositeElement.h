#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include "Element.h"
#include <vector>
#include <string>

// Un élément composite qui peut contenir d'autres éléments (simples ou composites)
class CompositeElement : public IElement
{
private:
    std::string name;
    std::vector<IElement *> components;

public:
    CompositeElement(const std::string &name);
    virtual ~CompositeElement();

    // Ajoute ou retire un composant
    void add(IElement *element);
    void remove(IElement *element);

    // Pour l'affichage, on renvoie par exemple le nom du composite
    virtual std::string getName() const override;
    // On peut renvoyer "Composite" ou le type voulu
    virtual std::string getElementType() const override;

    std::vector<IElement*> getComponents();
};

#endif

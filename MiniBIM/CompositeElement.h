#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include "Element.h"
#include <vector>
#include <string>
#include <memory>

// Un élément composite qui peut contenir d'autres éléments (simples ou composites)
class CompositeElement : public IElement
{
private:
    std::string name;
    std::vector<std::shared_ptr<IElement>> components;

public:
    CompositeElement(const std::string& name);
    virtual ~CompositeElement();

    void add(std::shared_ptr<IElement> element);
    void remove(std::shared_ptr<IElement> element);

    virtual std::string getName() const override;
    virtual std::string getElementType() const override;
    virtual void showDescription(int niveau) const override;
    virtual std::shared_ptr<IElement> clone() const override;

    std::vector<std::shared_ptr<IElement>> getComponents();
};

#endif
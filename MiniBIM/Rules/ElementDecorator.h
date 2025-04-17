#ifndef RULEDECORATOR_H
#define RULEDECORATOR_H

#include "../Element.h"
#include <memory>
#include "Rule.h"

class ElementDecorator : public IElement {
    private:
        std::shared_ptr<IElement> baseElement;
    public:
        ElementDecorator(std::shared_ptr<IElement> element);
    ~ElementDecorator();

    std::string getName() const override;
    std::string getElementType() const override;
    //void showDescription(int niveau) {};
    std::shared_ptr<IElement> getBaseElement() const;
    virtual void showDescription(int niveau) const override;

    virtual std::shared_ptr<IElement> clone() const;

    void setBaseElement(std::shared_ptr<IElement> newBase);
    
};

#endif
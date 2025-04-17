#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <memory>

class IElement {
public:
    virtual ~IElement() {}
    virtual std::string getName() const = 0;
    virtual std::string getElementType() const = 0;
    virtual void showDescription(int niveau) const = 0;
    virtual std::shared_ptr<IElement> clone() const = 0;
};

#endif

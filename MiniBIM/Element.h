#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class IElement {
public:
    virtual ~IElement() {}
    virtual std::string getName() const = 0;
    virtual std::string getElementType() const = 0;
    virtual IElement* clone() const = 0;
};

#endif

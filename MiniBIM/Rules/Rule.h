#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <memory> 
#include "ElementDecorator.h" 

class Rule : public ElementDecorator {
public:
    Rule(std::shared_ptr<IElement> element) : ElementDecorator(element) {};
    virtual ~Rule() = default;
    virtual std::string getDescription() const = 0;
    virtual std::shared_ptr<IElement> decorate() const = 0;
};

#endif
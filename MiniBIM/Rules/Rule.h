#ifndef RULE_H
#define RULE_H

#include <string>
#include <iostream>
#include <memory>
#include "../Element.h" 

class Rule : public std::enable_shared_from_this<Rule> {
public:
    virtual ~Rule() = default;
    virtual std::string getDescription() const = 0;
    virtual std::shared_ptr<IElement> decorate(std::shared_ptr<IElement> element) const = 0;
};

#endif
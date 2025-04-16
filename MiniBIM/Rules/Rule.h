#ifndef RULE_H
#define RULE_H

#include <string>

class Rule {
public:
    virtual ~Rule() {}
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
};

#endif
#ifndef ISOLATIONRULE_H
#define ISOLATIONRULE_H

#include "RuleDecorator.h"

class IsolationRule : public RuleDecorator {
public:
    std::string getName() const override { return "Isolation"; }
    std::string getDescription() const override {
        return "Améliore les performances thermiques.";
    }
};

#endif
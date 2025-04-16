#ifndef COSTRULE_H
#define COSTRULE_H

#include "RuleDecorator.h"

class CostEstimationRule : public RuleDecorator {
public:
    std::string getName() const override { return "Estimation des couts"; }
    std::string getDescription() const override {
        return "Cout estimé : $$$";
    }
};

#endif
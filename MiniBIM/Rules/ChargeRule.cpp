#ifndef CHARGERULE_H
#define CHARGERULE_H

#include "Rule.h"

class ChargeRule : public Rule {
public:
    std::string getName() const override { return "Contraintes de charge"; }
    std::string getDescription() const override {
        return "Spécifie les contraintes de charge maximales.";
    }
};

#endif
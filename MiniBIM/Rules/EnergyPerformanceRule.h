#ifndef ENERGYRULE_H
#define ENERGYRULE_H

#include "Rule.h"

class EnergyPerformanceRule : public Rule {
public:
EnergyPerformanceRule(std::shared_ptr<IElement> element);
    virtual ~EnergyPerformanceRule() { }
    virtual std::string getDescription() const override;
    virtual std::shared_ptr<IElement> clone() const override;
    virtual std::shared_ptr<IElement> decorate() const override;
    virtual void showDescription(int niveau) const override;
};

#endif
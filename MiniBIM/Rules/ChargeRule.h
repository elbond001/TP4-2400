#ifndef CHARGERULE_H
#define CHARGERULE_H

#include "Rule.h"

class ChargeRule : public Rule {
public:
    ChargeRule(std::shared_ptr<IElement> element);
    virtual~ChargeRule() {}
    virtual std::string getDescription() const override;
    virtual std::shared_ptr<IElement> clone() const override;
    virtual std::shared_ptr<IElement> decorate() const override;
    virtual void showDescription(int niveau) const override;
};

#endif
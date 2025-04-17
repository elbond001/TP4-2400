#ifndef COSTRULE_H
#define COSTRULE_H

#include "Rule.h"

class CostEstimationRule : public Rule {
public:
    CostEstimationRule(std::shared_ptr<IElement> element);
    virtual ~CostEstimationRule() { }
    virtual std::string getDescription() const override;
    virtual std::shared_ptr<IElement> clone() const override;
    virtual std::shared_ptr<IElement> decorate() const override;
    virtual void showDescription(int niveau) const override;
};

#endif
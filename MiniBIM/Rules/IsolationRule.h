#ifndef ISOLATIONRULE_H
#define ISOLATIONRULE_H

#include "Rule.h"

class IsolationRule : public Rule {
public:
    IsolationRule(std::shared_ptr<IElement> element);
    virtual ~IsolationRule() { }
    virtual std::string getDescription() const override;
    
    virtual std::shared_ptr<IElement> clone() const override;
    virtual std::shared_ptr<IElement> decorate() const override;
    virtual void showDescription(int niveau) const override;
};

#endif
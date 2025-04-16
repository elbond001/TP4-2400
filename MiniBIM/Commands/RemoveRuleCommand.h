#pragma once
#include "Command.h"
#include "../Element.h"
#include "../Rules/Rule.h"

class RemoveRuleCommand : public Command {
private:
    Rule* rule;
    IElement* decoratedElement;
    IElement* restoredElement;  // pour undo

public:
    RemoveRuleCommand(Project* project, IElement* elementWithRule, Rule* rule);
    void execute() override;
    void undo() override;
};
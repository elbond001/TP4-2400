#pragma once
#include "Command.h"
#include "../Element.h"
#include "../Rules/Rule.h"

class RemoveRuleCommand : public Command {
private:
    std::shared_ptr<Rule> rule;
    std::shared_ptr<IElement> decoratedElement;
    std::shared_ptr<IElement> restoredElement;

public:
    RemoveRuleCommand(Project* project, std::shared_ptr<IElement> elementWithRule, std::shared_ptr<Rule> rule);
    void execute() override;
    void undo() override;
    std::string getDescription() override;
};
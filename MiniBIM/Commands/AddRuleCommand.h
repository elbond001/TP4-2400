#pragma once
#include "Command.h"
#include "../Element.h"
#include "../Rules/Rule.h"

class AddRuleCommand : public Command {
private:
    std::shared_ptr<Rule> rule;
    std::shared_ptr<IElement> originalElement;
    std::shared_ptr<IElement> decoratedElement;

public:
    AddRuleCommand(Project* project, std::shared_ptr<Rule> rule);

    void execute() override;
    void undo() override;
    std::string getDescription() override;
};
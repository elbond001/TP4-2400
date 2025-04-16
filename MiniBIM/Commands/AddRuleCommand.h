#pragma once
#include "Command.h"
#include "../Element.h"
#include "../Rules/Rule.h"

class AddRuleCommand : public Command {
private:
    Rule* rule;
    IElement* originalElement;
    IElement* decoratedElement;

public:
    AddRuleCommand(Project* project, IElement* elem, Rule* rule);

    void execute() override;
    void undo() override;
    std::string getDescription() override;
};
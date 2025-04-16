#include "AddRuleCommand.h"
#include "../Rules/RuleDecorator.h"
#include "../Project.h"

AddRuleCommand::AddRuleCommand(Project* project, IElement* elem, Rule* rule)
    : Command(project), rule(rule), originalElement(elem), decoratedElement(nullptr) {}

void AddRuleCommand::execute() {
    decoratedElement = project->addRule(originalElement, rule);
}

void AddRuleCommand::undo() {
    if (decoratedElement != nullptr) {
        IElement* restored = project->removeRule(decoratedElement, rule);
        if (restored) {
            decoratedElement = nullptr;
        }
    }
}
#include "RemoveRuleCommand.h"
#include "../Project.h"

RemoveRuleCommand::RemoveRuleCommand(Project* project, IElement* elementWithRule, Rule* rule)
    : Command(project), rule(rule), decoratedElement(elementWithRule), restoredElement(nullptr) {}

void RemoveRuleCommand::execute() {
    restoredElement = project->removeRule(decoratedElement, rule);
}

void RemoveRuleCommand::undo() {
    if (restoredElement != nullptr) {
        decoratedElement = project->addRule(restoredElement, rule);
    }
}
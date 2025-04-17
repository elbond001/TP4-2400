#include "RemoveRuleCommand.h"
#include "../Project.h"

RemoveRuleCommand::RemoveRuleCommand(Project* project, std::shared_ptr<IElement> elementWithRule, std::shared_ptr<Rule> rule)
    : Command(project), rule(rule), decoratedElement(elementWithRule), restoredElement(nullptr) {}

void RemoveRuleCommand::execute() {
    restoredElement = project->removeRule(decoratedElement, rule);
}

void RemoveRuleCommand::undo() {
    if (restoredElement != nullptr) {
        decoratedElement = project->addRule(restoredElement, rule);
    }
}

std::string RemoveRuleCommand::getDescription() {
    return ("Retrait de : " + rule->getDescription() + " a " + decoratedElement->getName());
}
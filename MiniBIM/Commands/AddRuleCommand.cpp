#include "AddRuleCommand.h"
#include "../Rules/ElementDecorator.h"
#include "../Project.h"

AddRuleCommand::AddRuleCommand(Project* project, std::shared_ptr<IElement> elem, std::shared_ptr<Rule> rule)
    : Command(project), rule(rule), originalElement(elem), decoratedElement(nullptr) {}

void AddRuleCommand::execute() {
    decoratedElement = project->addRule(originalElement, rule);
}

void AddRuleCommand::undo() {
    if (decoratedElement != nullptr) {
        std::shared_ptr<IElement> restored = project->removeRule(decoratedElement, rule);
        if (restored) {
            decoratedElement = nullptr;
        }
    }
}

std::string AddRuleCommand::getDescription() {
    return "Ajout de [" + std::string(rule->getDescription()) + "] a: " + originalElement->getElementType() +
           " (" + originalElement->getName() + ")";
}
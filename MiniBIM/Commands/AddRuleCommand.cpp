#include "AddRuleCommand.h"
#include "../Rules/ElementDecorator.h"
#include "../Project.h"

AddRuleCommand::AddRuleCommand(Project* project, std::shared_ptr<Rule> rule)
    : Command(project), rule(rule), originalElement(rule->getBaseElement()) {}

void AddRuleCommand::execute() {
    decoratedElement = project->addRule(rule);
}

void AddRuleCommand::undo() {
    if (decoratedElement != nullptr) {
        std::shared_ptr<IElement> restored = project->removeRule(rule);
        if (restored) {
            decoratedElement = nullptr;
        }
    }
}

std::string AddRuleCommand::getDescription() {
    return "Ajout de [" + std::string(rule->getDescription()) + "] a: " + originalElement->getElementType() +
           " (" + originalElement->getName() + ")";
}
#include "DeleteElementCommand.h"
#include <iostream>
#include <algorithm>

DeleteElementCommand::DeleteElementCommand(Project* p, std::shared_ptr<IElement> elem)
    : Command(p), element(elem)
{}

void DeleteElementCommand::execute() {
    project->removeElement(element);
}

void DeleteElementCommand::undo() {
    project->addElement(element);
}

std::string DeleteElementCommand::getDescription() {
    return "Retrait : " + element->getElementType() + " (" + element->getName() + ")";
}
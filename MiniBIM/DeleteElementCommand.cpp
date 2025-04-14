#include "DeleteElementCommand.h"
#include <iostream>
#include <algorithm>

DeleteElementCommand::DeleteElementCommand(Project* p, IElement* elem)
: Command(p), element(elem) 
{}

DeleteElementCommand::~DeleteElementCommand() {
    // Si vous êtes propriétaire de l'élément, vous pourriez le supprimer ici.
}

void DeleteElementCommand::execute() {
    project->removeElement(element);
}

void DeleteElementCommand::undo() {
    project->addElement(element);
}

std::string DeleteElementCommand::getDescription() {
    return ("[" + commandProposalName + "] " + "Retrait : " + element->getElementType() + " " + "(" + element->getName() + ")");
}

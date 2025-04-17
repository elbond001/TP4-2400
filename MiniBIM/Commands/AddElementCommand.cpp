#include "AddElementCommand.h"

AddElementCommand::AddElementCommand(Project* p, std::shared_ptr<IElement> elem)
: Command(p), element(elem) 
{}

AddElementCommand::~AddElementCommand() {
    // Si vous êtes propriétaire de l'élément, pensez à le supprimer ici (attention aux allocations)
}

void AddElementCommand::execute() {
    project->addElement(element);
}

void AddElementCommand::undo() {
    project->removeElement(element);
}

std::string AddElementCommand::getDescription() {
    return ("Ajout : " + element->getElementType() + " " + "(" + element->getName() + ")");
}

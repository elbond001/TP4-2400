#include "AddElementCommand.h"

AddElementCommand::AddElementCommand(Project* p, IElement* elem)
: Command(p), element(elem) 
{}

AddElementCommand::~AddElementCommand() {
    // Si vous êtes propriétaire de l'élément, pensez à le supprimer ici (attention aux allocations)
}

void AddElementCommand::execute() {
    project->addElement(element);
    //elements->push_back(element);
}

void AddElementCommand::undo() {
    //auto it = std::find(elements->begin(), elements->end(), element);
    //if (it != elements->end()) {
    //    elements->erase(it);
    //}
    project->removeElement(element);
}

std::string AddElementCommand::getDescription() {
    return ("[" + commandProposalName + "] " + "Ajout : " + element->getElementType() + " " + "(" + element->getName() + ")");
}

#include "AddElementCommand.h"

AddElementCommand::AddElementCommand(Project* proj, IElement* elem)
    : project(proj), element(elem)
{
}

AddElementCommand::~AddElementCommand() {
    // Si vous êtes propriétaire de l'élément, pensez à le supprimer ici (attention aux allocations)
}

void AddElementCommand::execute() {
    project->addElement(element);
}

void AddElementCommand::undo() {
    project->removeElement(element);
}

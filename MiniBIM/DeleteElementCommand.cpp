#include "DeleteElementCommand.h"
#include <iostream>

DeleteElementCommand::DeleteElementCommand(Project* proj, IElement* elem)
    : project(proj), element(elem)
{
}

DeleteElementCommand::~DeleteElementCommand() {
    // Si vous êtes propriétaire de l'élément, vous pourriez le supprimer ici.
}

void DeleteElementCommand::execute() {
    project->removeElement(element);
    std::cout << "Commande executee: L'element " 
              << element->getElementType() << " (" << element->getName() 
              << ") a ete retire de la maquette du project " 
              << project->getName() << std::endl;
}

void DeleteElementCommand::undo() {
    project->addElement(element);
    std::cout << "Commande undo: L'element " 
              << element->getElementType() << " (" << element->getName() 
              << ") a ete re-ajoute a la maquette du project " 
              << project->getName() << std::endl;
}

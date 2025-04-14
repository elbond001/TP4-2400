#include "DeleteElementCommand.h"
#include <iostream>
#include <algorithm>

DeleteElementCommand::DeleteElementCommand(std::vector<IElement*>* elements, IElement* elem)
    : elements(elements), element(elem)
{
}

DeleteElementCommand::~DeleteElementCommand() {
    // Si vous êtes propriétaire de l'élément, vous pourriez le supprimer ici.
}

void DeleteElementCommand::execute() {
    auto it = std::find(elements->begin(), elements->end(), element);
    if (it != elements->end()) {
        elements->erase(it);
    }
}

void DeleteElementCommand::undo() {
    elements->push_back(element);
}

#include "AddElementCommand.h"

AddElementCommand::AddElementCommand(std::vector<IElement*>* elements, IElement* elem)
    : elements(elements), element(elem)
{
}

AddElementCommand::~AddElementCommand() {
    // Si vous êtes propriétaire de l'élément, pensez à le supprimer ici (attention aux allocations)
}

void AddElementCommand::execute() {
    elements->push_back(element);
}

void AddElementCommand::undo() {
    //auto it = std::find(elements->begin(), elements->end(), element);
    //if (it != elements->end()) {
    //    elements->erase(it);
    //}
    elements->pop_back();
}

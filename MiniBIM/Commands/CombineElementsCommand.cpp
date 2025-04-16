#include "CombineElementsCommand.h"

CombineElementsCommand::CombineElementsCommand(Project *p, IElement *elem1, IElement *elem2, CompositeElement* compositeElem)
    : Command(p), element1(elem1), element2(elem2), newCombinedElement(compositeElem)
{
    newCombinedElement->add(element1);
    newCombinedElement->add(element2);

    combineElementsName = newCombinedElement->getName();
}

CombineElementsCommand::~CombineElementsCommand() {
    //delete newCombinedElement;
}

void CombineElementsCommand::execute()
{
    project->addElement(newCombinedElement);

    project->removeElement(element1);
    project->removeElement(element2);

    std::cout << "Combinaison " << newCombinedElement->getName() << " cree." << std::endl;
}

void CombineElementsCommand::undo()
{
    project->addElement(element1);
    project->addElement(element2);
}

std::string CombineElementsCommand::getDescription()
{
    return ("Combinaison en : " + combineElementsName);
}

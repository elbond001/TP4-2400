#include "CombineElementsCommand.h"

CombineElementsCommand::CombineElementsCommand(Project *p, IElement *elem1, IElement *elem2, std::string name)
    : Command(p), element1(elem1), element2(elem2), CombineElementsName(name)
{
    newCombinedElement = new CompositeElement(CombineElementsName);

    newCombinedElement->add(element1);
    newCombinedElement->add(element2);
}

void CombineElementsCommand::execute()
{
    project->addElement(newCombinedElement);

    project->removeElement(element1);
    project->removeElement(element2);
}

void CombineElementsCommand::undo() {
    project->addElement(element1);
    project->addElement(element2);
}

std::string CombineElementsCommand::getDescription() {
    return ("Combinaison : " + dissociatedElement->getElementType() + " depuis " + "(" + compositeElement->getName() + ")");
}

#include "CombineElementsCommand.h"

CombineElementsCommand::CombineElementsCommand(Project* p, 
                                               std::shared_ptr<IElement> elem1, 
                                               std::shared_ptr<IElement> elem2, 
                                               std::shared_ptr<CompositeElement> compositeElem)
    : Command(p), element1(elem1), element2(elem2), newCombinedElement(compositeElem)
{
    newCombinedElement->add(element1);
    newCombinedElement->add(element2);

    combineElementsName = newCombinedElement->getName();
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

    project->removeElement(newCombinedElement);
}

std::string CombineElementsCommand::getDescription()
{
    return "Combinaison en : " + combineElementsName;
}
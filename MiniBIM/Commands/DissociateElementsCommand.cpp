#include "DissociateElementsCommand.h"

DissociateElementsCommand::DissociateElementsCommand(Project* p, std::shared_ptr<IElement> elemToDissociate, std::shared_ptr<CompositeElement> compElem)
    : Command(p), dissociatedElement(elemToDissociate), compositeElement(compElem)
{}

void DissociateElementsCommand::execute()
{
    compositeElement->remove(dissociatedElement);
    project->addElement(dissociatedElement);
}

void DissociateElementsCommand::undo()
{
    compositeElement->add(dissociatedElement);
    project->removeElement(dissociatedElement);
}

std::string DissociateElementsCommand::getDescription() {
    return "Dissociation de : " + dissociatedElement->getElementType() + " depuis : (" + compositeElement->getName() + ")";
}
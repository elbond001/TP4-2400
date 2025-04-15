#include "DissociateElementsCommand.h"

DissociateElementsCommand::DissociateElementsCommand(Project* p, IElement* elemToDissociate, CompositeElement* compElem)
    : Command(p), dissociatedElement(elemToDissociate), compositeElement(compElem)
{}

DissociateElementsCommand::~DissociateElementsCommand() {
    delete dissociatedElement;
    delete compositeElement;
}

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
    return ("Dissociation de : " + dissociatedElement->getElementType() + " depuis " + "(" + compositeElement->getName() + ")");
}

#ifndef DISSOCIATEELEMENTSCOMMAND_H
#define DISSOCIATEELEMENTSCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "CompositeElement.h"

class DissociateElementsCommand : public Command
{
private:
    IElement * dissociatedElement;
    CompositeElement *compositeElement;

public:
    DissociateElementsCommand(Project *p, IElement* elemToDissociate, CompositeElement *compElem);
    virtual ~DissociateElementsCommand();
    virtual void execute() override;
    virtual void undo() override;

    virtual std::string getDescription() override;
};

#endif

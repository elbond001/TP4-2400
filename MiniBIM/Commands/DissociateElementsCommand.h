#ifndef DISSOCIATEELEMENTSCOMMAND_H
#define DISSOCIATEELEMENTSCOMMAND_H

#include "Command.h"
#include "../Project.h"
#include "../CompositeElement.h"
#include <memory>

class DissociateElementsCommand : public Command
{
private:
    std::shared_ptr<IElement> dissociatedElement;
    std::shared_ptr<CompositeElement> compositeElement;

public:
    DissociateElementsCommand(Project* p, std::shared_ptr<IElement> elemToDissociate, std::shared_ptr<CompositeElement> compElem);
    virtual void execute() override;
    virtual void undo() override;

    virtual std::string getDescription() override;
};

#endif
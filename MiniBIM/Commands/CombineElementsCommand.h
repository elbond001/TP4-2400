#ifndef COMBINEELEMENTSCOMMAND_H
#define COMBINEELEMENTSCOMMAND_H

#include "Command.h"
#include "../Project.h"
#include "../CompositeElement.h"
#include <memory>

class CombineElementsCommand : public Command
{
private:
    std::shared_ptr<IElement> element1;
    std::shared_ptr<IElement> element2;
    std::shared_ptr<CompositeElement> newCombinedElement;
    std::string combineElementsName;

public:
    CombineElementsCommand(Project* p, 
                           std::shared_ptr<IElement> elem1, 
                           std::shared_ptr<IElement> elem2, 
                           std::shared_ptr<CompositeElement> compositeElem);
    
    virtual void execute() override;
    virtual void undo() override;
    virtual std::string getDescription() override;
};

#endif
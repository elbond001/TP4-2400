#ifndef COMBINEELEMENTSCOMMAND_H
#define COMBINEELEMENTSCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "CompositeElement.h"

class CombineElementsCommand : public Command
{
private:
    IElement *element1;
    IElement *element2;
    CompositeElement *newCombinedElement;
    std::string combineElementsName;

public:
    CombineElementsCommand(Project *p, IElement *elem1, IElement *elem2, std::string combinedElementsName);
    virtual ~CombineElementsCommand();
    virtual void execute() override;
    virtual void undo() override;

    virtual std::string getDescription() override;
};

#endif

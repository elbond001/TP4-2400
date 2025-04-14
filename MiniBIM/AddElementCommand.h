#ifndef ADDELEMENTCOMMAND_H
#define ADDELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class AddElementCommand : public Command {
private:
    std::vector<IElement*>* elements;
    IElement* element;
public:
    AddElementCommand(std::vector<IElement*>* elements, IElement* elem);
    virtual ~AddElementCommand();
    virtual void execute() override;
    virtual void undo() override;
};

#endif

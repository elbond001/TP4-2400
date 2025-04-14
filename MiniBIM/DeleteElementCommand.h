#ifndef DELETEELEMENTCOMMAND_H
#define DELETEELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class DeleteElementCommand : public Command {
private:
    std::vector<IElement*>* elements;
    IElement* element;
public:
    DeleteElementCommand(std::vector<IElement*>* elements, IElement* elem);
    virtual ~DeleteElementCommand();
    virtual void execute() override;
    virtual void undo() override;
};

#endif

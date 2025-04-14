#ifndef DELETEELEMENTCOMMAND_H
#define DELETEELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class DeleteElementCommand : public Command {
private:
    Project* project;
    IElement* element;
public:
    DeleteElementCommand(Project* proj, IElement* elem);
    virtual ~DeleteElementCommand();
    virtual void execute() override;
    virtual void undo() override;
};

#endif

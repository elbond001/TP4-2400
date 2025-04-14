#ifndef ADDELEMENTCOMMAND_H
#define ADDELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class AddElementCommand : public Command {
private:
    Project* project;
    IElement* element;
public:
    AddElementCommand(Project* proj, IElement* elem);
    virtual ~AddElementCommand();
    virtual void execute() override;
    virtual void undo() override;
};

#endif

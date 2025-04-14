#ifndef DELETEELEMENTCOMMAND_H
#define DELETEELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class DeleteElementCommand : public Command {
private:
    IElement* element;
public:
    DeleteElementCommand(IElement* elem);
    virtual ~DeleteElementCommand();
    virtual void execute() override;
    virtual void undo() override;
    virtual std::string getDescription() override;
};

#endif

#ifndef ADDELEMENTCOMMAND_H
#define ADDELEMENTCOMMAND_H

#include "Command.h"
#include "Project.h"
#include "Element.h"

class AddElementCommand : public Command {
private:
    IElement* element;
public:
    AddElementCommand(Project* p, IElement* elem);
    virtual ~AddElementCommand();
    virtual void execute() override;
    virtual void undo() override;
    virtual std::string getDescription() override;
};

#endif

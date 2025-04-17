#ifndef DELETEELEMENTCOMMAND_H
#define DELETEELEMENTCOMMAND_H

#include "Command.h"
#include "../Project.h"
#include "../Element.h"
#include <memory>

class DeleteElementCommand : public Command {
private:
    std::shared_ptr<IElement> element;

public:
    DeleteElementCommand(Project* p, std::shared_ptr<IElement> elem);
    virtual void execute() override;
    virtual void undo() override;
    virtual std::string getDescription() override;
};

#endif
#ifndef ADDELEMENTCOMMAND_H
#define ADDELEMENTCOMMAND_H

#include "Command.h"
#include "../Project.h"
#include "../Element.h"

class AddElementCommand : public Command {
private:
    std::shared_ptr<IElement> element;
public:
    AddElementCommand(Project* p, std::shared_ptr<IElement> elem);
    virtual ~AddElementCommand();
    virtual void execute() override;
    virtual void undo() override;
    
    virtual std::string getDescription() override;
};

#endif

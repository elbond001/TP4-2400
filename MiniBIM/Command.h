#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Project;
class ModificationProposal;

class Command {
protected:
    std::string commandProposalName;
    Project* project;

public:
    Command(Project* p);
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getDescription() = 0;

    void setCommandProposalName(const std::string& name);
    void setProject(Project* p);
    Project* getProject() const;
};

#endif

#include "Command.h"

void Command::setCommandProposalName(const std::string& name) {
    commandProposalName = name;
}

void Command::setProject(Project* p) { 
    project = p; 
}

Project* Command::getProject() const { 
    return project; 
}
#ifndef MODIFICATIONPROPOSAL_H
#define MODIFICATIONPROPOSAL_H

#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Project.h"
#include "./Commands/CommandManager.h"

class Project;
class IElement;

enum class ProposalStatus { PENDING, ACCEPTED, REJECTED };

class ModificationProposal {
    private:
        Project* project;
        User* submitter;
        std::string title;
        std::vector<std::shared_ptr<Command>> commandList;
        ProposalStatus status;
    
    public:
        ModificationProposal(Project* proj, User* submitter, const std::string& title);

        void addCommand(std::shared_ptr<Command> command);
    
        void requestValidation();
        void accept(User* manager);
        void reject(User* manager);
    
        Project* getProject() const;
        User* getSubmitter() const;
        std::string getTitle() const;
        ProposalStatus getStatus() const;
        std::vector<std::shared_ptr<Command>> getCommands() const;

        void showCommands();
    };
    
    #endif

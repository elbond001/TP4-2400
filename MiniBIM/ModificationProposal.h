#ifndef MODIFICATIONPROPOSAL_H
#define MODIFICATIONPROPOSAL_H

#include <string>
#include <vector>
#include "User.h"
#include "Project.h"

class Project;
class IElement;

class ModificationProposal {
    private:
        Project* project;
        User* submitter;    // Ex. l'ingénieur
        std::string title;  // Ex. "Isolation Porte1"
    
    public:
        // Constructeur
        ModificationProposal(Project* proj, User* submitter, const std::string& title);
    
        void requestValidation();
        void accept(User* manager);
        void reject(User* manager);
    
        // Getters
        Project* getProject() const;
        User* getSubmitter() const;
        std::string getTitle() const;
    };
    
    #endif
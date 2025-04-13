#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "ModificationProposal.h"
class ModificationProposal;

class User {
protected:
    std::string name;

public:
    User(const std::string& name);
    virtual ~User();

    // Sera appelée quand il y aura une notification
    virtual void update(const std::string& message);

    std::string getName() const;
};

class Architect : public User {
    public:
        Architect(const std::string& name)
            : User(name)
        {}
        // On peut ajouter des méthodes si nécessaire
    };

class Engineer : public User {
public:
    Engineer(const std::string& name)
        : User(name)
    {}

    // L'ingénieur peut demander la validation
    void requestValidation(ModificationProposal* proposal);
};

class Manager : public User {
    public:
        Manager(const std::string& name)
            : User(name)
        {}
    
        // Le manager peut accepter ou rejeter
        void acceptProposal(ModificationProposal* proposal);
        void rejectProposal(ModificationProposal* proposal);
    };

#endif

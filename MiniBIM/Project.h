#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "IObservable.h"
#include "CommandManager.h"
#include "AddElementCommand.h"
#include "DeleteElementCommand.h"
#include "ModificationProposal.h"
#include <iostream>

// Forward declarations
class User;
class IElement;

class Project : public IObservable {  // <-- Héritage public
private:
    std::string name;
    std::vector<User*> users;     // Les utilisateurs du projet
    std::vector<IElement*> elements;
    std::vector<ModificationProposal*> proposals;
    
    CommandManager commandManager;

    // Ajout d’une liste (ou set) d’observateurs, si on veut séparer
    // la liste d’observateurs de la liste des users. 
    // Souvent, “users” == “observers”, mais on peut séparer si on souhaite
    // que certains users ne reçoivent pas les notifs.
    std::vector<User*> observers;  // On va y stocker ceux qui s'attachent
    
public:
    Project(const std::string& name);
    Project(const Project& projet, const std::string& name);

    const std::string& getName() const;
    const std::vector<User*>& getUsers() const;
    const std::vector<IElement*> getElements() const;
    const std::vector<User*> getObservers() const;
    std::vector<ModificationProposal*>* getProposals();
    CommandManager* getCommandManager();

    void showCommandHistory();

    // Méthodes de base
    void addUser(User* user);
    void removeUser(User* user);

    void addElement(IElement* elem);
    void removeElement(IElement* elem);
    void undoLastCommand();

    void addRule(IElement* element, const std::string& ruleName);
    
    // Méthodes d'IObservable
    virtual void attach(User* observer) override;
    virtual void detach(User* observer) override;
    virtual void notifyAll(const std::string& message) override;
};

#endif


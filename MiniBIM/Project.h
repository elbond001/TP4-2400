#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "IObservable.h"
#include "./Commands/CommandManager.h"
#include "./Commands/AddElementCommand.h"
#include "./Commands/DeleteElementCommand.h"
#include "ModificationProposal.h"
#include "./Rules/Rule.h"
#include "Element.h"

// Forward declarations
class User;
class IElement;

class Project : public IObservable {
private:
    std::string name;
    std::vector<User*> users;
    std::vector<std::shared_ptr<IElement>> elements;
    std::vector<ModificationProposal*> proposals;
    
    CommandManager commandManager;
    
    std::vector<User*> observers; 
    
public:
    Project(const std::string& name);
    Project(const Project& projet, const std::string& name);

    const std::string& getName() const;
    const std::vector<User*>& getUsers() const;
    const std::vector<std::shared_ptr<IElement>>& getElements() const;
    const std::vector<User*> getObservers() const;
    std::vector<ModificationProposal*>* getProposals();
    CommandManager* getCommandManager();

    void showCommandHistory();
    void showElements();

    void addUser(User* user);
    void removeUser(User* user);

    bool replaceElementInHierarchy(std::shared_ptr<IElement>& current,
        std::shared_ptr<IElement> target,
        std::shared_ptr<IElement> replacement);

    void addElement(std::shared_ptr<IElement> elem);
    void removeElement(std::shared_ptr<IElement> elem);
    void undoLastCommand();

    std::shared_ptr<IElement> findElementByName(const std::string& name);

    std::shared_ptr<IElement> addRule(std::shared_ptr<Rule> rule);
    std::shared_ptr<IElement> removeRule(std::shared_ptr<Rule> rule);
    
    virtual void attach(User* observer) override;
    virtual void detach(User* observer) override;
    virtual void notifyAll(const std::string& message) override;
};

#endif

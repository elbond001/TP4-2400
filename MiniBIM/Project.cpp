#include "Project.h"
#include "User.h"
#include "Element.h"
#include <algorithm> // std::find
#include "RuleDecorator.h"

Project::Project(const std::string& name)
    : name(name)
{
    std::cout << "Projet " << name << " est cree" << std::endl;
}

Project::Project(const Project& projet, const std::string& name)
{
    this->name = name;
    //this->users = projet.getUsers();
    this->elements = projet.getElements();
    //this->observers = projet.getObservers();

    std::cout << "Projet " << name << " est cree par copie" << std::endl;
}

const std::string& Project::getName() const {
    return name;
}

const std::vector<User*>& Project::getUsers() const {
    return users;
}

const std::vector<IElement*> Project::getElements() const {
    return elements;
}

const std::vector<User*> Project::getObservers() const {
    return observers;
}

const std::stack<Command*> Project::getCommandHistory() const {
    return commandManager.getCommandHistory();
}

void Project::addUser(User* user) {
    users.push_back(user);

    attach(user);
    std::cout << user->getName() 
        << " est ajoute au projet " 
        << this->name 
        << std::endl;
}

void Project::removeUser(User* user) {
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
    }

    detach(user);
}

void Project::addElement(IElement* elem) {
    commandManager.executeCommand(new AddElementCommand(&this->elements, elem));
}

void Project::removeElement(IElement* elem) {
    commandManager.executeCommand(new DeleteElementCommand(&this->elements, elem));
}

void Project::undoLastCommand() {
    commandManager.getCommandHistory().pop()
}

void Project::addRule(IElement* element, const std::string& ruleName) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {

        IElement* decoratedElement = new RuleDecorator(element, ruleName);
        
        *it = decoratedElement;
        
        std::cout << "L'element " 
                  << decoratedElement->getElementType() 
                  << " (" << decoratedElement->getName() 
                  << ") est enrobe de la regle [" << ruleName << "]." << std::endl;
    } else {
        std::cout << "L'element " << element->getName() << " n'a pas ete trouve dans le project " 
                  << name << std::endl;
    }
}
// ========================
// Méthodes IObservable
// ========================
void Project::attach(User* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it == observers.end()) {
        observers.push_back(observer);
    }
}

void Project::detach(User* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Project::notifyAll(const std::string& message) {
    for (User* obs : observers) {
        obs->update(message);
    }
}

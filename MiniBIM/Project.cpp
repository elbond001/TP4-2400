#include "Project.h"
#include "User.h"
#include "Element.h"
#include <algorithm>
#include "./Rules/RuleDecorator.h"

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

std::vector<ModificationProposal*>* Project::getProposals() {
    return &proposals;
}

CommandManager* Project::getCommandManager() {
    return &commandManager;
}



void Project::showCommandHistory() {

    std::cout << "Historique du projet '" << name << "' :" << std::endl;

    for(auto command : commandManager.getCommandHistory()) {
        std::cout << "  " << "[" + command->getProposalName() + "] " << command->getDescription() << std::endl;
    }
}

void Project::showElements() {
    std::cout << "Elements dans la maquette :" << std::endl;
    for(auto element : elements) {
        std::cout << "- " << element->getName() << " (" << element->getElementType() << ")" << std::endl;
    }
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

void Project::addElement(IElement* element) {
    elements.push_back(element);
}

void Project::removeElement(IElement* element) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        elements.erase(it);
    }
}

void Project::undoLastCommand() {
    commandManager.undoLastCommand();
}

IElement* Project::addRule(IElement* element, Rule* rule) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        IElement* decoratedElement = new RuleDecorator(element, rule);
        *it = decoratedElement;

        std::cout << "L'élément "
                  << decoratedElement->getElementType() << " (" 
                  << decoratedElement->getName()
                  << ") est enrobé de la règle [" << rule->getName()
                  << "] : " << rule->getDescription() << std::endl;

        return decoratedElement;
    } else {
        std::cout << "Élément non trouvé dans le projet." << std::endl;
        return nullptr;
    }
}

IElement* Project::removeRule(IElement* element, Rule* rule) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        RuleDecorator* decorator = dynamic_cast<RuleDecorator*>(element);
        if (decorator && decorator->getRule() == rule) {
            IElement* base = decorator->getBaseElement();
            *it = base;

            std::cout << "Règle [" << rule->getName() << "] retirée de l'élément " 
                      << base->getName() << std::endl;
            return base;
        } else {
            std::cout << "La règle ne correspond pas ou l'élément n'est pas un décorateur." << std::endl;
        }
    }
    return nullptr;
}

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

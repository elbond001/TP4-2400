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
    //this->observers = projet.getObservers();

    std::cout << "Projet " << name << " est cree par copie" << std::endl;
    //Creation d'une copie profonde elements
    for (IElement* elem : projet.getElements()) {
        elements.push_back(elem->clone());
    }

    //commandManager = CommandManager(projet.commandManager);
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
    for (IElement* element : elements) {
        if(RuleDecorator* rd = dynamic_cast<RuleDecorator*>(element))
            std::cout << "- " << rd->getBaseElement()->getName() << " (" << rd->getElementType() << ") avec [" << rd->getName() << "]"  << std::endl;
        else
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
        std::shared_ptr<Rule> rulePtr(rule, [](Rule*){});  // convertit le Rule* en shared_ptr
        IElement* decoratedElement = rule->decorate(element, rulePtr);
        *it = decoratedElement;

        std::cout << "Regle [" << rule->getName() << "] est ajoute a l'element " 
                  << element->getElementType() << " (" << element->getName() << ") !" << std::endl;

        return decoratedElement;
    } else {
        std::cout << "Element non trouve dans le projet." << std::endl;
        return nullptr;
    }
}

IElement* Project::removeRule(IElement* element, Rule* rule) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if (it != elements.end()) {
        RuleDecorator* decorator = dynamic_cast<RuleDecorator*>(element);
        if (decorator && decorator->getRule() && typeid(*decorator->getRule()) == typeid(*rule)) {
        //if (decorator && decorator->getRule() && decorator->getRule()->getName() == rule->getName()) {
            IElement* base = decorator->getBaseElement();
            *it = base;

            return base;
        } else {
            std::cout << "La regle ne correspond pas ou l'element n'est pas un decorateur." << std::endl;
        }
    }
    return nullptr;
}

IElement* Project::findElementByName(const std::string& name) {
    for (IElement* el : elements) {
        if (el->getName() == name) return el;
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

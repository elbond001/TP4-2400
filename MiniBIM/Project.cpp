#include "Project.h"
#include "User.h"
#include "Element.h"
#include <algorithm>
#include "./Rules/ElementDecorator.h"
#include "CompositeElement.h"

Project::Project(const std::string& name)
    : name(name)
{
    std::cout << "Projet " << name << " est cree" << std::endl;
}

Project::Project(const Project& projet, const std::string& name)
{
    this->name = name;
    std::cout << "Projet " << name << " est cree par copie" << std::endl;

    for (const auto& elem : projet.getElements()) {
        elements.push_back(std::shared_ptr<IElement>(elem->clone()));
    }
}

const std::string& Project::getName() const { return name; }

const std::vector<User*>& Project::getUsers() const { return users; }

const std::vector<std::shared_ptr<IElement>>& Project::getElements() const { return elements; }

const std::vector<User*> Project::getObservers() const { return observers; }

std::vector<ModificationProposal*>* Project::getProposals() { return &proposals; }

CommandManager* Project::getCommandManager() { return &commandManager; }

void Project::showCommandHistory() {
    std::cout << "Historique du projet '" << name << "' :" << std::endl;
    for (auto command : commandManager.getCommandHistory()) {
        std::cout << "  [" << command->getProposalName() << "] " << command->getDescription() << std::endl;
    }
}

void Project::showElements() {
    std::cout << "Elements dans la maquette :" << std::endl;
    for (const auto& element : elements) {
        element->showDescription(0);
    }
}

void Project::addUser(User* user) {
    users.push_back(user);
    attach(user);
    std::cout << user->getName() << " est ajoute au projet " << this->name << std::endl;
}

void Project::removeUser(User* user) {
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
    }
    detach(user);
}

void Project::addElement(std::shared_ptr<IElement> element) {
    if (std::find(elements.begin(), elements.end(), element) == elements.end()) {
        elements.push_back(element);
    }
}

void Project::removeElement(std::shared_ptr<IElement> element) {
    elements.erase(std::remove(elements.begin(), elements.end(), element), elements.end());
}

void Project::undoLastCommand() {
    commandManager.undoLastCommand();
}

bool Project::replaceElementInHierarchy(std::shared_ptr<IElement>& current,
                                        std::shared_ptr<IElement> target,
                                        std::shared_ptr<IElement> replacement)
{
    if (current == target) {
        current = replacement;
        return true;
    }

    if (auto composite = std::dynamic_pointer_cast<CompositeElement>(current)) {
        auto children = composite->getComponents();
        for (auto child : children) {
            if (replaceElementInHierarchy(child, target, replacement)) {
                return true;
            }
        }
    }

    return false;
}

std::shared_ptr<IElement> Project::addRule(std::shared_ptr<Rule> rule) {
    std::shared_ptr<IElement> decoratedElement = rule->decorate();
    bool replaced = false;

    // Remplacer dans la liste principale si présent
    for (auto& e : elements) {
        if (e == rule->getBaseElement()) {
            e = decoratedElement;
            replaced = true;
        }
    }

    // Remplacer dans les compositeElements
    for (auto& e : elements) {
        if (replaceElementInHierarchy(e, rule->getBaseElement(), decoratedElement)) {
            replaced = true;
        }
    }

    if (replaced) {
        return decoratedElement;
    }

    std::cout << "Element non trouve dans le projet." << std::endl;
    return nullptr;
}

std::shared_ptr<IElement> Project::removeRule(std::shared_ptr<Rule> ruleToRemove) {
    auto it = std::find(elements.begin(), elements.end(), ruleToRemove);
    if (it == elements.end()) {
        std::cout << "Element non trouvé dans le projet." << std::endl;
        return nullptr;
    }

    std::shared_ptr<IElement> current = *it;
    std::shared_ptr<ElementDecorator> previousDecorator = nullptr;

    while (auto decorator = std::dynamic_pointer_cast<ElementDecorator>(current)) {
        auto rule = std::dynamic_pointer_cast<Rule>(decorator);
        if (rule && rule->getDescription() == ruleToRemove->getDescription()) {
            std::shared_ptr<IElement> newBase = decorator->getBaseElement();

            if (previousDecorator) {
                previousDecorator->setBaseElement(newBase);
            } else {
                *it = newBase;
            }

            std::cout << "Regle [" << rule->getDescription() << "] retiree de l'element "
                      << newBase->getElementType() << " (" << newBase->getName() << ") !" << std::endl;

            return newBase;
        }

        previousDecorator = decorator;
        current = decorator->getBaseElement();
    }

    std::cout << "La regle n'a pas ete trouvee parmi les decorateurs." << std::endl;
    return nullptr;
}

std::shared_ptr<IElement> Project::findElementByName(const std::string& name) {
    for (const auto& el : elements) {
        if (el->getName() == name) return el;
    }
    return nullptr;
}


void Project::attach(User* observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
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
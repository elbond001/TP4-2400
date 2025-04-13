#include "Project.h"
#include "User.h"
#include "Element.h"
#include <algorithm> // std::find


Project::Project(const std::string& name)
    : name(name)
{
    std::cout << "Projet " << name << " est cree" << std::endl;
}

const std::string& Project::getName() const {
    return name;
}

void Project::addUser(User* user) {
    users.push_back(user);

    // Automatiquement attacher ce user au notifications, si on veut
    // On suppose ici que tout user ajouté au projet veut recevoir les notifications
    attach(user);
    std::cout << user->getName() 
        << " est ajoute au projet " 
        << this->name 
        << std::endl;
}

void Project::removeUser(User* user) {
    // On le retire de la liste users
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
    }

    // On le retire également de la liste observers
    detach(user);
}

void Project::addElement(IElement* elem) {
    elements.push_back(elem);

    // On peut notifier tout le monde qu’un élément est ajouté
    // (Nous verrons ensuite si on veut l’inscrire dans une proposition)
    // Ex.: notifyAll("Element " + elem->getName() + " a ete ajoute au projet " + name);
    std::cout << "Element " 
        << elem->getElementType()
        << " (" << elem->getName() << ") "
        << "a ete ajoute a la maquette du project "
        << this->name
        << std::endl;
}

void Project::removeElement(IElement* elem) {
    auto it = std::find(elements.begin(), elements.end(), elem);
    if (it != elements.end()) {
        elements.erase(it);
    }
}
void Project::addRule(IElement* element, const std::string& ruleName) {
    // "Regle [Isolation] est ajoutee a l'element Door (Porte1) !"
    std::cout << "Regle [" << ruleName << "] est ajoutee a l'element "
              << element->getElementType() 
              << " (" << element->getName() << ") !"
              << std::endl;
}
// ========================
// Méthodes IObservable
// ========================
void Project::attach(User* observer) {
    // On s’assure de ne pas le mettre 2x
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

#include <iostream>
#include "./MiniBIM/Project.h"
#include "./MiniBIM/User.h"
#include "./MiniBIM/ElementTypes.h"
#include "./MiniBIM/ModificationProposal.h"


int main() {
    // 1) Créer les projets
    Project alpha("ProjectAlpha");
    Project beta("ProjectBeta");

    User* alice = UserFactory::createUser(UserType::ARCHITECT, "Alice Dupont");
    User* bob = UserFactory::createUser(UserType::ENGINEER, "Bob Matrin");
    User* charlie = UserFactory::createUser(UserType::MANAGER, "Charlie Durand");
    User* eva = new User("Eva Moreau");
    User* david = new User("David Leroy");
    User* fiona = new User("Fiona Leclerc");
    User* greg = UserFactory::createUser(UserType::ENGINEER, "Greg Morel");


    alpha.addUser(alice);
    alpha.addUser(bob);
    alpha.addUser(charlie);

    beta.addUser(alice);
    beta.addUser(bob);
    beta.addUser(david);

    Wall mur1("Mur1");
    alpha.addElement(&mur1);

    Door porte1("Porte1");
    alpha.addElement(&porte1);

    Door porte2("Porte2");
    alpha.addElement(&porte2);

    alpha.addRule(&porte1, "Isolation");

    ModificationProposal prop1(&alpha, bob, "PropositionAlpha");

    if(Engineer* engineer = dynamic_cast<Engineer*>(bob))
        engineer->requestValidation(&prop1);


    if(Manager* manager = dynamic_cast<Manager*>(charlie))
        manager->acceptProposal(&prop1);


    Wall mur2("Mur2");
    beta.addElement(&mur2);

    Door porte3("Porte3");
    beta.addElement(&porte3);

    Window fenetre1("Fenetre1");
    beta.addElement(&fenetre1);

    beta.addUser(eva);

    beta.addRule(&mur2, "Contraintes de charge");

    beta.detach(alice);

    ModificationProposal prop2(&beta, bob, "PropositionBeta");
    if(Engineer* engineer = dynamic_cast<Engineer*>(bob))
        engineer->requestValidation(&prop2);

    if(Manager* manager = dynamic_cast<Manager*>(charlie))
        manager->rejectProposal(&prop2);

    Project alphaCopy(alpha, "ProjectAlphaCopy");

    alphaCopy.addUser(charlie);
    alphaCopy.addUser(fiona);
    alphaCopy.addUser(greg);

    Wall mur3("Mur3");
    alphaCopy.addElement(&mur3);

    alphaCopy.addRule(&mur3, "Estimation des couts");

    ModificationProposal prop3(&alphaCopy, greg, "PropositionAlphaCopy");
    if(Engineer* engineer = dynamic_cast<Engineer*>(greg))
        engineer->requestValidation(&prop3);

    if(Manager* manager = dynamic_cast<Manager*>(charlie))
        manager->acceptProposal(&prop3);

    return 0;
}

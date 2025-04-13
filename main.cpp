#include <iostream>
#include "./MiniBIM/Project.h"
#include "./MiniBIM/User.h"
#include "./MiniBIM/ElementTypes.h"
#include "./MiniBIM/ModificationProposal.h"


int main() {
    // 1) Créer les projets
    Project alpha("ProjectAlpha");
    Project beta("ProjectBeta");

    // 2) Créer les utilisateurs : ex. (Architect) Alice, (Engineer) Bob, (Manager) Charlie
    Architect alice("Alice Dupont");
    Engineer bob("Bob Martin");
    Manager charlie("Charlie Durand");
    User eva("Eva Moreau");
    User david("David Leroy");
    User fiona("Fiona Leclerc");
    Engineer greg("Greg Morel");

    // 3) Associer les utilisateurs à alpha
    alpha.addUser(&alice);
    alpha.addUser(&bob);
    alpha.addUser(&charlie);

    beta.addUser(&alice);
    beta.addUser(&bob);
    beta.addUser(&david);

    // 4) Ajouter des éléments (Mur1, Porte1, Porte2) 
    Wall mur1("Mur1");
    alpha.addElement(&mur1);

    Door porte1("Porte1");
    alpha.addElement(&porte1);

    Door porte2("Porte2");
    alpha.addElement(&porte2);

    // 5) L'ingénieur ajoute une règle sur Porte1
    alpha.addRule(&porte1, "Isolation");

    // 6) L'ingénieur "Bob" demande la validation
    ModificationProposal prop1(&alpha, &bob, "PropositionAlpha");
    bob.requestValidation(&prop1);

    // 7) Le manager "Charlie" accepte
    charlie.acceptProposal(&prop1);


    Wall mur2("Mur2");
    beta.addElement(&mur2);

    Door porte3("Porte3");
    beta.addElement(&porte3);

    Window fenetre1("Fenetre1");
    beta.addElement(&fenetre1);

    beta.addUser(&eva);

    beta.addRule(&mur2, "Contraintes de charge");

    beta.detach(&alice);

    ModificationProposal prop2(&beta, &bob, "PropositionBeta");
    bob.requestValidation(&prop2);

    charlie.rejectProposal(&prop2);

    Project alphaCopy(alpha, "ProjectAlphaCopy");

    alphaCopy.addUser(&charlie);
    alphaCopy.addUser(&fiona);
    alphaCopy.addUser(&greg);

    Wall mur3("Mur3");
    alphaCopy.addElement(&mur3);

    alphaCopy.addRule(&mur3, "Estimation des couts");

    ModificationProposal prop3(&alphaCopy, &greg, "PropositionAlphaCopy");
    greg.requestValidation(&prop3);

    charlie.acceptProposal(&prop3);

    return 0;
}

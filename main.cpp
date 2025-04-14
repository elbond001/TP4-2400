#include <iostream>
#include "./MiniBIM/Project.h"
#include "./MiniBIM/User.h"
#include "./MiniBIM/ElementTypes.h"
#include "./MiniBIM/ModificationProposal.h"
#include "./MiniBIM/AddElementCommand.h"
#include "./MiniBIM/RuleDecorator.h"
#include "./MiniBIM/CompositeElement.h"
#include "./MiniBIM/CommandManager.h"
#include "./MiniBIM/DeleteElementCommand.h"

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


    // 1. Test du decorator
    // On crée une porte "Porte4" puis on l'enrobe d'une règle "Simulation de performance energetique"
    Door porte4("Porte4");
    RuleDecorator decoratedPorte(&porte4, "Simulation de performance energetique");
    // Affichage pour vérifier
    std::cout << "L'element " << decoratedPorte.getElementType() << " ("
            << decoratedPorte.getName() << ") est enrobe de la regle ["
            << decoratedPorte.getRule() << "]." << std::endl;

    // 2. Test du composite
    CompositeElement salle("Salle1");
    salle.add(&mur1);
    salle.add(&porte1);
    std::cout << "Composite cree : " << salle.getName() << " (" << salle.getElementType() << ")" << std::endl;

    // 3. Test du Command
    AddElementCommand addCmd(&alpha, &porte4);
    addCmd.execute();  // Ceci ajoute Porte4 dans ProjectAlpha
    // ... et ensuite on peut annuler
    addCmd.undo();
    // Par exemple, prenons ProjectAlpha et une nouvelle porte "Porte5"
    Door porte5("Porte5");

    // Créons une commande pour ajouter Porte5 dans ProjectAlpha
    alpha.addElement(&porte5);
    //CommandManager cmdManager;
    //AddElementCommand* addPorte5 = new AddElementCommand(&alpha, &porte5);
    
    // Exécuter la commande via le gestionnaire
    //cmdManager.executeCommand(addPorte5);

    // Affichage immédiat pour vérifier l'ajout :
    // (Dans la sortie, on devrait voir "Element Door (Porte5) a ete ajoute a la maquette du project ProjectAlpha")
    
    // Maintenant, on effectue un undo pour annuler l'ajout
    cmdManager.undoLastCommand();  // Ceci doit retirer Porte5 de ProjectAlpha

    // Tu peux aussi tester d'autres commandes et faire plusieurs undo...
    // Test avancé du CommandManager :
    // Création d'une nouvelle porte "Porte6" pour le projet alpha.
    Door porte6("Porte6");

    // Création d'un gestionnaire de commandes.


    // 1. Commande pour ajouter Porte6 à ProjectAlpha (alpha est créé plus tôt)
    AddElementCommand* addPorte6 = new AddElementCommand(&alpha, &porte6);
    cmdManager.executeCommand(addPorte6);  
    // Ce qui doit afficher : "Element Door (Porte6) a ete ajoute a la maquette du project ProjectAlpha"

    // 2. Commande pour supprimer Porte6 de ProjectAlpha.
    DeleteElementCommand* delPorte6 = new DeleteElementCommand(&alpha, &porte6);
    cmdManager.executeCommand(delPorte6);  
    // Cela devrait retirer Porte6 et afficher le message associé.

    // 3. Faire un undo de la dernière commande (qui devrait réinsérer Porte6).
    cmdManager.undoLastCommand();
    // Devrait afficher un message indiquant que Porte6 a été ré-ajoutée.

    // 4. Faire un undo de la commande précédente (qui devrait annuler l'ajout initial de Porte6).
    cmdManager.undoLastCommand();
    // -------------------------------
    // Test avancé du Composite
    // -------------------------------

    // 1. Création de nouveaux éléments "Mur4" et "Plancher1"
    Wall mur4("Mur4");
    // Pour cet exemple, nous utilisons Door pour "Plancher1" (ou, si tu as un type spécifique, utilise-le)
    Door plancher1("Plancher1");

    // 2. Combiner Mur1 et Mur4 en un composite "Cloisonnement"
    // Remarque : 'mur1' a déjà été créé et ajouté au projet alpha précédemment.
    CompositeElement cloisonnement("Cloisonnement");
    cloisonnement.add(&mur1);
    cloisonnement.add(&mur4);
    std::cout << "Composite 'Cloisonnement' cree : " 
              << cloisonnement.getName() << " (" 
              << cloisonnement.getElementType() << ")" << std::endl;

    // 3. Combiner Porte1, Plancher1 et Cloisonnement en "Structure murale"
    CompositeElement structureMurale("Structure murale");
    structureMurale.add(&porte1);
    structureMurale.add(&plancher1);
    structureMurale.add(&cloisonnement);
    std::cout << "Composite 'Structure murale' cree : " 
              << structureMurale.getName() << " (" 
              << structureMurale.getElementType() << ")" << std::endl;

    // 4. Dissocier Plancher1 de "Structure murale" (supprimer plancher1 du composite)
    structureMurale.remove(&plancher1);
    std::cout << "Plancher1 dissocie de 'Structure murale'" << std::endl;

    // 5. Combiner Plancher1 et Structure murale en "Salle1"
    CompositeElement salle1("Salle1");
    salle1.add(&structureMurale);
    salle1.add(&plancher1);
    std::cout << "Composite 'Salle1' cree : " 
              << salle1.getName() << " (" 
              << salle1.getElementType() << ")" << std::endl;
    return 0;
}

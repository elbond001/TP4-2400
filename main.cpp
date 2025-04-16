#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <iostream>
#include "./MiniBIM/Project.h"
#include "./MiniBIM/User.h"
#include "./MiniBIM/ElementTypes.h"
#include "./MiniBIM/ModificationProposal.h"
#include "./MiniBIM/Commands/AddElementCommand.h"
#include "./MiniBIM/Rules/RuleDecorator.h"
#include "./MiniBIM/CompositeElement.h"
#include "./MiniBIM/Commands/CommandManager.h"
#include "./MiniBIM/Commands/DeleteElementCommand.h"
#include "./MiniBIM/Commands/CombineElementsCommand.h"
#include "./MiniBIM/Commands/DissociateElementsCommand.h"
#include "./MiniBIM/Commands/AddRuleCommand.h"
#include "./MiniBIM/Commands/RemoveRuleCommand.h"
#include "./MiniBIM/Rules/ChargeRule.cpp"
#include "./MiniBIM/Rules/IsolationRule.cpp"
#include "./MiniBIM/Rules/CostEstimationRule.cpp"
#include "./MiniBIM/Rules/EnergyPerformanceRule.cpp"

int main()
{


    Project alpha("ProjectAlpha");
    Project beta("ProjectBeta");

    User *alice = UserFactory::createUser(UserType::ARCHITECT, "Alice Dupont");
    User *bob = UserFactory::createUser(UserType::ENGINEER, "Bob Matrin");
    User *charlie = UserFactory::createUser(UserType::MANAGER, "Charlie Durand");
    User *eva = new User("Eva Moreau");
    User *david = new User("David Leroy");
    User *fiona = new User("Fiona Leclerc");
    User *greg = UserFactory::createUser(UserType::ENGINEER, "Greg Morel");

    alpha.addUser(alice);
    alpha.addUser(bob);
    alpha.addUser(charlie);

    beta.addUser(alice);
    beta.addUser(bob);
    beta.addUser(david);

    std::cout << std::endl;

    Wall mur1("Mur1");
    Door porte1("Porte1");
    Door porte2("Porte2");

    ModificationProposal prop1(&alpha, alice, "Ajouts Initiaux Alpha");

    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, &mur1));
    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, &porte1));
    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, &porte2));

    prop1.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop1);

    ModificationProposal prop2(&alpha, bob, "Isolation porte1");

    

    std::shared_ptr<IsolationRule> rule1 = std::make_shared<IsolationRule>(&porte1);
    prop2.addCommand(std::make_shared<AddRuleCommand>(&alpha, &porte1, rule1.get()));

    prop2.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop2);

    std::cout << std::endl;
    std::cout << std::endl;

    Wall mur2("Mur2");
    Door porte3("Porte3");
    Window fenetre1("Fenetre1");
    

    ModificationProposal prop3(&beta, alice, "Ajouts Initiaux Beta");
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, &mur2));
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, &porte3));
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, &fenetre1));

    prop3.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop3);


    beta.addUser(eva);


    ModificationProposal prop4(&beta, bob, "Charge Mur2");

    auto rule2 = std::make_shared<ChargeRule>(&mur2);
    prop4.addCommand(std::make_shared<AddRuleCommand>(&beta, &mur2, rule2.get()));

    prop4.showCommands();
    prop4.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->rejectProposal(&prop4);

    beta.showCommandHistory();



    std::cout << std::endl;


    Project alphaCopy(alpha, "ProjectAlphaCopy");

    alphaCopy.addUser(charlie);
    alphaCopy.addUser(fiona);
    alphaCopy.addUser(greg);

    Wall mur3("Mur3");

    ModificationProposal prop5(&alphaCopy, fiona, "Ajout Mur 3");
    prop5.addCommand(std::make_shared<AddElementCommand>(&alphaCopy, &mur3));
    prop5.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop5);

    ModificationProposal prop6(&alphaCopy, greg, "Estimation couts");
    std::shared_ptr<CostEstimationRule> rule3 = std::make_shared<CostEstimationRule>(alphaCopy.getElements().front());
    prop6.addCommand(std::make_shared<AddRuleCommand>(&alphaCopy, alphaCopy.getElements().front(), rule3.get()));

    prop6.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop6);

    alphaCopy.showElements();

    alphaCopy.undoLastCommand();

    alphaCopy.showElements();

    alpha.showCommandHistory();

    HeatingFloor plancher1("Plancher1");
    Wall mur4("Mur4");
    CompositeElement cloisonnement("Cloisonnement");
    cloisonnement.add(&mur1);
    cloisonnement.add(&mur4);

    CompositeElement structureMurale("StructureMurale");
    cloisonnement.add(&cloisonnement);
    cloisonnement.add(&porte1);

    CompositeElement salle1("Salle1");
    cloisonnement.add(&structureMurale);
    cloisonnement.add(&plancher1);


    ModificationProposal prop7(&alpha, fiona, "Niveaux d'architecture");
    prop7.addCommand(std::make_shared<AddElementCommand>(&alphaCopy, &plancher1));
    prop7.addCommand(std::make_shared<AddElementCommand>(&alphaCopy, &mur4));
    prop7.addCommand(std::make_shared<DeleteElementCommand>(&alphaCopy, &porte2));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alphaCopy, &mur1, &mur4, &cloisonnement));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alphaCopy, &cloisonnement, &porte1, &structureMurale));
    prop7.addCommand(std::make_shared<DissociateElementsCommand>(&alphaCopy, &plancher1, &structureMurale));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alphaCopy, &structureMurale, &plancher1, &salle1));
    
    

    prop7.showCommands();

    prop7.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop7);

    
    std::cout << std::endl;


    ModificationProposal prop8(&alpha, bob, "PerformancePlancher");

    auto rule4 = std::make_shared<EnergyPerformanceRule>(&plancher1);
    prop8.addCommand(std::make_shared<AddRuleCommand>(&alphaCopy, &plancher1, rule4.get()));

    prop8.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop8);

    alphaCopy.showElements();


    std::cout << std::endl;


    alphaCopy.showCommandHistory();


//     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//     _CrtDumpMemoryLeaks();
     return 0;
}
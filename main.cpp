#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "./MiniBIM/Project.h"
#include "./MiniBIM/User.h"
#include "./MiniBIM/ElementTypes.h"
#include "./MiniBIM/ModificationProposal.h"
#include "./MiniBIM/Commands/AddElementCommand.h"
#include "./MiniBIM/Rules/ElementDecorator.h"
#include "./MiniBIM/CompositeElement.h"
#include "./MiniBIM/Commands/CommandManager.h"
#include "./MiniBIM/Commands/DeleteElementCommand.h"
#include "./MiniBIM/Commands/CombineElementsCommand.h"
#include "./MiniBIM/Commands/DissociateElementsCommand.h"
#include "./MiniBIM/Commands/AddRuleCommand.h"
#include "./MiniBIM/Commands/RemoveRuleCommand.h"
#include "./MiniBIM/Rules/ChargeRule.h"
#include "./MiniBIM/Rules/IsolationRule.h"
#include "./MiniBIM/Rules/CostEstimationRule.h"
#include "./MiniBIM/Rules/EnergyPerformanceRule.h"

int main()
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

     Project alpha("ProjectAlpha");
    Project beta("ProjectBeta");

    User *alice = UserFactory::createUser(UserType::ARCHITECT, "Alice Dupont");
    User *bob = UserFactory::createUser(UserType::ENGINEER, "Bob Matrin");
    User *charlie = UserFactory::createUser(UserType::MANAGER, "Charlie Durand");
    User *eva = new User("Eva Moreau");
    User *david = UserFactory::createUser(UserType::MANAGER, "David Leroy");
    User *fiona = UserFactory::createUser(UserType::ARCHITECT, "Fiona Leclerc");
    User *greg = UserFactory::createUser(UserType::ENGINEER, "Greg Morel");

    alpha.addUser(alice);
    alpha.addUser(bob);
    alpha.addUser(charlie);

    beta.addUser(alice);
    beta.addUser(bob);
    beta.addUser(david);

    std::cout << std::endl;

    auto mur1 = std::make_shared<Wall>("Mur1");
    auto porte1 = std::make_shared<Door>("Porte1");
    auto porte2 = std::make_shared<Door>("Porte2");

    ModificationProposal prop1(&alpha, alice, "Ajouts Initiaux Alpha");

    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, mur1));
    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, porte1));
    prop1.addCommand(std::make_shared<AddElementCommand>(&alpha, porte2));

    prop1.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop1);

    ModificationProposal prop2(&alpha, bob, "Isolation porte1");

    

    std::shared_ptr<IsolationRule> rule1 = std::make_shared<IsolationRule>(porte1);
    prop2.addCommand(std::make_shared<AddRuleCommand>(&alpha, rule1));

    prop2.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop2);

    std::cout << std::endl;

    auto mur2 = std::make_shared<Wall>("Mur2");
    auto porte3 = std::make_shared<Door>("Porte3");
    auto fenetre1 = std::make_shared<Window>("Fenetre1");
    

    ModificationProposal prop3(&beta, alice, "Ajouts Initiaux Beta");
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, mur2));
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, porte3));
    prop3.addCommand(std::make_shared<AddElementCommand>(&beta, fenetre1));

    prop3.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(david))
        manager->acceptProposal(&prop3);


    beta.addUser(eva);
    beta.detach(alice);


    ModificationProposal prop4(&beta, bob, "Charge Mur2");

    auto rule2 = std::make_shared<ChargeRule>(mur2);
    prop4.addCommand(std::make_shared<AddRuleCommand>(&beta, rule2));

    prop4.showCommands();
    prop4.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(david))
        manager->rejectProposal(&prop4);

    beta.showCommandHistory();



    std::cout << std::endl;


    Project alphaCopy(alpha, "ProjectAlphaCopy");

    alphaCopy.addUser(charlie);
    alphaCopy.addUser(fiona);
    alphaCopy.addUser(greg);

    auto mur3 = std::make_shared<Wall>("Mur3");

    ModificationProposal prop5(&alphaCopy, fiona, "Ajout Mur 3");
    prop5.addCommand(std::make_shared<AddElementCommand>(&alphaCopy, mur3));
    prop5.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop5);

    ModificationProposal prop6(&alphaCopy, greg, "Estimation couts");
    std::shared_ptr<CostEstimationRule> rule3 = std::make_shared<CostEstimationRule>(alphaCopy.getElements().front());
    prop6.addCommand(std::make_shared<AddRuleCommand>(&alphaCopy, rule3));

    prop6.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop6);

    alphaCopy.showElements();

    alphaCopy.undoLastCommand();

    alphaCopy.showElements();

    alpha.showCommandHistory();

    auto plancher1 = std::make_shared<HeatingFloor>("Plancher1");
    auto mur4 = std::make_shared<Wall>("Mur4");
    auto cloisonnement = std::make_shared<CompositeElement>("Cloisonnement");
    //cloisonnement->add(mur1);
    //cloisonnement->add(mur4);

    auto structureMurale = std::make_shared<CompositeElement>("Structure murale");
    //structureMurale->add(cloisonnement);
    //structureMurale->add(porte1);

    auto salle1 = std::make_shared<CompositeElement>("Salle1");
    //salle1->add(structureMurale);
    //salle1->add(plancher1);


    ModificationProposal prop7(&alpha, fiona, "Niveaux d'architecture");
    prop7.addCommand(std::make_shared<AddElementCommand>(&alpha, plancher1));
    prop7.addCommand(std::make_shared<AddElementCommand>(&alpha, mur4));
    prop7.addCommand(std::make_shared<DeleteElementCommand>(&alpha, porte2));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alpha, mur1, mur4, cloisonnement));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alpha, cloisonnement, porte1, structureMurale));
    prop7.addCommand(std::make_shared<DissociateElementsCommand>(&alpha, plancher1, structureMurale));
    prop7.addCommand(std::make_shared<CombineElementsCommand>(&alpha, structureMurale, plancher1, salle1));
    
    

    prop7.showCommands();

    prop7.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop7);

    
    std::cout << std::endl;


    ModificationProposal prop8(&alpha, bob, "PerformancePlancher");

    auto rule4 = std::make_shared<EnergyPerformanceRule>(plancher1);
    prop8.addCommand(std::make_shared<AddRuleCommand>(&alpha, rule4));

    prop8.requestValidation();

    if (Manager *manager = dynamic_cast<Manager *>(charlie))
        manager->acceptProposal(&prop8);

    alpha.showElements();


    std::cout << std::endl;


    alpha.showCommandHistory();

    plancher1->showDescription(0);

    _CrtDumpMemoryLeaks();

    return 0;
}
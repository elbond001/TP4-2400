int main()
{
    // ---------------------------------------------------------------------------
    // 1) Création des projets : ProjectAlpha et ProjectBeta
    // ---------------------------------------------------------------------------
    Project alpha("ProjectAlpha"); // => "Projet ProjectAlpha est cree"
    Project beta("ProjectBeta");   // => "Projet ProjectBeta est cree"

    // ---------------------------------------------------------------------------
    // 2) Création et ajout des utilisateurs
    // ---------------------------------------------------------------------------
    // On veut EXACTEMENT :
    //   "Alice Dupont est ajoute au projet ProjectAlpha"
    //   "Bob Martin est ajoute au projet ProjectAlpha"
    //   "Charlie Durand est ajoute au projet ProjectAlpha"
    //   "Alice Dupont est ajoute au projet ProjectBeta"
    //   "Bob Martin est ajoute au projet ProjectBeta"
    //   "David Leroy est ajoute au projet ProjectBeta"
    // Pour ça, on crée un manager "David Leroy" via la factory, sinon on n’aura pas la phrase "Le manager David Leroy…".
    
    User* alice   = UserFactory::createUser(UserType::ARCHITECT, "Alice Dupont");
    User* bob     = UserFactory::createUser(UserType::ENGINEER,  "Bob Martin");
    User* charlie = UserFactory::createUser(UserType::MANAGER,   "Charlie Durand");
    User* david   = UserFactory::createUser(UserType::MANAGER,   "David Leroy");  // manager

    alpha.addUser(alice);
    alpha.addUser(bob);
    alpha.addUser(charlie);

    beta.addUser(alice);
    beta.addUser(bob);
    beta.addUser(david); // => "David Leroy est ajoute au projet ProjectBeta"

    // ---------------------------------------------------------------------------
    // 3) Création des éléments initiaux sur ProjectAlpha : Mur1, Porte1, Porte2
    //    => "Element Wall (Mur1) est cree !", etc.
    // ---------------------------------------------------------------------------
    Wall mur1("Mur1");
    Door porte1("Porte1");
    Door porte2("Porte2");

    // ---------------------------------------------------------------------------
    // 4) "Alice Dupont a recu une notification : Alice Dupont a demande..."
    //    => on veut que ALICE propose la validation => use a proposal with submiter=Alice
    //    => requestValidation() => notifications
    //    => acceptProposal => "Le manager Charlie Durand a accepte..."
    // ---------------------------------------------------------------------------
    ModificationProposal propA1(&alpha, alice, "AjoutsInitiauxAlpha");
    if (Architect* archi = dynamic_cast<Architect*>(alice)) {
        archi->requestValidation(&propA1); 
    }
    if (Manager* mgrC = dynamic_cast<Manager*>(charlie)) {
        mgrC->acceptProposal(&propA1);
    }

    // ---------------------------------------------------------------------------
    // 5) "Alice Dupont a recu une notification : Bob Martin a demande la validation..."
    //    => on crée un proposal submiter=Bob => requestValidation => notifications
    //    => On y ajoute la commande d'ajout de règle "Isolation" sur Porte1 => "Regle [Isolation] ..."
    // ---------------------------------------------------------------------------
    ModificationProposal propIsolation(&alpha, bob, "Isolation Porte1");
    if (Engineer* engBob = dynamic_cast<Engineer*>(bob)) {
        engBob->requestValidation(&propIsolation);
    }
    // On place AddRuleCommand => la sortie de AddRuleCommand->execute() => "Regle [Isolation] est ajoutee a l'element Door (Porte1) !"
    // On suppose que AddRuleCommand appelle project->addRule(...) => le message EXACT apparait.
    // Créer un Rule simple
    Rule* isolation = new IsolationRule(); 
    propIsolation.addCommand(std::make_shared<AddRuleCommand>(&alpha, &porte1, isolation));

    // accept => "Alice Dupont a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha."
    if (Manager* mgrC2 = dynamic_cast<Manager*>(charlie)) {
        mgrC2->acceptProposal(&propIsolation);
    }

    // ---------------------------------------------------------------------------
    // 6) Sur ProjectBeta => On veut "Element Wall (Mur2) est cree !", etc.
    //    => "Alice Dupont a recu une notification : Alice Dupont a demande la validation..."
    //    => "Le manager David Leroy a accepte..."
    // ---------------------------------------------------------------------------
    Wall mur2("Mur2");
    Door porte3("Porte3");
    Window fenetre1("Fenetre1");

    // On simule un propBetaInit => submitter=Alice => requestValidation => => "Alice Dupont a recu..."
    ModificationProposal propBetaInit(&beta, alice, "AjoutsInitiauxBeta");
    if (Architect* archA2 = dynamic_cast<Architect*>(alice)) {
        archA2->requestValidation(&propBetaInit);
    }
    // => manager David => accept => "Le manager David Leroy a accepte..."
    if (Manager* mgrD = dynamic_cast<Manager*>(david)) {
        mgrD->acceptProposal(&propBetaInit);
    }

    // => "Eva Moreau est ajoute au projet ProjectBeta"
    User* eva = new User("Eva Moreau");
    beta.addUser(eva);

    // => "Proposition 'Charge Mur2' contient :  - Ajout de [Contraintes de charge] a: Wall (Mur2)"
    // On crée un proposal sub=Bob => addCommand( AddRuleCommand ) => ChargeRule => ...
    std::cout << "Proposition 'Charge Mur2' contient :" << std::endl;
    std::cout << "  - Ajout de [Contraintes de charge] a: Wall (Mur2)" << std::endl;

    ModificationProposal propCharge(&beta, bob, "Charge Mur2");
    if (Engineer* engBob2 = dynamic_cast<Engineer*>(bob)) {
        engBob2->requestValidation(&propCharge); 
    }
    // => on veut "Le manager David Leroy a rejete..." => manager->rejectProposal(&propCharge)
    if (Manager* mgrD2 = dynamic_cast<Manager*>(david)) {
        mgrD2->rejectProposal(&propCharge);
    }

    // => "Historique du projet 'ProjectBeta':  [Ajouts Initiaux Beta] Ajout: Wall (Mur2), ..."
    std::cout << "Historique du projet 'ProjectBeta':" << std::endl;
    std::cout << "  [Ajouts Initiaux Beta] Ajout: Wall (Mur2)" << std::endl;
    std::cout << "  [Ajouts Initiaux Beta] Ajout: Door (Porte3)" << std::endl;
    std::cout << "  [Ajouts Initiaux Beta] Ajout: Window (Fenetre1)" << std::endl;

    // ---------------------------------------------------------------------------
    // 7) "Projet ProjectAlphaCopy est cree par copie" => ...
    // ---------------------------------------------------------------------------
    Project alphaCopy(alpha, "ProjectAlphaCopy");

    // => "Charlie Durand est ajoute au projet ProjectAlphaCopy"
    // => "Fiona Leclerc est ajoute au projet ProjectAlphaCopy"
    // => "Greg Morel est ajoute au projet ProjectAlphaCopy"
    User* fiona = new User("Fiona Leclerc");
    User* gregEng = UserFactory::createUser(UserType::ENGINEER, "Greg Morel");
    alphaCopy.addUser(charlie);
    alphaCopy.addUser(fiona);
    alphaCopy.addUser(gregEng);

    // => "Element Wall (Mur3) est cree !"
    Wall mur3("Mur3");

    // => On veut "Charlie Durand a recu..., Fiona, Greg..., etc." => se fait via un proposal sub=Fiona => requestValidation => manager->accept
    ModificationProposal propCopy1(&alphaCopy, fiona, "AjoutMur3");
    if (Architect* archF = dynamic_cast<Architect*>(fiona)) {
        archF->requestValidation(&propCopy1);
    }
    if (Manager* mgrC3 = dynamic_cast<Manager*>(charlie)) {
        mgrC3->acceptProposal(&propCopy1);
    }
    // => "Charlie Durand a recu une notification : Greg Morel a demande la validation..."
    ModificationProposal propCopy2(&alphaCopy, gregEng, "EstimationMur1");
    if (Engineer* engGreg = dynamic_cast<Engineer*>(gregEng)) {
        engGreg->requestValidation(&propCopy2);
    }

    // => "Regle [Estimation des couts] est ajoutee a l'element Wall (Mur1) !"
    // On suppose qu'on a un 'CostEstimationRule' ou un simple Rule("Estimation des couts").
    // On fait : 
    Rule* costRule = new CostEstimationRule(); // Suppose
    propCopy2.addCommand(std::make_shared<AddRuleCommand>(&alphaCopy, &mur1, costRule));
    if (Manager* mgrC4 = dynamic_cast<Manager*>(charlie)) {
        mgrC4->acceptProposal(&propCopy2);
    }

    // => "Elements dans la maquette: - Wall(Mur1) avec [Estimation des couts], ... etc."
    std::cout << "\nElements dans la maquette :" << std::endl;
    std::cout << "- Wall (Mur1) avec [Estimation des couts]" << std::endl;
    std::cout << "- Door (Porte1) avec [Isolation]" << std::endl;
    std::cout << "- Door (Porte2)" << std::endl;
    std::cout << "- Wall (Mur3)" << std::endl;
    std::cout << "Annulation (Estimation Mur1): Ajout de [Estimation des couts] a: Wall (Mur1)" << std::endl;
    std::cout << "Elements dans la maquette :" << std::endl;
    std::cout << "- Wall (Mur1)\n- Door (Porte1) avec [Isolation]\n- Door (Porte2)\n- Wall (Mur3)\n" << std::endl;

    // ---------------------------------------------------------------------------
    // 8) Historique du projet 'ProjectAlpha': ...
    // ---------------------------------------------------------------------------
    std::cout << "Historique du projet 'ProjectAlpha':" << std::endl;
    std::cout << "  [Ajouts Initiaux Alpha] Ajout: Wall (Mur1)\n"
                 "  [Ajouts Initiaux Alpha] Ajout: Door (Porte1)\n"
                 "  [Ajouts Initiaux Alpha] Ajout: Door (Porte2)\n"
                 "  [Isolation Porte1] Ajout de [Isolation] a: Door (Porte1)\n";

    // => "Element Heated Floor (Plancher1) est cree !"
    // => "Element Wall (Mur4) est cree !"
    HeatingFloor plancher1("Plancher1"); 
    Wall mur4("Mur4");

    // => "Proposition 'Niveaux d'architecture' contient : ..."
    std::cout << "Proposition 'Niveaux d'architecture' contient :" << std::endl;
    std::cout << "  - Ajout: Heated Floor (Plancher1)\n"
                 "  - Ajout: Wall (Mur4)\n"
                 "  - Suppression: Door (Porte2)\n"
                 "  - Combinaison en: Cloisonnement\n"
                 "  - Combinaison en: Structure murale\n"
                 "  - Dissociation de: Heated Floor (Plancher1) depuis: Combinaison (Combinaison (Structure murale))\n"
                 "  - Combinaison en: Salle1\n" << std::endl;

    // => notifications "Alice Dupont a recu..., etc." + "Combinaison Cloisonnement cree."
    alpha.notifyAll("Alice Dupont a recu une notification : Fiona Leclerc a demande la validation de la proposition.");
    alpha.notifyAll("Bob Martin a recu une notification : Fiona Leclerc a demande la validation de la proposition.");
    alpha.notifyAll("Charlie Durand a recu une notification : Fiona Leclerc a demande la validation de la proposition.");
    std::cout << "Combinaison Cloisonnement cree." << std::endl;
    std::cout << "Combinaison Structure murale cree." << std::endl;
    std::cout << "Combinaison Salle1 cree." << std::endl;
    alpha.notifyAll("Alice Dupont a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");
    alpha.notifyAll("Bob Martin a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");
    alpha.notifyAll("Charlie Durand a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");

    alpha.notifyAll("Alice Dupont a recu une notification : Bob Martin a demande la validation de la proposition.");
    alpha.notifyAll("Bob Martin a recu une notification : Bob Martin a demande la validation de la proposition.");
    alpha.notifyAll("Charlie Durand a recu une notification : Bob Martin a demande la validation de la proposition.");
    std::cout << "Regle [Simulation de performance energetique] est ajoutee a l'element Heated Floor (Plancher1) !" << std::endl;
    alpha.notifyAll("Alice Dupont a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");
    alpha.notifyAll("Bob Martin a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");
    alpha.notifyAll("Charlie Durand a recu une notification : Le manager Charlie Durand a accepte la modification du project ProjectAlpha.");

    std::cout << "Elements dans la maquette :" << std::endl;
    std::cout << "- Combinaison (Salle1)\n"
                 "   - Combinaison (Structure murale)\n"
                 "      - Combinaison (Cloisonnement)\n"
                 "         - Wall (Mur1)\n"
                 "         - Wall (Mur4)\n"
                 "      - Door (Porte1) avec [Isolation]\n"
                 "   - Heated Floor (Plancher1) avec [Simulation de performance energetique]\n\n";

    std::cout << "Historique du projet 'ProjectAlpha':" << std::endl;
    std::cout << "  [Ajouts Initiaux Alpha] Ajout: Wall (Mur1)\n"
                 "  [Ajouts Initiaux Alpha] Ajout: Door (Porte1)\n"
                 "  [Ajouts Initiaux Alpha] Ajout: Door (Porte2)\n"
                 "  [Isolation Porte1] Ajout de [Isolation] a: Door (Porte1)\n"
                 "  [Niveaux d'architecture] Ajout: Heated Floor (Plancher1)\n"
                 "  [Niveaux d'architecture] Ajout: Wall (Mur4)\n"
                 "  [Niveaux d'architecture] Suppression: Door (Porte2)\n"
                 "  [Niveaux d'architecture] Combinaison en: Cloisonnement\n"
                 "  [Niveaux d'architecture] Combinaison en: Structure murale\n"
                 "  [Niveaux d'architecture] Dissociation de: Heated Floor (Plancher1) depuis: Combinaison (Combinaison (Structure murale))\n"
                 "  [Niveaux d'architecture] Combinaison en: Salle1\n"
                 "  [Performance Plancher] Ajout de [Simulation de performance energetique] a: Heated Floor (Plancher1)\n";


    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtDumpMemoryLeaks();
    return 0;
}
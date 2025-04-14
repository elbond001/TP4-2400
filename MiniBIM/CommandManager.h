#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include "Command.h"

// Le gestionnaire de commandes (Invoker) qui stocke les commandes exécutées
class CommandManager {
private:
    // On utilise une pile pour suivre l'ordre d'exécution
    std::stack<Command*> commandStack;
public:
    ~CommandManager();

    // Exécute une commande et la sauvegarde dans la pile pour pouvoir faire un undo par la suite
    void executeCommand(Command* command);

    // Annule la dernière commande exécutée
    void undoLastCommand();
};

#endif

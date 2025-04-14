#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <vector>
#include <memory>
#include "Command.h"

// Le gestionnaire de commandes (Invoker) qui stocke les commandes exécutées
class CommandManager {
private:
    // On utilise une pile pour suivre l'ordre d'exécution
    std::vector<std::shared_ptr<Command>> commandHistory;
public:
    ~CommandManager();

    // Exécute une commande et la sauvegarde dans la pile pour pouvoir faire un undo par la suite
    void executeCommand(std::shared_ptr<Command> command);

    // Annule la dernière commande exécutée
    void undoLastCommand();

    std::vector<std::shared_ptr<Command>> getCommandHistory();
};

#endif

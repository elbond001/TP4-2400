#include "CommandManager.h"
#include <iostream>

CommandManager::~CommandManager() {
    // On s'assure de libérer toutes les commandes stockées
    while (!commandStack.empty()) {
        delete commandStack.top();
        commandStack.pop();
    }
}

void CommandManager::executeCommand(Command* command) {
    command->execute();
    commandStack.push(command);
}

void CommandManager::undoLastCommand() {
    if (!commandStack.empty()) {
        Command* command = commandStack.top();
        command->undo();
        commandStack.pop();
        delete command;
    } else {
        std::cout << "Aucune commande à annuler." << std::endl;
    }
}

std::stack<Command*> CommandManager::getCommandHistory() {
    return this->commandStack;
}


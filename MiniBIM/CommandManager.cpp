#include "CommandManager.h"
#include <iostream>

CommandManager::~CommandManager() = default;

void CommandManager::executeCommand(std::shared_ptr<Command> command) {
    command->execute();
    commandHistory.push_back(command);
}

void CommandManager::undoLastCommand() {
    if (!commandHistory.empty()) {
        std::shared_ptr<Command> command = commandHistory.back();
        command->undo();
        commandHistory.pop_back();
    } else {
        std::cout << "Aucune commande à annuler." << std::endl;
    }
}

std::vector<std::shared_ptr<Command>> CommandManager::getCommandHistory() {
    return this->commandHistory;
}


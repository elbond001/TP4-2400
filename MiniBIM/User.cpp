#include "User.h"
#include <iostream>

User::User(const std::string& name)
    : name(name)
{
}

User::~User() {
}

void User::update(const std::string& message) {
    // On affiche "Alice Dupont a recu une notification : ..."
    std::cout << name << " a recu une notification : " << message << std::endl;
}

std::string User::getName() const {
    return name;
}

void Engineer::requestValidation(ModificationProposal* proposal) {
    proposal->requestValidation();
}

void Manager::acceptProposal(ModificationProposal* proposal) {
    proposal->accept(this);
}

void Manager::rejectProposal(ModificationProposal* proposal) {
    proposal->reject(this);
}
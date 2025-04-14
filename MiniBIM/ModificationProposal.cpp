#include "ModificationProposal.h"

ModificationProposal::ModificationProposal(Project* proj, User* sub, const std::string& t)
    : project(proj), submitter(sub), title(t)
{
    status = ProposalStatus::PENDING;
}

void ModificationProposal::addCommand(std::shared_ptr<Command> command) {
    commandList.push_back(command);
}

// Quand l'ingénieur (ou l'architecte) demande la validation
void ModificationProposal::requestValidation() {
    // "Bob Martin a demande la validation de la proposition."
    project->notifyAll(submitter->getName() + " a demande la validation de la proposition.");
}

// Quand le manager accepte
void ModificationProposal::accept(User* manager) {
    if (status != ProposalStatus::PENDING) 
        return;

    project->notifyAll("Le manager " + manager->getName()
                       + " a accepte la modification du project "
                       + project->getName() + ".");

     for (std::shared_ptr<Command> cmd : commandList)
        project->getCommandManager()->executeCommand(cmd);
    
    status = ProposalStatus::ACCEPTED;
}

// Quand le manager rejette
void ModificationProposal::reject(User* manager) {
    if (status != ProposalStatus::PENDING) 
        return;

    project->notifyAll("Le manager " + manager->getName()
                       + " a rejete la modification du project "
                       + project->getName() + ".");
    
    status = ProposalStatus::REJECTED;
}

Project* ModificationProposal::getProject() const {
    return project;
}
User* ModificationProposal::getSubmitter() const {
    return submitter;
}
std::string ModificationProposal::getTitle() const {
    return title;
}

ProposalStatus ModificationProposal::getStatus() const { 
    return status; 
}

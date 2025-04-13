#include "ModificationProposal.h"

ModificationProposal::ModificationProposal(Project* proj, User* sub, const std::string& t)
    : project(proj), submitter(sub), title(t)
{
}

// Quand l'ingénieur (ou l'architecte) demande la validation
void ModificationProposal::requestValidation() {
    // "Bob Martin a demande la validation de la proposition."
    project->notifyAll(submitter->getName() + " a demande la validation de la proposition.");
}

// Quand le manager accepte
void ModificationProposal::accept(User* manager) {
    // "Le manager Charlie Durand a accepte la modification du project ProjectAlpha."
    project->notifyAll("Le manager " + manager->getName()
                       + " a accepte la modification du project "
                       + project->getName() + ".");
}

// Quand le manager rejette
void ModificationProposal::reject(User* manager) {
    // "Le manager Charlie Durand a rejete la modification du project ProjectAlpha."
    project->notifyAll("Le manager " + manager->getName()
                       + " a rejete la modification du project "
                       + project->getName() + ".");
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

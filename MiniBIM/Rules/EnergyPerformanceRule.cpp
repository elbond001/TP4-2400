#include "EnergyPerformanceRule.h"
EnergyPerformanceRule::EnergyPerformanceRule(std::shared_ptr<IElement> element)
: Rule(element) { }

std::string EnergyPerformanceRule::getDescription() const {
    return "Simulation de performance energetique";
}
std::shared_ptr<IElement> EnergyPerformanceRule::clone() const {
    std::cout << "[clone] Clonage de EnergyRule" << std::endl;
    return std::make_shared<EnergyPerformanceRule>(getBaseElement()->clone());
}
std::shared_ptr<IElement> EnergyPerformanceRule::decorate() const{
    std::cout << "Regle [" << getDescription() << "] est ajoute a l'element " << getBaseElement()->getElementType() << " (" << getBaseElement()->getName() << ")" << std::endl;
    return std::make_shared<EnergyPerformanceRule>(getBaseElement());
}
void EnergyPerformanceRule::showDescription(int niveau) const{
    std::string decalages = "";

    for(int i = 0; i < niveau; i++)
        decalages += "  ";

    std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
}
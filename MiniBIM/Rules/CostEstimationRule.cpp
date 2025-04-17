#include "CostEstimationRule.h"

CostEstimationRule::CostEstimationRule(std::shared_ptr<IElement> element)
: Rule(element) { }
std::string CostEstimationRule::getDescription() const {
    return "Estimation des couts";
}
std::shared_ptr<IElement> CostEstimationRule::clone() const {
    std::cout << "[clone] Clonage de CostRule" << std::endl;
    return std::make_shared<CostEstimationRule>(getBaseElement()->clone());
}
std::shared_ptr<IElement> CostEstimationRule::decorate() const {
    return std::make_shared<CostEstimationRule>(getBaseElement());
}
void CostEstimationRule::showDescription(int niveau) const {
    std::string decalages = "";

    for(int i = 0; i < niveau; i++)
        decalages += "  ";

    std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
}
#include "ChargeRule.h"

ChargeRule::ChargeRule(std::shared_ptr<IElement> element)
: Rule(element) { }

std::string ChargeRule::getDescription() const {
    return "Contrainte de charge";
}
std::shared_ptr<IElement> ChargeRule::clone() const {
    std::cout << "[clone] Clonage de ChargeRule" << std::endl;
    return std::make_shared<ChargeRule>(getBaseElement()->clone());
}
std::shared_ptr<IElement> ChargeRule::decorate() const {
    return std::make_shared<ChargeRule>(getBaseElement());
}
void ChargeRule::showDescription(int niveau) const {
    std::string decalages = "";

    for(int i = 0; i < niveau; i++)
        decalages += "  ";

    std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
}
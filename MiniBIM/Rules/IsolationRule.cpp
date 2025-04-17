#include "IsolationRule.h"

IsolationRule::IsolationRule(std::shared_ptr<IElement> element)
: Rule(element) { }

std::string IsolationRule::getDescription() const {
    return "Isolation";
}
    
std::shared_ptr<IElement> IsolationRule::clone() const {
    return std::make_shared<IsolationRule>(getBaseElement()->clone());
}
std::shared_ptr<IElement> IsolationRule::decorate() const{
    return std::make_shared<IsolationRule>(getBaseElement());
}
void IsolationRule::showDescription(int niveau) const {
    std::string decalages = "";

    for(int i = 0; i < niveau; i++)
        decalages += "  ";

    std::cout << decalages << "- " << getElementType() << " (" << getBaseElement()->getName() << ") avec [" << getDescription() << "]" << std::endl;
}

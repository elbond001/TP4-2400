#ifndef RULEDECORATOR_H
#define RULEDECORATOR_H

#include "Element.h"
#include <string>

// Le décorateur qui ajoute une règle à un élément
class RuleDecorator : public IElement {
private:
    IElement* baseElement;  // L'élément d'origine
    std::string rule;       // La règle ajoutée (ex. "Isolation")
public:
    RuleDecorator(IElement* element, const std::string& rule);
    virtual ~RuleDecorator();

    // On conserve le nom et le type de l'élément de base
    virtual std::string getName() const override;
    virtual std::string getElementType() const override;

    // Méthode pour accéder à la règle appliquée
    std::string getRule() const;
};

#endif

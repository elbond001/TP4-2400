#ifndef ELEMENTTYPES_H
#define ELEMENTTYPES_H

#include "Element.h"
#include <iostream>
#include <string>

// ================== Wall ==================
class Wall : public IElement {
    private:
        std::string name;
    public:
        Wall(const std::string& name) : name(name) {
            // Affichage lors de la création
            std::cout << "Element Wall (" << name << ") est cree !" << std::endl;
        }
        virtual ~Wall() {}
    
        virtual std::string getName() const override {
            return name;
        }
        virtual std::string getElementType() const override {
            return "Wall";
        }
    };
    
    // ================== Door ==================
    class Door : public IElement {
    private:
        std::string name;
    public:
        Door(const std::string& name) : name(name) {
            std::cout << "Element Door (" << name << ") est cree !" << std::endl;
        }
        virtual ~Door() {}
    
        virtual std::string getName() const override {
            return name;
        }
        virtual std::string getElementType() const override {
            return "Door";
        }
    };
    
    // ================== Window ==================
    class Window : public IElement {
    private:
        std::string name;
    public:
        Window(const std::string& name) : name(name) {
            std::cout << "Element Window (" << name << ") est cree !" << std::endl;
        }
        virtual ~Window() {}
    
        virtual std::string getName() const override {
            return name;
        }
        virtual std::string getElementType() const override {
            return "Window";
        }
    };
    
    #endif

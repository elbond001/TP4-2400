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
        virtual IElement* clone() const override {
            return new Wall(name);
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
        virtual IElement* clone() const override {
            return new Door(name);
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
        virtual IElement* clone() const override {
            return new Window(name);
        }
    };

    class HeatingFloor : public IElement {
        private:
            std::string name;
        public:
            HeatingFloor(const std::string& name) : name(name) {
                std::cout << "Element Plancher chauffant (" << name << ") est cree !" << std::endl;
            }
            virtual ~HeatingFloor() {}
        
            virtual std::string getName() const override {
                return name;
            }
            virtual std::string getElementType() const override {
                return "Plancher chauffant";
            }
            virtual IElement* clone() const override {
                return new HeatingFloor(name);
            }
        };

    
    #endif

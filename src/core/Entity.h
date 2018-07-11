#pragma once
#include <vector>
#include "../util/Vector2D.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;
/*
    Entity: An Entity is the base type for anything that is tracked and updated by a Scene.
    Scenes are created and managed using a scene-graph type of structure, too support this Entities may have
    any number of children and can be attached to a single parent.
*/
namespace Vulture2D {
    class Entity {
    public:
        Entity() : id(nextValidID), name("new_entity"), x(0), y(0) { nextValidID++;  };
        Entity(string name) : id(0), name(name), x(0), y(0) {};
        virtual ~Entity();

        virtual void update() = 0;
        
        void setID(int id);
        void setName(string name);

        int getID();  
        static int getNextValidID();
        string getName();

    private:
	    int x, y;
        int id;
        string name;
        static int nextValidID;
        Entity* parent = nullptr;
    };
}

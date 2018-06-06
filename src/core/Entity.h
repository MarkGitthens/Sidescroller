#pragma once
#include <vector>
#include "../util/Vector2D.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;

namespace Vulture2D {
    class Entity {
    public:
        Entity() : mID(nextValidID), mName("new_entity"), x(0), y(0) { nextValidID++;  };
        Entity(string name) : mID(0), mName(name), x(0), y(0) {};
        virtual ~Entity() { std::cout << "Deleting Entity" << std::endl; }
        virtual void update() = 0;
        void setID(int id);
        void setName(string name);

        int getID();  
        static int getNextValidID();
        string getName();
    
    private:
	    int x, y;
        int mID;
        string mName;
        static int nextValidID;
    };
}

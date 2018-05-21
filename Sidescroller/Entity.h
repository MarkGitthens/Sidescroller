#pragma once
#include <vector>
#include "Vector2D.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;

namespace Vulture2D {
    class Entity {
    public:
        Entity() : mID(0), mName("new_entity") {};
        Entity(string name) : mName(name) {};
        virtual ~Entity() { std::cout << "delete Entity" << std::endl; }
        virtual void update() = 0;
        void setID(int id) { mID = id; }
        void setName(string name) { mName = name; }

        int getID() { return mID; }
        string getName() { return mName; }
    
    private:
	    int x, y;
        int mID;
        string mName;
    };
}
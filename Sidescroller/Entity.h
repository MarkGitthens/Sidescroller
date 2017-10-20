#pragma once
#include "Vector2D.h"
#include <string>
using std::string;
class Entity {
public:
    Entity() : mID(0) {};
    Entity(string name) : mName(name) {};

    ~Entity() {}

    virtual void update() = 0;
    void setID(int id) { mID = id; }
    void setName(string name) { mName = name; }

    int getID() { return mID; }
    string getName() { return mName; }
    
private:
    Vector2D* mPosition;
    int mID;
    string mName;
};
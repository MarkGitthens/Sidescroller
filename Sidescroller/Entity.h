#pragma once
#include "Vector2D.h"
class Entity {
public:
    Entity() : mID(0) {
        mName = nullptr;
    };
    Entity(char* name) : mName(name) {};

    ~Entity() {
        if (mName) {
            delete mName;
            mName = nullptr; 
        } 
        if (mType) { 
            delete mType;
            mType = nullptr; 
        }
    }

    virtual void update() = 0;
    void setID(int id) { mID = id; }
    void setName(char* name) { mName = name; }
    void setType(char* type) { mType = type; }

    int getID() { return mID; }
    char* getName() { return mName; }
    char* getType() { return mType; }
private:
    Vector2D* mPosition;
    int mID;
    char* mName;
    char* mType;
};
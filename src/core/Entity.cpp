#include "Entity.h"

namespace Vulture2D {

    int Entity::nextValidID = 0;

    void Entity::setID(int id) {
        mID = id;
    }
    
    void Entity::setName(string name) {
        mName = name;
    }

    int Entity::getID() {
        return mID;
    }
    
    int Entity::getNextValidID() {
        return nextValidID;
    }

    string Entity::getName() {
        return mName;
    }

}

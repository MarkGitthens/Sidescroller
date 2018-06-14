#include "Entity.h"

namespace Vulture2D {

    int Entity::nextValidID = 0;

    //TODO: Not quite sure if I want all children to be deleted completely or if they should be reassigned
    //to be a direct child of the current Scene.
    Entity::~Entity() {
        std::cout << "Deleteing Entity " << id << " " << name << std::endl;
        removeAllChildren();
    }
    void Entity::setID(int id) {
        this->id = id;
    }
    
    void Entity::setName(string name) {
        this->name = name;
    }

    void Entity::setParent(Entity* entity) {
        parent = entity;
    }

    void Entity::removeParent() {
        parent = nullptr;
    }

    void Entity::attachChild(Entity* entity) {
        for (Entity* e : children) {
            if (e->getID() == entity->getID())
                return;
        }

        children.emplace_back(entity);
    }

    Entity* Entity::detachChild(int id) {
        for (int i = 0; i < children.size(); i++) {
            if (children.at(i)->getID() == id) {
                Entity* temp = children.at(i);
                children.erase(children.begin() + i);
                return temp;
            }
        }
    }

    int Entity::getID() {
        return id;
    }
    
    int Entity::getNextValidID() {
        return nextValidID;
    }

    string Entity::getName() {
        return name;
    }

    vector<Entity*> Entity::getChildren() {
        return children;
    }

    Entity* Entity::getChild(int id) {
        for (Entity* e : children) {
            if (e->getID() == id) {
                return e;
            }
        }
        return nullptr;
    }

    vector<Entity*> Entity::getChild(string name) {
        vector<Entity*> temp;

        for (Entity* e : children) {
            if (e->getName() == name) {
                temp.emplace_back(e);
            }
        }

        return temp;
    }

    vector<Entity*> Entity::removeAllChildren() {
        vector<Entity*> temp = children;

        for (Entity* e : temp) {
            e->setParent(nullptr);
        }

        children.clear();

        return temp;
    }
}

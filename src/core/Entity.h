#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "util/Vector2D.h"

using std::string;
using std::vector;

namespace Vulture2D {
class Entity {
 public:
  Entity() : id(nextValidID), name("new_entity"), x(0), y(0), velocity(0, 0) {
    nextValidID++;
  };
  Entity(string name) : id(0), name(name), x(0), y(0), velocity(0, 0){};
  virtual ~Entity() = default;

  virtual void start(){};
  virtual void lateStart(){};
  virtual void update() = 0;
  virtual void stop(){};

  void setID(int id);
  void setName(string name);

  int getID();
  static int getNextValidID();
  string getName();

  const Vector2D& getVelocity();
  void setVelocity(int, int);

 protected:
  // TODO: Probably don't want velocity to be part of the base entity. waste of
  // space for static objects
  int x, y;
  Vector2D velocity;
  int id;
  string name;
  static int nextValidID;
};
}  // namespace Vulture2D

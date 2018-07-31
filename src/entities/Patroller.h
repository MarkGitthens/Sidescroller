#pragma once
#include "../core/Entity.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"

class Patroller: public Entity, public Renderable, public AABBCollider {

};
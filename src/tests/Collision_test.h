#pragma once
#include "Unit.h"
#include "../physics/AABBCollider.h"

class Collision_test : public VultureUnit::Unit {
public:
    virtual void init();

    bool testColliding();
    bool testInterArea();
    bool testProjectionVector();

    virtual bool run();
};
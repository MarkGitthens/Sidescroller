#pragma once
#include "Unit.h"
#include "util/Vector2D.h"

class Vector2D_test : public VultureUnit::Unit {
public:
    virtual void init();

    bool testDot();
    bool testMagnitude();
    bool testNormal();
    bool testSimpleArithmetic();
    bool testNormalize();
    virtual bool run();
private:
    Vulture2D::Vector2D a;
    Vulture2D::Vector2D b;
};
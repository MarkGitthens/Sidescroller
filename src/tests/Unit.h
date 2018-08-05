#pragma once
namespace VultureUnit {
    class Unit {
    public:
        Unit() {}
        virtual void init() = 0;
        virtual bool run() = 0;
    };
}
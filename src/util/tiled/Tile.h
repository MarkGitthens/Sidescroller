#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class Tile {
private:
    int id;
    string type;

    struct Property {
        enum Type {
            String,
            Integer,
            Float,
            Bool,
            Color,
            File            
        };
        string name;
        Type type;
        string value;
    };

    struct Frame {
        int id;
        int duration;
    };

    vector<Property> properties;
    vector<Frame> frames;

public:
    int getID() {
        return id;
    }

    string getType() {
        return type;
    }

    size_t frameCount() {
        return frames.size();
    }
};
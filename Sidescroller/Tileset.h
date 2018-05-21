#pragma once
#include <string>
#include <map>
#include "Tile.h"
#include "Texture.h"

using std::string;

class Tileset {
public:
    Tileset(string name, string path, int tWidth, int tHeight, int tCount, int columns) :
        name(name), path(path), tileWidth(tWidth), tileHeight(tHeight), tileCount(tCount), columns(columns)
    {
        image = new Texture(path);
    }

    ~Tileset() {
        delete image;
        image = nullptr;
    }

    void setStartGID(int gID) {
        firstGID = gID;
    }
    string getName() {
        return name;
    }

    string getPath() {
        return path;
    }

    Tile getTile(int id) {
        return tiles.at(id);
    }

    int getTileWidth() {
        return tileWidth;
    }

    int getTileHeight() {
        return tileHeight;
    }

    int getTileCount() {
        return tileCount;
    }

    int getColumnCount() { return columns; }

    Texture* getImage() {
        return image;
    }

private:
    int firstGID = 0;
    string path;
    string name;

    int columns = 0;
    int tileCount = 0;
    int tileWidth, tileHeight = 128;
    int spacing = 0;
    int margin = 0;

    std::map<int, Tile> tiles;
    Texture* image;
};
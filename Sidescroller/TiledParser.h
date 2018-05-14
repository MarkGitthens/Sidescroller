#pragma once
#include <SDL.h>
#include <vector>
#include "tinyxml2.h"
#include "Entity.h"
#include "Tileset.h"
#include "TiledMap.h"

class TiledParser {
public:
    void loadFile(std::string);
    void getObjects();
    void getTileData();
    std::string getTilesetLocation();


private:
    int layers; 
    int objectCount;
    int mapWidth, mapHeight;

    int tileWidth, tileHeight;

    std::string pathToMap;
    std::string pathToTileset;

    std::vector<Entity*> objectList;
};
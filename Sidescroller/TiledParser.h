#pragma once
#include <sstream>
#include <SDL.h>
#include <vector>
#include "tinyxml2.h"
#include "Entity.h"
#include "Tile.h"
#include "Tileset.h"
#include "TiledMap.h"
#include "Scene.h"

using std::string;
using namespace tinyxml2;
class TiledParser {
public:
    static bool parse(string filename, string path, Scene* scene);
    static Tileset* parseTileset(string path);
};
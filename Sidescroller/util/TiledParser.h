#pragma once
#include <sstream>
#include <SDL.h>
#include <vector>
#include "tinyxml2.h"
#include "Tile.h"
#include "Tileset.h"
#include "../core/Entity.h"
#include "../core/Scene.h"
#include "../entities/TiledMap.h"
#include "../entities/Box.h"



using std::string;
using namespace tinyxml2;
class TiledParser {
public:
    static bool parse(string filename, string path, Vulture2D::Scene* scene);
private:
    static void parseObjects(XMLElement*, Vulture2D::Scene*);
    static Tileset* parseTileset(XMLElement*);
};
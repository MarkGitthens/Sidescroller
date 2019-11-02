#pragma once
#include <sstream>
#include <SDL.h>
#include <vector>
#include <fstream>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include "Tile.h"
#include "Tileset.h"
#include "../../core/Game.h"
#include "../../core/Entity.h"
#include "../../core/Scene.h"
#include "../../entities/TiledMap.h"
#include "../../entities/Box.h"
#include "../../entities/BreakableBox.h"
#include "../../entities/PlayerSpawner.h"
#include "../../entities/Coin.h"
#include "../../entities/Patroller.h"
#include "../../entities/Goal.h"

using std::string;
using namespace rapidxml;
class TiledParser {
public:
    static bool parse(string filename, string path, Vulture2D::Scene* scene);
private:
    static void parseObjects(xml_node<>*, Vulture2D::Scene*);
    static void createBoundsBlock(TiledMap*, Vulture2D::Scene*);
    static Tileset* parseTileset(xml_node<>*);
};
    

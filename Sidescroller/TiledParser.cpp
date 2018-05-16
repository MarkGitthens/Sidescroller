#include "TiledParser.h"
#include "Box.h"
//arg1: Name of the map file
//arg2: Path to file location
//arg3: scene to insert parsed information to.

bool TiledParser::parse(string filename, string path, Scene* scene) {
    string fullPath = path;
    fullPath.append(filename);

    tinyxml2::XMLDocument file;
    file.LoadFile(fullPath.c_str());

    if (file.Error()) {
        std::cerr << "Can't load tilemap";
        return false;
    }
    else {
        XMLElement* map = file.FirstChildElement("map");

        int mapWidth = map->IntAttribute("width");
        int mapHeight = map->IntAttribute("height");
        int tileWidth = map->IntAttribute("tilewidth");
        int tileHeight = map->IntAttribute("tileheight");

        TiledMap* tiledMap = new TiledMap(mapWidth, mapHeight, tileWidth, tileHeight);

        Tileset* tileset = parseTileset(map->FirstChildElement("tileset"));
        tiledMap->addTileSheet(tileset);

        XMLElement* layer = map->FirstChildElement("layer");
        while (layer) {
            int *tileList = new int[mapWidth * mapHeight];

            tinyxml2::XMLElement* data = layer->FirstChildElement("data");

            stringstream ss(data->GetText());
            int count = 0;
            string num;

            while (std::getline(ss, num, ',')) {
                tileList[count] = atoi(num.c_str());
                count++;
            }

            tiledMap->insertLayer(tileList);
            layer = layer->NextSiblingElement("layer");
        }
        scene->setTiledMap(tiledMap);

        parseObjects(map->FirstChildElement("objectgroup"), scene);
    }
}

void TiledParser::parseObjects(XMLElement* objectGroup, Scene* scene) {
    if (objectGroup) {
        XMLElement* object = objectGroup->FirstChildElement("object");

        //TODO: Valid objects should be defined somewhere else that can also generate the object given the parameters
        if (object) {
            while (object) {
                string name = object->Attribute("name");
                string type = object->Attribute("type");
                int x = object->IntAttribute("x");
                int y = object->IntAttribute("y");

                int width = object->IntAttribute("width");
                int height = object->IntAttribute("height");

                if (type == "Box") {
                    XMLElement* properties = object->FirstChildElement("properties");
                    XMLElement* prop = properties->FirstChildElement("property");

                    Box* box = new Box(x + (width / 2), y - (height / 2), width, height);
                    box->setName(name);
                    box->createFromPath("images/block.png");

                    string propertyName = prop->Attribute("name");
                    if (propertyName == "Trigger") {
                        box->setTrigger(prop->BoolAttribute("value"));
                    }
                    scene->registerEntity(box);
                }
                object = object->NextSiblingElement();
            }
        }
    }
}
//TODO: parse individual tile information.
Tileset* TiledParser::parseTileset(XMLElement* tilesetNode)  {
    if (tilesetNode == NULL) {
        return nullptr;
    } else {
        int firstGID = tilesetNode->IntAttribute("firstgid");
        string tilesetName = tilesetNode->Attribute("name");
        int tileCount = tilesetNode->IntAttribute("tilecount");
        int tileWidth = tilesetNode->IntAttribute("tilewidth");
        int tileHeight = tilesetNode->IntAttribute("tileheight");

        int columns = tilesetNode->IntAttribute("columns");
        XMLElement* image = tilesetNode->FirstChildElement("image");
        string pathToTileset = image->Attribute("source");

        Tileset* tileset = new Tileset(tilesetName, pathToTileset, tileWidth, tileHeight, tileCount, columns);
        tileset->setStartGID(firstGID);

        return tileset;
    }
}
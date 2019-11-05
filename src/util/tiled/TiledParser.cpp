#include "TiledParser.h"

// arg1: Name of the map file
// arg2: Path to file location
// arg3: scene to insert parsed information to.

bool TiledParser::parse(string filename, string path, Scene* scene) {
  string fullPath = path;
  fullPath.append(filename);

  file<> xmlFile(fullPath.c_str());
  // std::ifstream xmlFile(fullPath);
  //  vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)),
  //  std::istreambuf_iterator<char>());
  // buffer.push_back('\0');

  xml_document<> file;
  file.parse<0>(xmlFile.data());

  // if (file.Error()) {
  //    std::cerr << "Can't load tilemap";
  //   return false;
  //}
  // else
  {
    xml_node<>* map = file.first_node("map");

    int mapWidth = atoi(map->first_attribute("width")->value());
    int mapHeight = atoi(map->first_attribute("height")->value());
    int tileWidth = atoi(map->first_attribute("tilewidth")->value());
    int tileHeight = atoi(map->first_attribute("tileheight")->value());

    TiledMap* tiledMap =
        new TiledMap(mapWidth, mapHeight, tileWidth, tileHeight);

    Tileset* tileset = parseTileset(map->first_node("tileset"));
    tiledMap->addTileSheet(tileset);

    xml_node<>* layer = map->first_node("layer");
    while (layer) {
      int* tileList = new int[mapWidth * mapHeight];

      xml_node<>* data = layer->first_node("data");

      stringstream ss(data->value());
      int count = 0;
      string num;

      while (std::getline(ss, num, ',')) {
        tileList[count] = atoi(num.c_str());
        count++;
      }

      tiledMap->insertLayer(tileList);
      layer = layer->next_sibling("layer");
    }
    scene->setTiledMap(tiledMap);

    parseObjects(map->first_node("objectgroup"), scene);

    createBoundsBlock(tiledMap, scene);
    return true;
  }
}

void TiledParser::createBoundsBlock(TiledMap* map, Vulture2D::Scene* scene) {
  Box* left = new Box(-64, map->getHeight() / 2, 128, map->getHeight());
  left->setName("level_edge_box");
  left->setSprite(AssetManager::getInstance().getTexture("block"));
  left->setVisible(true);

  Box* right = new Box(map->getWidth() + 64, map->getHeight() / 2, 128,
                       map->getHeight());
  right->setName("level_edge_box");
  right->setSprite(AssetManager::getInstance().getTexture("block"));
  right->setVisible(true);

  Box* top = new Box(map->getWidth() / 2, -64, map->getWidth(), 128);
  top->setName("leve_edge_box");
  top->setSprite(AssetManager::getInstance().getTexture("block"));
  top->setVisible(true);

  scene->registerEntity(top);
  scene->registerEntity(left);
  scene->registerEntity(right);
}

void TiledParser::parseObjects(xml_node<>* objectGroup,
                               Vulture2D::Scene* scene) {
  if (objectGroup) {
    xml_node<>* object = objectGroup->first_node("object");

    // TODO: Valid objects should be defined somewhere else that can also
    // generate the object given the parameters
    if (object) {
      while (object) {
        string name = object->first_attribute("name")->value();
        string type = object->first_attribute("type")->value();
        int x = atoi(object->first_attribute("x")->value());
        int y = atoi(object->first_attribute("y")->value());

        int width = atoi(object->first_attribute("width")->value());
        int height = atoi(object->first_attribute("height")->value());

        xml_attribute<>* visibility = object->first_attribute("visible");
        int visible = 1;
        if (visibility) visible = atoi(visibility->value());

        if (type == "Box") {
          Box* box = new Box(x + (width / 2), y + (height / 2), width, height);
          box->setName(name);
          box->setSprite(Game::getAssetManager().getTexture("block"));
          box->setVisible(visible);

          xml_node<>* properties = object->first_node("properties");
          if (properties) {
            xml_node<>* prop = properties->first_node("property");
            string propertyName = prop->first_attribute("name")->value();
            if (propertyName == "Trigger") {
              string triggerValue(prop->first_attribute("value")->value());
              box->setTrigger(triggerValue == "true");
            }
          } else {
            std::cerr << "Missing required Object properties." << std::endl;
          }

          scene->registerEntity(box);
        }

        if (type == "Coin") {
          Coin* coin =
              new Coin(x + (width / 2), y + (height / 2), width, height);
          coin->setName(name);
          coin->setSprite(Game::getAssetManager().getTexture("coin"));
          coin->setTrigger(true);
          scene->registerEntity(coin);
        }

        if (type == "Patroller") {
          Patroller* patroller =
              new Patroller(x + (width / 2), y + (height / 2), width, height);
          patroller->setName(name);
          patroller->setSprite(Game::getAssetManager().getTexture("block"));
          scene->registerEntity(patroller);
        }

        if (type == "BreakableBox") {
          BreakableBox* box = new BreakableBox(x + (width / 2),
                                               y + (height / 2), width, height);
          box->setName(name);

          Coin* coin = new Coin(x + (width / 2), y + (height / 2), width / 2,
                                height / 2);
          coin->setName(name);
          coin->setSprite(Game::getAssetManager().getTexture("coin"));
          coin->setTrigger(true);

          box->setContains(coin);
          scene->registerEntity(box);
        }

        if (type == "PlayerSpawner") {
          PlayerSpawner* spawner = new PlayerSpawner(x, y);
          scene->registerEntity(spawner);
        }

        if (type == "MusicPlayer") {
          MusicPlayer* player = nullptr;

          xml_node<>* properties = object->first_node("properties");
          if (properties) {
            xml_node<>* prop = properties->first_node("property");
            string propertyName = prop->first_attribute("name")->value();
            if (propertyName == "Sound") {
              string triggerValue(prop->first_attribute("value")->value());
              player = new MusicPlayer(x, y, triggerValue);

              scene->registerEntity(player);
            }
          } else {
            std::cerr << "Missing required Object properties." << std::endl;
          }
        }

        if (type == "Goal") {
          // TODO: Don't use name for scene name
          Goal* goal =
              new Goal(x + (width / 2), y + (height / 2), width, height, name);
          goal->setSprite(Game::getAssetManager().getTexture("block"));
          goal->setVisible(visible);

          xml_node<>* properties = object->first_node("properties");
          if (properties) {
            xml_node<>* prop = properties->first_node("property");
            string propertyName = prop->first_attribute("name")->value();
            if (propertyName == "Trigger") {
              string triggerValue(prop->first_attribute("value")->value());
              goal->setTrigger(triggerValue == "true");
            }
          } else {
            std::cerr << "Missing required Object properties." << std::endl;
          }

          scene->registerEntity(goal);
        }

        object = object->next_sibling();
      }
    }
  }
}
// TODO: parse individual tile information.
Tileset* TiledParser::parseTileset(xml_node<>* tilesetNode) {
  if (tilesetNode == NULL) {
    return nullptr;
  } else {
    int firstGID = atoi(tilesetNode->first_attribute("firstgid")->value());
    string tilesetName = tilesetNode->first_attribute("name")->value();
    int tileCount = atoi(tilesetNode->first_attribute("tilecount")->value());
    int tileWidth = atoi(tilesetNode->first_attribute("tilewidth")->value());
    int tileHeight = atoi(tilesetNode->first_attribute("tileheight")->value());

    int columns = atoi(tilesetNode->first_attribute("columns")->value());
    xml_node<>* image = tilesetNode->first_node("image");
    string pathToTileset = "resources/tilesets/";
    pathToTileset += image->first_attribute("source")->value();

    Tileset* tileset =
        new Tileset(tilesetName, pathToTileset, Game::getSDLRenderer(),
                    tileWidth, tileHeight, tileCount, columns);
    tileset->setStartGID(firstGID);

    return tileset;
  }
}

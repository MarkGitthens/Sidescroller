#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <SDL.h>
#include "../util/tinyxml2.h"
#include "../util/tiled/Tileset.h"
#include "../core/Texture.h"
#include "../core/Entity.h"
#include "../core/Renderable.h"
#include "../core/Renderer.h"

using std::string;
using std::vector;
using std::stringstream;

class TiledMap : public Vulture2D::Entity, public Vulture2D::Renderable{
public:
    TiledMap() {};
    TiledMap(int width, int height, int tilew, int tileh) : width(width), height(height), tileWidth(tilew), tileHeight(tileh) {}

    int* getLayer(int index) {
        return layers.at(index);
    }
    int numLayers() {
        return layers.size();
    }

    void insertLayer(int layer[]) {
        layers.emplace_back(layer);
    }

    void drawLayer(int layer, int xOffset, int yOffset) {
        SDL_Rect src;
        SDL_Rect dest;
        int tilesetColumns = tilesets.at(0)->getColumnCount();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (layers.at(layer)[j * width + i] == 0)
                    continue;
                src.x = ((layers.at(layer)[j * width + i] % tilesetColumns)-1) * tileWidth;
                src.y = ((layers.at(layer)[j * width + i] / tilesetColumns)) * tileHeight;
                src.w = tileWidth;  
                src.h = tileHeight;

                dest.x = i * tileWidth - xOffset;
                dest.y = j * tileHeight - yOffset;
                dest.w = tileWidth;
                dest.h = tileHeight;
                Vulture2D::Renderer::getInstance().drawTexture(tilesets.at(0)->getImage(), &src, &dest);
            }
        }
    }

    virtual void update() {
        //Stub Tilemap will never need to perform any game logic.
    }

    virtual void render(SDL_Rect* cameraRect) {
        for (int i = 0; i < layers.size(); i++) {
            drawLayer(i, cameraRect->x, cameraRect->y);
        }
    }

    void addTileSheet(Tileset* tileset) {
        tilesets.emplace_back(tileset);
    }

private:
    int width, height;
    int tileWidth, tileHeight;

    vector<int*> layers;
    vector<Tileset*> tilesets;
};
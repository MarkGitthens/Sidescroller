#pragma once
#include <vector>
#include <SDL.h>
#include "Renderer.h"
#include "tinyxml2.h"
#include "Texture.h"

#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include "Entity.h"
#include "Renderable.h"
#include "Tileset.h"

using std::string;
using std::vector;
using std::stringstream;

class TiledMap : public Entity, public Renderable{
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
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (layers.at(layer)[j * width + i] == 0)
                    continue;
                src.x = ((layers.at(layer)[j * width + i] % 22)-1) * tileWidth;
                src.y = ((layers.at(layer)[j * width + i] / 22)) * tileHeight;
                src.w = tileWidth;  
                src.h = tileHeight;

                dest.x = i * tileWidth - xOffset;
                dest.y = j * tileHeight - yOffset;
                dest.w = tileWidth;
                dest.h = tileHeight;
                Renderer::getInstance().drawTexture(tilesets.at(0)->getImage(), &src, &dest);
            }
        }
    }

    void drawAllLayers(int xOffset, int yOffset) {
        SDL_Rect src;
        SDL_Rect dest;
        int numLayers = layers.size();
        for (int layer = 0; layer < numLayers; layer++) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    if (layers.at(layer)[j * width + i] == 0)
                        continue;
                    src.x = ((layers.at(layer)[j * width + i] % 22) - 1) * tileWidth;
                    src.y = ((layers.at(layer)[j * width + i] / 22)) * tileHeight;
                    src.w = tileWidth;
                    src.h = tileHeight;

                    dest.x = i * tileWidth - xOffset;
                    dest.y = j * tileHeight - yOffset;
                    dest.w = tileWidth;
                    dest.h = tileHeight;
                    Renderer::getInstance().drawTexture(tilesets.at(0)->getImage(), &src, &dest);
                }
            }
        }
    }

    virtual void update() {
        //Stub Tilemap will never need to perform any game logic.
    }

    virtual void render(SDL_Rect* cameraRect) {
        drawAllLayers(cameraRect->x, cameraRect->y);
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
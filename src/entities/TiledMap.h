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
    TiledMap(): width(1), height(1), tileWidth(128), tileHeight(128) {};
    TiledMap(int width, int height, int tilew, int tileh) : width(width), height(height), tileWidth(tilew), tileHeight(tileh) {}

    int* getLayer(size_t index) {
        return layers[index];
    }

    size_t numLayers() {
        return layers.size();
    }

    void insertLayer(int layer[]) {
        layers.emplace_back(layer);
    }

    void drawLayer(size_t layer, int xOffset, int yOffset) {
        SDL_Rect src;
        SDL_Rect dest;
        int tilesetColumns = tilesets[0]->getColumnCount();
        int* currentLayer = layers[layer];

        Vulture2D::Texture* tileTex = tilesets[0]->getImage();
        Vulture2D::Renderer& renderer = Vulture2D::Renderer::getInstance();
    
        int currentRow = 0;
        int currentTile = currentLayer[currentRow];

        for(int j = 0; j < height; j++, currentRow += width) {
            
            for(int i = 0; i < width; i++) {

                currentTile = currentLayer[currentRow + i];

                if(currentTile == 0)
                    continue;
                src.x = ((currentTile % tilesetColumns) - 1) * tileWidth;
                src.y = ((currentTile / tilesetColumns)) * tileHeight;
                src.w = tileWidth;
                src.h = tileHeight;

                dest.x = i * tileWidth - xOffset;
                dest.y = j * tileHeight - yOffset;
                dest.w = tileWidth;
                dest.h = tileHeight;

                renderer.drawTexture(tileTex, &src, &dest);
            }
        }
    }

    virtual void update() {
        //Stub Tilemap will never need to perform any game logic.
    }

    virtual void render(SDL_Rect* cameraRect) {
        for (size_t i = 0; i < layers.size(); i++) {
            drawLayer(i, cameraRect->x, cameraRect->y);
        }
    }

    void addTileSheet(Tileset* tileset) {
        tilesets.emplace_back(tileset);
    }
    
    int getWidth() {
        return width * tileWidth;
    }

    int getHeight() {
        return height * tileHeight;
    }

private:
    int width, height;
    int tileWidth, tileHeight;

    vector<int*> layers;
    vector<Tileset*> tilesets;
};

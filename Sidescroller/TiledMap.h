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
    void parseFile(char* path) {
        tinyxml2::XMLDocument file;
        file.LoadFile(path);
        if (file.Error())
            std::cout << "Can't load file";
        int layerNum = 0;

        tinyxml2::XMLElement* map = file.FirstChildElement("map");
        tinyxml2::XMLElement* layer = map->FirstChildElement("layer");

        while (layer) {
            layers.push_back(new int[width*height]);
            tinyxml2::XMLElement* data = layer->FirstChildElement("data");
            
            stringstream ss(data->GetText());

            int count = 0;
            string num;
                
            while (std::getline(ss, num, ',')) {
                layers.at(layerNum)[count] = atoi(num.c_str());
                count++;
            }

            layerNum++;
            layer = layer->NextSiblingElement("layer");
        }

        this->numLayers = layerNum;
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
                Renderer::getInstance().drawTexture(mImage, &src, &dest);
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
                    Renderer::getInstance().drawTexture(mImage, &src, &dest);
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

    void setTileSheet(char* path) {
        createFromPath(path);
    }

private:
    int width, height;
    int tileWidth, tileHeight;

    vector<int*> layers;
    vector<Tileset> tilesets;
};
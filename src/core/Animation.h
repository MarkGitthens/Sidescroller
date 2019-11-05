#pragma once
#include <SDL.h>
#include <string>
#include "util/rapidxml/rapidxml.hpp"
#include "util/rapidxml/rapidxml_utils.hpp"
#include "util/rapidxml/rapidxml_print.hpp"
#include "Texture.h"
#include <fstream>
#include "core/Game.h"
using namespace rapidxml;
namespace Vulture2D{
    class Animation {
    public:
        Animation() : currentTick(0), loopable(false), cycles(false), frameCount(0) { startTick = SDL_GetTicks(); };
        Animation(string path): currentTick(0), frameList(), loopable(false), cycles(false), frameCount(0) {
            startTick = SDL_GetTicks();
            parseFile(path, Game::getSDLRenderer());
        }
        ~Animation() = default;
        int getFrameCount() { return frameCount; }
        std::string getName() { return title; }
        SDL_Rect* getFrame(size_t frameNumber) { return &frameList[frameNumber]; }

        SDL_Rect* getCurrentFrame() { return &frameList[currentFrame]; }

        void update() {
            currentTick = SDL_GetTicks();

            if(currentTick - startTick >= frameDelay) {
                if(cycles) {
                    if(incrementing) {
                        currentFrame++;
                        if(currentFrame == frameCount - 1) {
                            incrementing = false;
                        }
                    } else {
                        currentFrame--;
                        if(currentFrame == 0) {
                            incrementing = true;
                        }
                    }

                } else {
                    if(currentFrame == frameCount - 1) {
                        currentFrame = 0;
                    } else {
                        currentFrame++;
                    }
                }
                
                startTick = currentTick;
            }
        }

        int  getFrameDelay() { return frameDelay; }

        bool parseFile(string path, SDL_Renderer* renderer) {
            file<> xmlFile(path.c_str());
            
            xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            //TODO: Need to update error handling for when the file doesn't exist
            {
                xml_node<>* animStart = doc.first_node("animation");
                title = animStart->first_node("name")->value();

                frameCount = atoi(animStart->first_node("framecount")->value());
                frameDelay = atoi(animStart->first_node("framedelay")->value());
                loopable = (animStart->first_node("loopable")->value() == "true");
                cycles = (animStart->first_node("cyclic")->value() == "true");

                xml_node<>* frameNode = animStart->first_node("frames");
                xml_node<>* frameElement = frameNode->first_node("frame");

                for (int i = 0; i < frameCount; i++) {
                    frameList[i].x = atoi(frameElement->first_attribute("x")->value());
                    frameList[i].y = atoi(frameElement->first_attribute("y")->value());
                    frameList[i].w = atoi(frameElement->first_attribute("width")->value());
                    frameList[i].h = atoi(frameElement->first_attribute("height")->value());

                    frameElement = frameElement->next_sibling("frame");
                }

                return true;
            }

        }
    private:
        bool incrementing = true;
        SDL_Rect frameList[64]; //Can have upto 128 frames
        int startTick;
        int currentTick;
        int frameDelay = 66;
        string title;
        bool loopable;
        bool cycles;
        int frameCount;
        int currentFrame = 0;
    };
}

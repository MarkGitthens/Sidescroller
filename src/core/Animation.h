#pragma once
#include <SDL.h>
#include <string>
#include "../util/tinyxml2.h"
#include "Texture.h"

namespace Vulture2D{
    class Animation {
    public:
        Animation() : currentTick(0), frameList(), loopable(false), cycles(false), frameCount(0) { startTick = SDL_GetTicks(); };
        Animation(string path): currentTick(0), frameList(), loopable(false), cycles(false), frameCount(0) {
            startTick = SDL_GetTicks();
            parseFile(path, Game::getSDLRenderer());
        }
        ~Animation() {};
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
            tinyxml2::XMLDocument doc;
            doc.LoadFile(path.c_str());

            if (doc.Error()) {
                std::cerr << "Can't load animation file: " << path << std::endl;
                doc.PrintError();
                return false;
            }
            else {
                tinyxml2::XMLElement* animStart = doc.FirstChildElement("animation");
                title = animStart->FirstChildElement("name")->GetText();

                animStart->FirstChildElement("framecount")->QueryIntText(&frameCount);
                animStart->FirstChildElement("framedelay")->QueryIntText(&frameDelay);
                animStart->FirstChildElement("loopable")->QueryBoolText(&loopable);
                animStart->FirstChildElement("cyclic")->QueryBoolText(&cycles);

                tinyxml2::XMLElement* frameNode = animStart->FirstChildElement("frames");

                tinyxml2::XMLElement* frameElement = frameNode->FirstChildElement("frame");
                frameList = new SDL_Rect[frameCount];
                for (int i = 0; i < frameCount; i++) {
                    frameList[i].x = frameElement->IntAttribute("x");
                    frameList[i].y = frameElement->IntAttribute("y");
                    frameList[i].w = frameElement->IntAttribute("width");
                    frameList[i].h = frameElement->IntAttribute("height");

                    frameElement = frameElement->NextSiblingElement("frame");
                }

                return true;
            }

        }
    private:
        bool incrementing = true;
        SDL_Rect *frameList;
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

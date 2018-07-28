#pragma once
#include <fstream>
#include <string>
#include "time.h"
#include <iostream>
//using namespace std;
namespace Vulture2D {
    class Log {
    public:
        Log();
        ~Log();
        Log(std::string);
        void openFile(std::string fileName, std::fstream::openmode mode = std::fstream::in | std::fstream::out | std::fstream::trunc);
        void closeFile();
        void writeMessage(const std::string& msg);

    private:
        std::fstream logFile;
        std::string fileName;
    };
}
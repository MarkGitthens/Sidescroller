#include "logger.h"

namespace Vulture2D {

    Log::Log() {}

    Log::Log(std::string file) : fileName(file) {
        openFile(fileName);
    }
    Log::~Log() {
        //    closeFile();
        //    std::cout << "closing log" << std::endl;
    }

    void Log::openFile(std::string file, std::ios_base::openmode mode) {
        if (!logFile.is_open()) {
            fileName.swap(file);
            std::cout << "Loading log file: " << fileName << std::endl;

            logFile.open(fileName, mode);

            std::string border = "==============================================================\n";
            std::string logMessage = "Begin Logging\n";
            logFile.write(border.c_str(), border.size());
            logFile.write(logMessage.c_str(), logMessage.size());
            logFile.write(border.c_str(), border.size());
            logFile.flush();
        }
    }
    void Log::closeFile() {
        if (logFile.is_open()) {
            std::cout << "Closing log file: " << fileName << std::endl;
            std::string border = "==============================================================\n";
            std::string logMessage = "End Logging\n";
            logFile.write(border.c_str(), border.size());
            logFile.write(logMessage.c_str(), logMessage.size());
            logFile.write(border.c_str(), border.size());
            logFile.close();
        }
    }

    void Log::writeMessage(const std::string& msg) {
        logFile.write(msg.c_str(), msg.size() - 1);
        logFile << std::endl;
        logFile.flush();
    }
}
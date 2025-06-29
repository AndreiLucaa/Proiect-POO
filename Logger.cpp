//
// Created by Andrei Luca on 29.06.2025.
//

#include "Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[LOG] " << msg << std::endl;
}

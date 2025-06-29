//
// Created by Andrei Luca on 29.06.2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <iostream>

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& msg);

private:
    Logger() = default;
    std::mutex mtx;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H

//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef FILEREADEXCEPTION_H
#define FILEREADEXCEPTION_H
#include <exception>
#include <string>


class FileReadException : public std::exception {
private:
    std::string filename;
    std::string message;
public:
    explicit FileReadException(const std::string &filename);
    const char *what() const noexcept override;
};


#endif //FILEREADEXCEPTION_H

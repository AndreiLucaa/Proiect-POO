//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef FILEREADEXCEPTION_H
#define FILEREADEXCEPTION_H
#include <exception>
#include <string>


class FileReadException : public std::exception {
public:
    explicit FileReadException(const std::string &filename);

    const char *what() const noexcept override;

    // const std::string &getFilename() const;

private:
    std::string filename;
};



#endif //FILEREADEXCEPTION_H

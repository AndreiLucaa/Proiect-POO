#ifndef WORDEXCEPTIONS_H
#define WORDEXCEPTIONS_H

#include <exception>
#include <string>

class WordException : public std::exception {
protected:
    std::string message;
public:
    explicit WordException(const std::string &msg);

    const char *what() const noexcept override;
};



#endif // WORDEXCEPTIONS_H
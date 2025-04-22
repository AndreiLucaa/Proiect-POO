#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <vector>
#include <string>



class Word {
public:
    Word(const std::string& word, const std::vector<std::string>& validWords);

    Word(const Word &other);

    Word(Word &&other) noexcept;

    Word & operator=(const Word &other);

    Word & operator=(Word &&other) noexcept;

    const std::string& getWord() const;

    bool isValid(const std::string& guess) const;

    bool correctLength(const std::string& guess) const;

    bool isCorrect(const std::string& guess) const;

    std::string getHint(const std::string& guess) const;

    std::pair<std::string, std::string> verifyLetters(const std::string &guess) const;

    std::string getLetters(const std::string& guess);

    ~Word();

private:
    std::string word;
    std::vector<std::string> validWords;
    std::string litere;

    bool privateIsValid(const std::string& guess) const;

    bool privateCorrectLength(const std::string& guess) const;

    bool privateIsCorrect(const std::string& guess) const;

    // std::string privateGetHint(const std::string& guess) const;

    std::pair<std::string, std::string> privateVerifyLetters(const std::string &guess) const;

    std::string privateGetLetters(const std::string& guess);

    friend std::ostream& operator<<(std::ostream& os, const Word& word) {
        os << "Word: " << word.word << "\n"
           << "Valid Words: ";
        for (const auto& validWord : word.validWords) {
            os << validWord << " ";
        }
        os << "\n";
        return os;
    }
};



#endif //WORD_H

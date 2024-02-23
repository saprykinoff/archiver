#pragma once
#include <string>
namespace exceptions {
class Archiver : public std::exception {
public:
    const char *what() const noexcept override {
        return "Common Archiver exception";
    }
};

// IOSteam
class IOstream : public Archiver {
public:
    const char *what() const noexcept override {
        return "Common IOstream exception";
    }
};
class CantOpenFile : public IOstream {
    std::string error_;

public:
    explicit CantOpenFile(const std::string &s) : error_("Can't open file " + s) {
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};

class CantWriteToFile : public IOstream {
    std::string error_;

public:
    explicit CantWriteToFile(const std::string &s) : error_("Can't write to file " + s) {
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};
class CantReadFromFile : public IOstream {
    std::string error_;

public:
    explicit CantReadFromFile(const std::string &s) : error_("Can't read from file " + s) {
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};

class NonBitString : public IOstream {
    const char *what() const noexcept override {
        return "Try to write non 0/1 string";
    }
};

class FileOverflowed : public IOstream {
    const char *what() const noexcept override {
        return "Try to read when EOF achieved";
    }
};
// IOSteam end

// My Symbol
class MySymbol : public Archiver {
    const char *what() const noexcept override {
        return "Common MySymbol exception";
    }
};

class SetBitError : public MySymbol {
public:
    const char *what() const noexcept override {
        return "Try to set too much bit";
    }
};
class GetBitError : public MySymbol {
public:
    const char *what() const noexcept override {
        return "Try to get too much bit";
    }
};
//  MySymbol end

// Trie
class Trie : public Archiver {
    const char *what() const noexcept override {
        return "Common Trie exception";
    }
};

class GoFromLeafError : public Trie {
public:
    const char *what() const noexcept override {
        return "Try to go from leaf node";
    }
};

class GetNonTerminaredNodeError : public Trie {
public:
    const char *what() const noexcept override {
        return "Try to get non terminated node";
    }
};

class TerminatedNodeHasChildError : public Trie {
public:
    const char *what() const noexcept override {
        return "Terminated node has children";
    }
};
class TrieOverflowed : public Trie {
public:
    const char *what() const noexcept override {
        return "Trie size was overflowed";
    }
};

class UseUninitiatedNodeError : public Trie {
public:
    const char *what() const noexcept override {
        return "Use uninitiated node";
    }
};
// Trie end

// Decoder
class Decoder : public Archiver {
    const char *what() const noexcept override {
        return "Common Decoder exception";
    }
};

class UnexpectedEndOfFile : public Decoder {
public:
    const char *what() const noexcept override {
        return "Unexpected end of file";
    }
};

class TryToIncreaseLength : public Archiver {
public:
    const char *what() const noexcept override {
        return "Try to increase string length in Inc()";
    }
};

class TryToIncrementEmptyString : public Archiver {
public:
    const char *what() const noexcept override {
        return "Try to increment empty string";
    }
};
// Decoder end

// Queue
class Queue : public Archiver {

public:
    const char *what() const noexcept override {
        return "Common Queue exception";
    }
};
class PopFromEmptyQueue : public Queue {
public:
    const char *what() const noexcept override {
        return "Try to pop from empty queue";
    }
};
class GetFromEmptyQueue : public Queue {
public:
    const char *what() const noexcept override {
        return "Try to get from empty queue";
    }
};

// Queue end

// ArgParser
class ArgParser : public Archiver {

public:
    const char *what() const noexcept override {
        return "Common Queue exception";
    }
};

class InvalidParameterCount : public ArgParser {
    std::string error_;

public:
    InvalidParameterCount(std::string arg, size_t got, int exp) {
        error_ = "Invalid parameter count for argument \'" + arg + "\': got " + std::to_string(got) +
                 ", but expected " + std::to_string(exp);
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};
class InvalidMinimalParameterCount : public ArgParser {
    std::string error_;

public:
    InvalidMinimalParameterCount(std::string arg, size_t got, size_t exp) {
        error_ = "Invalid parameter count for argument \'" + arg + "\': got " + std::to_string(got) +
                 ", but expected at least " + std::to_string(exp);
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};
class RequiredArgumentNotFound : public ArgParser {
    std::string error_;

public:
    explicit RequiredArgumentNotFound(std::string arg) {
        error_ = "Required argument \'" + arg + "\' not found";
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};
class CantFindArgument : public ArgParser {
    std::string error_;

public:
    explicit CantFindArgument(std::string arg) {
        error_ = "Try to get non-existent argument \'" + arg + "\'";
    }
    const char *what() const noexcept override {
        return error_.c_str();
    }
};

// ArgParser end

}  // namespace exceptions

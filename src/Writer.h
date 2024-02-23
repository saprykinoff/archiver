#pragma once
#include <fstream>
#include <string>
#include "MySymbol.h"

class WriterBase {
private:
    std::ofstream file_;
    unsigned char buffer_ = 0;
    int bits_ = 0;
    std::string filename_;
    const size_t buffsize_ = 100;
    std::string buffer_str_;

    void WriteByte();

protected:
    explicit WriterBase(const std::string &filename);
    WriterBase(const WriterBase &w) = delete;
    WriterBase &operator=(const WriterBase &w) = delete;
    ~WriterBase();

    void operator<<(const bool &bit);
    void Write(const bool &bit);

public:
    void Close();
    void BufferFlush();
    std::string GetFileName() {
        return filename_;
    }
};
class Writer : public WriterBase {
public:
    explicit Writer(const std::string &filename) : WriterBase(filename) {
    }

    using WriterBase::operator<<;
    void operator<<(const unsigned char &byte);
    void operator<<(const MySymbol &symbol);
    void operator<<(const std::string &str);
};

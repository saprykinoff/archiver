#pragma once
#include "constants.h"
#include "MySymbol.h"
#include <fstream>
#include <string>

class ReaderBase {
private:
    std::ifstream file_;
    unsigned char buffer_;
    int bits_ = CHAR_SIZE;
    std::string filename_;
    const size_t buffsize_ = 3;
    std::string buffer_str_;
    size_t buffer_str_index_ = 0;

    void ReadByte();
    void BufferRead();

protected:
    explicit ReaderBase(const std::string& filename);
    ReaderBase(const ReaderBase& r) = delete;
    ReaderBase& operator=(const ReaderBase& r) = delete;
    ~ReaderBase();

    bool operator>>(bool& bit);
    bool Read(bool& bit);

public:
    void Close();
    bool ReadBit();

    std::string GetFileName() {
        return filename_;
    }
};
class Reader : public ReaderBase {
public:
    explicit Reader(const std::string& filename) : ReaderBase(filename) {
    }

    using ReaderBase::operator>>;
    bool operator>>(unsigned char& byte);
    bool operator>>(MySymbol& symbol);

    unsigned char ReadChar();
    MySymbol ReadMy();
};

#include "Exceptions.h"
#include "Reader.h"
#include "constants.h"
#include <iostream>
ReaderBase::ReaderBase(const std::string &filename) : filename_(filename) {
    file_.open(filename);
    if (!file_) {
        throw exceptions::CantOpenFile(filename_);
    }
}
bool ReaderBase::Read(bool &bit) {
    if (bits_ == CHAR_SIZE && buffer_str_index_ == buffer_str_.size() && file_.peek() == EOF) {
        return false;
    }
    if (bits_ == CHAR_SIZE) {
        ReadByte();
        bits_ = 0;
    }
    bit = (buffer_ >> (CHAR_SIZE - bits_ - 1)) & 1;
    ++bits_;
    return true;
}
void ReaderBase::ReadByte() {
    if (buffer_str_index_ >= buffer_str_.size()) {
        BufferRead();
    }
    buffer_ = buffer_str_[buffer_str_index_];
    ++buffer_str_index_;
}

void ReaderBase::BufferRead() {
    bool error = false;
    std::string tmp_buffer;
    for (size_t i = 0; i < buffsize_; ++i) {
        if (file_.peek() == EOF) {
            error = true;
            break;
        }
        tmp_buffer += static_cast<char>(file_.get());
    }
    if (error && tmp_buffer.empty()) {
        throw exceptions::CantReadFromFile(filename_);
    }
    buffer_str_ = tmp_buffer;
    buffer_str_index_ = 0;
}
void ReaderBase::Close() {
    file_.close();
}
bool ReaderBase::operator>>(bool &bit) {
    return Read(bit);
}
bool Reader::operator>>(unsigned char &byte) {
    byte = 0;
    for (int i = CHAR_SIZE - 1; i >= 0; --i) {
        bool x = false;
        if (!Read(x)) {
            return false;
        }
        byte = byte | (x << i);
    }
    return true;
}

bool Reader::operator>>(MySymbol &symbol) {
    symbol.Clear();
    for (int i = MY_SYMBOL_SIZE - 1; i >= 0; --i) {
        bool x = false;
        if (!Read(x)) {
            return false;
        }
        symbol.SetBit(i, x);
    }
    return true;
}

ReaderBase::~ReaderBase() {
    Close();
}
bool ReaderBase::ReadBit() {
    bool res = false;
    bool success = *this >> res;
    if (!success) {
        throw exceptions::FileOverflowed();
    }
    return res;
}
unsigned char Reader::ReadChar() {
    unsigned char res = 0;
    bool success = *this >> res;
    if (!success) {
        throw exceptions::FileOverflowed();
    }
    return res;
}
MySymbol Reader::ReadMy() {
    MySymbol res;
    bool success = *this >> res;
    if (!success) {
        throw exceptions::FileOverflowed();
    }
    return res;
}
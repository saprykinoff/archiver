#include "Exceptions.h"
#include "Writer.h"
#include "constants.h"

WriterBase::WriterBase(const std::string &filename) : filename_(filename) {
    file_.open(filename);
    if (!file_) {
        throw exceptions::CantOpenFile(filename_);
    }
}
void WriterBase::WriteByte() {
    buffer_str_ += static_cast<char>(buffer_);
    buffer_ = 0;
    bits_ = 0;
    if (buffer_str_.size() >= buffsize_) {
        BufferFlush();
    }
}
void WriterBase::Write(const bool &bit) {
    buffer_ = (buffer_ << 1) + bit;
    bits_ += 1;
    if (bits_ == CHAR_SIZE) {
        WriteByte();
    }
}
WriterBase::~WriterBase() {
    Close();
}
void WriterBase::Close() {
    if (bits_) {
        buffer_ = (buffer_ << (CHAR_SIZE - bits_));
        bits_ = 0;
        WriteByte();
    }
    if (!buffer_str_.empty()) {
        BufferFlush();
    }
    file_.close();
}
void WriterBase::operator<<(const bool &bit) {
    Write(bit);
}
void WriterBase::BufferFlush() {
    try {
        file_ << buffer_str_;
    } catch (...) {
        throw exceptions::CantWriteToFile(filename_);
    }

    buffer_str_.clear();
}

void Writer::operator<<(const unsigned char &byte) {
    for (int i = CHAR_SIZE - 1; i >= 0; --i) {
        Write(static_cast<bool>(((byte >> i) & 1)));
    }
}

void Writer::operator<<(const MySymbol &symbol) {
    for (int i = MY_SYMBOL_SIZE - 1; i >= 0; --i) {
        auto tmp = symbol.GetBit(i);
        Write(tmp);
    }
}
void Writer::operator<<(const std::string &str) {
    for (auto c : str) {
        if (c == '1') {
            *this << true;
        } else if (c == '0') {
            *this << false;
        } else {
            throw exceptions::NonBitString();
        }
    }
}

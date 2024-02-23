#include "Exceptions.h"
#include "MySymbol.h"
#include "constants.h"
#include <iostream>
std::ostream &operator<<(std::ostream &out, const MySymbol &m) {
    switch (m.value_) {
        case ARCHIVE_END:
            out << "ARCHIVE_END";
            break;
        case FILENAME_END:
            out << "FILENAME_END";
            break;
        case ONE_MORE_FILE:
            out << "ONE_MORE_FILE";
            break;
        default:
            out << m.value_ << '(';
            if (m.value_ < (1 << CHAR_SIZE)) {
                out << static_cast<unsigned char>(m.value_);
            }
            out << ')';
            break;
    }
    return out;
}
MySymbol::MySymbol(unsigned char val) {
    value_ = static_cast<StorageType>(val);
}
void MySymbol::SetBit(size_t i, bool val) {
    if (i > sizeof(StorageType) * CHAR_SIZE) {
        throw exceptions::SetBitError();
    }
    value_ = value_ | (val << i);
}
bool MySymbol::GetBit(size_t i) const {
    if (i > sizeof(StorageType) * CHAR_SIZE) {
        throw exceptions::GetBitError();
    }
    return (value_ >> i) & 1;
}
void MySymbol::Clear() {
    value_ = 0;
}
MySymbol::StorageType MySymbol::GetValue() const {
    return value_;
}
bool MySymbol::operator==(const MySymbol &a) const {
    return value_ == a.value_;
}
unsigned char MySymbol::ToChar() const {
    return static_cast<unsigned char>(value_);
}
bool MySymbol::operator<(const MySymbol &m) const {
    return value_ < m.value_;
}

#pragma once

#include <iostream>
class MySymbol {
private:
    using StorageType = int16_t;
    StorageType value_;

public:
    explicit MySymbol() : value_(static_cast<StorageType>(0)){};
    explicit MySymbol(int val) : value_(static_cast<StorageType>(val)){};
    explicit MySymbol(unsigned char val);
    void SetBit(size_t i, bool val);
    bool GetBit(size_t i) const;
    void Clear();
    StorageType GetValue() const;
    bool operator==(const MySymbol &a) const;
    unsigned char ToChar() const;
    bool operator<(const MySymbol &m) const;
    friend std::ostream &operator<<(std::ostream &out, const MySymbol &m);
};

#pragma once
#include "TrieBase.h"
#include "MySymbol.h"
#include <map>
class TrieEncode : public TrieBase {
public:
    void RecursiveRestore(std::map<std::string, MySymbol> &out, std::string current_mask, size_t current_node);
    size_t InitNode(MySymbol value);
    size_t Union(size_t l, size_t r);
    std::map<std::string, MySymbol> Get();
};
class TrieDecode : public TrieBase {
private:
    size_t pointer_ = 0;
    MySymbol current_;

public:
    bool Go(bool fl);
    void Add(const std::string &key, const MySymbol &m);
    void SetPointr(const size_t &val) {
        pointer_ = val;
    }
    MySymbol Get();
};
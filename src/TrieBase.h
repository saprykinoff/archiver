#pragma once
#include "MySymbol.h"
#include <vector>
#include <stdexcept>
#include <optional>
class TrieBase {
public:
    struct Node {
        std::optional<size_t> parent;
        std::optional<size_t> l;
        std::optional<size_t> r;
        bool initiated = false;
        bool terminated = false;
        MySymbol value;
    };

    void Reserve(size_t size);
    size_t GetRoot() const;
    void SetRoot(size_t root);
    size_t NewNode();

protected:
    std::vector<Node> nodes_;
    size_t root_;
    size_t node_counter_ = 0;
    Node &GetNode(size_t node);
};

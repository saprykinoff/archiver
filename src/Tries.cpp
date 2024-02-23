#include "Exceptions.h"
#include "Tries.h"
#include "constants.h"
bool TrieDecode::Go(bool fl) {  // true = r
    Node &node = GetNode(pointer_);
    std::optional<size_t> to = node.l;
    if (fl) {
        to = node.r;
    }
    if (!to) {
        throw exceptions::GoFromLeafError();
    }
    pointer_ = to.value();
    return GetNode(pointer_).terminated;
}
void TrieDecode::Add(const std::string &key, const MySymbol &m) {
    size_t now = root_;
    for (size_t i = 0; i < key.size(); ++i) {
        Node &node = GetNode(now);
        if (key[i] == '0') {
            if (!node.l) {
                node.l = NewNode();
            }
            now = node.l.value();
        } else {
            if (!node.r) {
                node.r = NewNode();
            }
            now = node.r.value();
        }
    }
    Node &node = GetNode(now);
    node.terminated = true;
    node.value = m;
}
MySymbol TrieDecode::Get() {
    auto &node = GetNode(pointer_);
    if (!node.terminated) {
        throw exceptions::GetNonTerminaredNodeError();
    }
    pointer_ = root_;
    return node.value;
}

void TrieEncode::RecursiveRestore(std::map<std::string, MySymbol> &out, std::string current_mask, size_t current_node) {
    auto node = GetNode(current_node);
    if (node.terminated) {
        out[current_mask] = node.value;
        if (node.l || node.r) {
            throw exceptions::TerminatedNodeHasChildError();
        }
        return;
    }
    if (node.l) {
        RecursiveRestore(out, current_mask + "0", node.l.value());
    }
    if (node.r) {
        RecursiveRestore(out, current_mask + "1", node.r.value());
    }
}
size_t TrieEncode::InitNode(MySymbol value) {
    size_t i = NewNode();
    Node &node = nodes_[i];
    node.value = value;
    node.terminated = true;
    return i;
}
size_t TrieEncode::Union(size_t l, size_t r) {
    size_t parent = NewNode();
    GetNode(parent).l = l;
    GetNode(parent).r = r;
    GetNode(l).parent = parent;
    GetNode(r).parent = parent;
    return parent;
}
std::map<std::string, MySymbol> TrieEncode::Get() {
    std::map<std::string, MySymbol> res;
    RecursiveRestore(res, "", root_);
    return res;
}

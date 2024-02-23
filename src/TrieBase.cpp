#include "Exceptions.h"
#include "TrieBase.h"
void TrieBase::Reserve(size_t size) {
    nodes_.resize(size);
}
void TrieBase::SetRoot(size_t root) {
    root_ = root;
}
size_t TrieBase::NewNode() {

    if (node_counter_ == nodes_.size()) {
        throw exceptions::TrieOverflowed();
    }
    nodes_[node_counter_].initiated = true;
    return node_counter_++;
}
TrieBase::Node& TrieBase::GetNode(size_t node) {
    if (!nodes_[node].initiated) {
        throw exceptions::UseUninitiatedNodeError();
    }
    return nodes_[node];
}
size_t TrieBase::GetRoot() const {
    return root_;
}

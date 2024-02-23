#include "Exceptions.h"
#pragma once
#include <vector>
#include <tuple>
template <typename PRIORITY_T, typename VALUE_T>
class PriorityQueue {  // min-heap
private:
    struct Node {
        PRIORITY_T priority;
        VALUE_T value;
        bool operator<(const Node &other) {
            return std::tie(priority, value) < std::tie(other.priority, other.value);
        }
    };

    std::vector<Node> heap_;

    size_t Parent(size_t i) {
        if (i == 0) {
            return 0;
        }
        return (i - 1) / 2;
    }
    size_t LeftChild(size_t i) {
        return 2 * i + 1;
    }
    size_t RightChild(size_t i) {
        return 2 * i + 2;
    }
    void Push(size_t i) {
        if (i == 0) {
            return;
        }
        size_t par = Parent(i);
        if (heap_[i] < heap_[par]) {
            std::swap(heap_[i], heap_[par]);
            Push(par);
        }
    }
    void Pull(size_t i) {
        if (i >= heap_.size()) {
            return;
        }
        size_t l = LeftChild(i);
        size_t r = RightChild(i);
        if (r < heap_.size()) {  // both child
            size_t best = 0;
            if (heap_[r] < heap_[l]) {
                best = r;
            } else {
                best = l;
            }
            if (heap_[best] < heap_[i]) {
                std::swap(heap_[best], heap_[i]);
                Pull(best);
            }
        } else if (l < heap_.size()) {  // only left
            if (heap_[l] < heap_[i]) {
                std::swap(heap_[l], heap_[i]);
                Pull(l);
            }
        }
    }

public:
    Node Front() {
        if (heap_.empty()) {
            throw exceptions::GetFromEmptyQueue();
        }
        return heap_[0];
    }
    void Push(const Node &el) {
        heap_.push_back(el);
        Push(heap_.size() - 1);
    }
    void Pop() {
        if (heap_.empty()) {
            throw exceptions::PopFromEmptyQueue();
        }
        std::swap(heap_[0], heap_.back());
        heap_.pop_back();
        Pull(0);
    }

    bool Validate() {
        for (size_t i = 0; i < heap_.size(); ++i) {
            if (heap_[i] < heap_[Parent(i)]) {
                return false;
            }
        }
        return true;
    }
    size_t Size() {
        return heap_.size();
    }
};

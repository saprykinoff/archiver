#include "Exceptions.h"
#include "common.h"
#include <string>
#include <stdexcept>
void Inc(std::string &a) {
    if (a.empty()) {
        throw exceptions::TryToIncrementEmptyString();
    }
    int64_t n = static_cast<int64_t>(a.size());
    for (int64_t i = n - 1; i >= 0; --i) {
        if (a[i] == '0') {
            a[i] = '1';
            return;
        } else {
            a[i] = '0';
        }
    }
    throw exceptions::TryToIncreaseLength();
}
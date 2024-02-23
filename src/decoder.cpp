#include "Exceptions.h"
#include "decoder.h"

#include <vector>
#include "MySymbol.h"
#include "constants.h"
void CheckFileEnd(bool f) {
    if (!f) {
        throw exceptions::UnexpectedEndOfFile();
    }
}
TrieDecode DecodeTable(Reader &archive) {
    int n = archive.ReadMy().GetValue();
    std::vector<MySymbol> vec(n);
    for (int i = 0; i < n; ++i) {
        CheckFileEnd(archive >> vec[i]);
    }
    int sum = 0;
    std::vector<int> sizes(1);
    while (sum < n) {
        MySymbol x;
        CheckFileEnd(archive >> x);
        sizes.push_back(x.GetValue());
        sum += x.GetValue();
    }
    TrieDecode res;
    res.Reserve(4 * n);
    res.NewNode();
    res.SetRoot(0);
    std::string now;
    size_t size_i = 0;
    size_t symb_i = 0;
    while (size_i < sizes.size()) {
        if (sizes[size_i] == 0) {
            now += '0';
            size_i += 1;
            continue;
        }
        res.Add(now, vec[symb_i]);
        DEBUG_PRINT(now << ' ' << vec[symb_i] << '\n')
        ++symb_i;
        --sizes[size_i];
        try {
            Inc(now);
        } catch (exceptions::TryToIncreaseLength &e) {
        } catch (...) {
            throw;
        }
    }
    return res;
}

bool UnzipOneFile(Reader &archive) {  // return true if there are one more file
    auto trie = DecodeTable(archive);
    trie.SetPointr(trie.GetRoot());
    std::string filename;
    bool tmp = false;
    MySymbol fend(FILENAME_END);
    MySymbol aend(ARCHIVE_END);
    MySymbol omf(ONE_MORE_FILE);
    while (true) {
        CheckFileEnd(archive >> tmp);
        if (!trie.Go(tmp)) {
            continue;
        }
        MySymbol my = trie.Get();
        DEBUG_PRINT("readed: " << my << '\n')
        if (my == fend) {
            break;
        }
        filename += static_cast<char>(my.GetValue());  // NEED SIGNED FOR STRINGS
    }
    Writer file(filename);
    while (true) {
        CheckFileEnd(archive >> tmp);
        if (!trie.Go(tmp)) {
            continue;
        }
        MySymbol my = trie.Get();
        DEBUG_PRINT("readed: " << my << '\n')
        if (my == aend) {
            return false;
        }
        if (my == omf) {
            return true;
        }
        file << my.ToChar();
    }
}
void UnzipFiles(const std::string &arcname) {
    Reader archive(arcname);
    while (UnzipOneFile(archive)) {
    }
}
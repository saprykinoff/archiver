#include "Exceptions.h"
#include "encoder.h"
#include "Tries.h"
#include "PriorityQueue.h"
#include "common.h"
std::map<int, int> CountAllSymbols(Reader &reader) {
    unsigned char c = 0;
    std::map<int, int> res;
    while (reader >> c) {
        ++res[c];
    }

    for (const char &ch : reader.GetFileName()) {
        ++res[ch];
    }

    res[FILENAME_END] = 1;
    res[ONE_MORE_FILE] = 1;
    res[ARCHIVE_END] = 1;
    return res;
}

Table MakeTable(const std::map<int, int> &counts) {
    TrieEncode trie;
    trie.Reserve(2 * counts.size());
    PriorityQueue<std::pair<int, size_t>, size_t> queue;
    for (auto [k, v] : counts) {
        if (v) {
            queue.Push({{v, k}, trie.InitNode(MySymbol(k))});
        }
    }
    while (queue.Size() > 1) {
        auto a = queue.Front();
        queue.Pop();
        auto b = queue.Front();
        queue.Pop();
        auto c = a;
        c.value = trie.Union(a.value, b.value);
        c.priority.first = a.priority.first + b.priority.first;
        c.priority.second = std::min(a.priority.second, b.priority.second);
        queue.Push(c);
    }
    auto root = queue.Front();
    trie.SetRoot(root.value);
    return trie.Get();
}
Table MakeCanonic(const Table &codes) {
    std::vector<std::pair<size_t, int>> to_sort;
    for (auto &[k, v] : codes) {
        to_sort.push_back({k.size(), v.GetValue()});
    }
    std::sort(to_sort.begin(), to_sort.end());
    size_t sz = to_sort[0].first;
    std::string now;
    for (size_t i = 0; i < sz; ++i) {
        now += '0';
    }
    Table res;
    res[now] = MySymbol(to_sort[0].second);
    for (size_t i = 1; i < to_sort.size(); ++i) {
        auto &[len, val] = to_sort[i];
        Inc(now);
        while (now.size() < len) {
            now += '0';
        }
        res[now] = MySymbol(val);
    }
    return res;
}
void EncodeTable(const Table &table, Writer &archive) {
    MySymbol n(static_cast<int>(table.size()));
    DEBUG_PRINT("N:" << n << '\n')
    archive << n;
    std::vector<int> szs(MAX_CODE + 10);
    size_t mx_size = 0;

    for (auto &[k, v] : table) {
        ++szs[k.size()];
        mx_size = std::max(mx_size, k.size());
        archive << MySymbol(v);
        DEBUG_PRINT(k << '\n')
    }

    DEBUG_PRINT("Sizes:\n")
    for (size_t i = 1; i <= mx_size; ++i) {
        archive << MySymbol(szs[i]);
        DEBUG_PRINT(i << ' ' << MySymbol(szs[i]) << '\n')
    }
}

void ZipOneFile(const std::string &filename, Writer &archive, bool archive_end) {
    Reader file1(filename);
    auto count = CountAllSymbols(file1);
    Table table = MakeCanonic(MakeTable(count));
    std::map<MySymbol, std::string> revtable;
    for (auto [k, v] : table) {
        revtable[v] = k;
    }
    EncodeTable(table, archive);
    file1.Close();
    Reader file2(filename);
    unsigned char tmp = 0;
    for (auto c : filename) {
        MySymbol m(c);
        archive << revtable[m];
    }
    archive << revtable[MySymbol(FILENAME_END)];
    while (file2 >> tmp) {
        auto tmp2 = MySymbol(tmp);
        archive << revtable[tmp2];
    }
    if (archive_end) {
        archive << revtable[MySymbol(ARCHIVE_END)];
    } else {
        archive << revtable[MySymbol(ONE_MORE_FILE)];
    }
}
void ZipFiles(const std::string &arcname, const std::vector<std::string> &files) {
    Writer archive(arcname);
    for (size_t i = 0; i < files.size(); ++i) {
        ZipOneFile(files[i], archive, i + 1 == files.size());
    }
}
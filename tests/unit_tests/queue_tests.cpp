#include "tester.h"
#include "../../src/PriorityQueue.h"
TEST_CASE("QueueOrderCheck") {
    int n = 10;
    for (int mask = 0; mask < (1 << n); ++mask) {
        PriorityQueue<int, char> q;
        for (int i = 0; i < n; ++i) {
            q.Push({(mask >> i) & 1, static_cast<char>('a' + i)});
        }
        std::string expected;
        {
            std::string a;
            std::string b;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    b += static_cast<char>('a' + i);
                } else {
                    a += static_cast<char>('a' + i);
                }
            }
            expected = a + b;
        }
        std::string result;
        {
            for (int i = 0; i < n; ++i) {
                result += q.Front().value;
                q.Pop();
            }
        }
        REQUIRE(result == expected);
    }
}

TEST_CASE("QueueErrors") {
    PriorityQueue<int, int> q;
    bool caught = false;
    try {
        q.Front();
    } catch (exceptions::GetFromEmptyQueue &a) {
        caught = true;
    }
    REQUIRE(caught);
    caught = false;
    try {
        q.Pop();
    } catch (exceptions::PopFromEmptyQueue &a) {
        caught = true;
    }
    REQUIRE(caught);
}

TEST_CASE("QueueBase") {
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    //    seed = 8885943753998;
    rnd.seed(seed);
    std::cout << "QueueBase " << seed << std::endl;
    int cnt = 1000;
    for (int ZZ = 0; ZZ < cnt; ++ZZ) {
        int n = static_cast<int>(rnd() % 100 + 10);
        std::vector<std::pair<int, int>> data(n);
        PriorityQueue<int, int> q;
        for (int i = 0; i < n; ++i) {
            int x = rnd() % 101 - 50;
            int y = rnd() % 101 - 50;
            data[i] = {x, y};
            q.Push({x, y});
        }
        sort(data.begin(), data.end());
        for (int i = 0; i < n; ++i) {
            auto x = q.Front().value;
            q.Pop();
            auto y = data[i].second;
            REQUIRE(x == y);
        }
    }
}
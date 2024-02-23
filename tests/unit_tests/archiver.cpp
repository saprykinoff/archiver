#include "tester.h"
#include "../src/encoder.h"
#include "../src/decoder.h"
TEST_CASE("CanonicCheck") {
    {
        std::map<int, int> cnt;
        cnt['a'] = 15;
        cnt['b'] = 7;
        cnt['c'] = 6;
        cnt['d'] = 6;
        cnt['e'] = 5;
        auto result = MakeCanonic(MakeTable(cnt));
        std::map<std::string, MySymbol> expected = {
            {"0", MySymbol('a')},   {"100", MySymbol('b')}, {"101", MySymbol('c')},
            {"110", MySymbol('d')}, {"111", MySymbol('e')},
        };
        REQUIRE(expected == result);
    }
}
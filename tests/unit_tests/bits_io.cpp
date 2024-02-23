#include "tester.h"
#include "../src/Reader.h"
#include "../src/Writer.h"
#include "../src/Exceptions.h"
bool validate() {
    int cnt = 1000 + rnd() % 1000;
    Writer writer("aboba.txt");
    std::vector<bool> vc;
    for (int i = 0; i < cnt; ++i) {
        vc.push_back(rnd() % 2);
        writer << vc.back();
    }
    writer.Close();
    Reader reader("aboba.txt");
    for (int i = 0; i < cnt; ++i) {
        bool read;
        assert(reader >> read);
        if (read != vc[i]) {
            return false;
        }
    }
    return true;
}
TEST_CASE("BitsIO") {
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    //    seed = 8885943753998;
    rnd.seed(seed);
    std::cout << "BitsIO " << seed << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        REQUIRE(validate());
    }
}
TEST_CASE("Cant open") {
    bool caught = false;
    try {
        Writer w("abob/us.txt");
    } catch (exceptions::CantOpenFile &a) {
        caught = true;
    }
    REQUIRE(caught);
    caught = false;
    try {
        Reader t("amogus/us.txt");
    } catch (exceptions::CantOpenFile &a) {
        caught = true;
    }
    REQUIRE(caught);
}

#include "tester.h"
#include "../../src/ArgParser.h"

std::string TestParser(std::vector<std::string>& v) {
    std::string res;
    for (const auto& x : v) {
        res += x;
        res += '/';
    }
    return res;
}
std::string RealParser(std::vector<std::string>& v) {
    std::string res;
    for (size_t i = 1; i < v.size(); ++i) {
        res += v[i];
        if (i + 1 != v.size()) {
            res += '/';
        }
    }
    return res;
}

TEST_CASE("Simple") {
    ArgParser arg({"-h", "-a", "b", "c", "-d", "1"});
    arg.SetStatus("h", ArgParser::ZERO);
    arg.SetStatus("a", ArgParser::MULTIPLE);
    arg.SetStatus("d", ArgParser::ONE);
    arg.Parse();
    //    std::cout << arg.GetArg("h", TestParser);
    REQUIRE(arg.GetArg<std::string>("h", TestParser) == "-h/");
    REQUIRE(arg.GetArg<std::string>("a", TestParser) == "-a/b/c/");
    REQUIRE(arg.GetArg<std::string>("d", TestParser) == "-d/1/");
}
TEST_CASE("Exception") {
    {
        ArgParser arg({"-aboba", "-boba"});
        arg.SetStatus("aboba", ArgParser::ONE);

        bool caught = false;
        try {
            arg.Parse();
        } catch (exceptions::InvalidParameterCount& a) {
            caught = true;
        }
        REQUIRE(caught);
    }
    {
        ArgParser arg({"-aboba", "biba", "boba"});
        arg.SetStatus("aboba", ArgParser::MULTIPLE, 3);
        bool caught = false;
        try {
            arg.Parse();
        } catch (exceptions::InvalidMinimalParameterCount& a) {
            caught = true;
        }
        REQUIRE(caught);
    }
    {
        ArgParser arg({"-aboba", "biba", "boba", "-boba", "1", "2", "3"});
        arg.SetStatus("aboba", ArgParser::MULTIPLE, 2);
        arg.SetStatus("aboba", ArgParser::MULTIPLE, 1);
        bool ok = true;
        try {
            arg.Parse();
        } catch (...) {
            ok = false;
        }
        REQUIRE(ok);
        REQUIRE(arg.GetArg<std::string>("aboba", RealParser) == "biba/boba");
        REQUIRE(arg.GetArg<std::string>("boba", RealParser) == "1/2/3");
    }
}
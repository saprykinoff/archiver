#include "catch.hpp"
#include "iostream"
const std::string EXECUTABLE = "~/study/cpp/cmake-build-debug/archiver";
const std::string PRIVATE_PATH = "~/study/cpp/cmake-build-debug/testing/";  // папка с временными файлами
const std::string PUBLIC_PATH = "~/study/cpp/tasks/archiver/tests/data/";  // папка с данными
auto cmd(std::string c) {
    return system(c.c_str());
}
const bool CHECK_ARC = true;
const bool CHECK_OUT = true;
double totoal_time_to_encode = 0;
double totoal_time_to_decode = 0;
double GetTime() {
    return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch().count()).count()/1e9;
}
void CheckSample(const std::string& dirname, const std::vector<std::string>& files) {
    {
        std::cout << "Stat encoding " << dirname << "... " << std::flush;
        // zip
        cmd("mkdir -p " + PRIVATE_PATH + dirname);
        std::string my_arc_name = PRIVATE_PATH + dirname + ".arc";
        std::string full_dirname = PUBLIC_PATH + dirname;
        std::string command = "cd " + full_dirname + " && " + EXECUTABLE + " -c " + my_arc_name + " ";
        for (const auto& file : files) {
            command += file + " ";
        }
        double start = GetTime();
        cmd(command);
        double end = GetTime();
        double delta = end - start;
        totoal_time_to_encode += delta;
        std::cout << "Encoded(" << delta << "s)... " << std::flush;

        // check
        if (CHECK_ARC) {

            std::string right_arc_name = PUBLIC_PATH + dirname + ".arc";
            std::cout << "Comparing...        " << std::flush;
            if (cmd("diff " + my_arc_name + " " + right_arc_name)) {
                std::string s = "Не совпадают файлы архивов";
                REQUIRE(s == "");
                std::cout << "Error";
            } else {
                std::cout << "OK...";
            }
        }
        std::cout << std::endl;
    }
    {

        if (CHECK_OUT) {
            std::cout << "Stat decoding " << dirname << "... " << std::flush;

            // unzip
            std::string my_arc_name = PRIVATE_PATH + dirname + ".arc";
            std::string full_dirname = PRIVATE_PATH + dirname;
            std::string command = "cd " + full_dirname + " && " + EXECUTABLE + " -d " + my_arc_name + " ";
            double start = GetTime();
            cmd(command);
            double end = GetTime();
            double delta = end - start;
            totoal_time_to_decode += delta;
            std::cout << "Decoded(" << delta << "s)... " << std::flush;
            std::cout << "Comparing...        " << std::flush;
            // check
            std::string my_dir = full_dirname + "/";
            std::string orig_dir = PUBLIC_PATH + dirname + "/";
            for (const auto& file : files) {
                REQUIRE(cmd("diff " + my_dir + file + " " + orig_dir + file) == 0);
                if (cmd("diff " + my_dir + file + " " + orig_dir + file)) {
                    std::cout << "Error...";
                } else {
                    std::cout << "OK...";
                }
            }
            std::cout << std::endl;
        }
    }
}
TEST_CASE("a") {
    CheckSample("a", {"a"});
}
TEST_CASE("empty") {
    CheckSample("empty", {"empty"});
}
TEST_CASE("forest") {
    CheckSample("forest", {"forest.mp4"});
}
TEST_CASE("master") {
    CheckSample("master", {"master_i_margarita.txt"});
}

TEST_CASE("mountains") {
    CheckSample("mountains", {"mountains.jpg"});
}

TEST_CASE("multiple_files") {
    std::vector<std::string> tmp = {"master_i_margarita.txt", "mountains.jpg", "forest.mp4", "shabanov.pdf"};
    sort(tmp.begin(), tmp.end());
    CheckSample("multiple_files", tmp);
}

TEST_CASE("new_lines") {
    CheckSample("new_lines", {"new_lines"});
}
TEST_CASE("Out") {
    std::cout << "Total time to encode: " << totoal_time_to_encode << "s\n";
    std::cout << "Total time to decode: " << totoal_time_to_decode << "s\n";
}

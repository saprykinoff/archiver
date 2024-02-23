#include "Exceptions.h"
#include <iostream>
#include <vector>
#include "encoder.h"
#include "decoder.h"
#include "ArgParser.h"
using CompressArgType = std::pair<std::string, std::vector<std::string>>;
CompressArgType CompressParser(std::vector<std::string>& s) {
    std::vector<std::string> tmp;
    for (size_t i = 2; i < s.size(); ++i) {
        tmp.push_back(s[i]);
    }
    return {s[1], tmp};
}
std::string DecompressParser(std::vector<std::string>& s) {
    return s[1];
}
int main(int argc, char** argv) {
    ArgParser arg(argc, argv);
    arg.SetStatus("h", ArgParser::ZERO);
    arg.SetStatus("d", ArgParser::ONE);
    arg.SetStatus("c", ArgParser::MULTIPLE, 2);
    try {
        arg.Parse();
    } catch (exceptions::ArgParser& e) {
        std::cout << e.what() << '\n';
        std::cout << "Use -h for help\n";
    }
    if (arg.CheckArgument("h")) {
        std::cout << "archiver -c archive_name file1 [file2 ...] - заархивировать файлы file1, file2, ... и сохранить "
                     "результат в файл archive_name.\n"
                     "\n"
                     "archiver -d archive_name - разархивировать файлы из архива archive_name и положить в текущую "
                     "директорию.\n"
                     "\n"
                     "archiver -h - вывести справку по использованию программы.";
    }
    try {
        if (arg.CheckArgument("c")) {
            auto [arcname, files] = arg.GetArg<CompressArgType>("c", CompressParser);
            ZipFiles(arcname, files);
        }
        if (arg.CheckArgument("d")) {
            auto arcname = arg.GetArg<std::string>("d", DecompressParser);
            UnzipFiles(arcname);
        }
    } catch (exceptions::Archiver& e) {
        std::cerr << e.what();
        return 111;
    }
    return 0;
}

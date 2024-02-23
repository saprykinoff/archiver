#pragma once
#include <string>
#include <map>
#include <set>
#include <functional>
#include "Exceptions.h"
class ArgParser {
public:
    enum CntType { ZERO, ONE, MULTIPLE };

private:
    using Command = std::vector<std::string>;
    std::map<std::string, CntType> cnt_;
    std::set<std::string> req_;
    std::map<std::string, size_t> min_cnt_;
    std::map<std::string, Command> command_vec_;
    std::vector<std::string> commands_;

public:
    ArgParser(int argc, char **argv);
    explicit ArgParser(const std::vector<std::string> &commands);

    void Parse();
    template <typename T>
    T GetArg(const std::string &cmd, std::function<T(std::vector<std::string> &)> parser) {
        if (command_vec_.count(cmd) == 0) {
            throw exceptions::CantFindArgument(cmd);
        }
        return parser(command_vec_[cmd]);
    }
    void SetRequired(const std::string &s);
    void SetStatus(const std::string &s, const CntType &t, const int &minimal = 0);
    void NewCommand(const std::vector<std::string> &now);
    bool CheckArgument(const std::string &s);
};
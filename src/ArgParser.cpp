#include "ArgParser.h"
#include "Exceptions.h"
void ArgParser::Parse() {
    std::vector<std::string> now;
    for (size_t i = 0; i < commands_.size(); ++i) {
        if (commands_[i][0] == '-') {
            if (!now.empty()) {
                NewCommand(now);
                now.clear();
            }
        }
        now.push_back(commands_[i]);
    }
    NewCommand(now);
    for (const auto &req : req_) {
        if (!command_vec_.count(req)) {
            throw exceptions::RequiredArgumentNotFound(req);
        }
    }
}
void ArgParser::SetRequired(const std::string &s) {
    req_.insert(s);
}
void ArgParser::SetStatus(const std::string &s, const ArgParser::CntType &t, const int &minimal) {
    cnt_[s] = t;
    if (t == MULTIPLE) {
        min_cnt_[s] = minimal;
    }
}
ArgParser::ArgParser(const std::vector<std::string> &commands) : commands_(commands) {
}
ArgParser::ArgParser(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        commands_.push_back(argv[i]);
    }
}
void ArgParser::NewCommand(const std::vector<std::string> &now) {
    std::string clear_cmd;
    bool started = false;
    for (auto c : now[0]) {
        if (c != '-') {
            started = true;
        }
        if (started) {
            clear_cmd += c;
        }
    }
    size_t cnt = now.size() - 1;
    if (cnt_.count(clear_cmd)) {
        switch (cnt_[clear_cmd]) {
            case ZERO:
                if (cnt != 0) {
                    throw exceptions::InvalidParameterCount(clear_cmd, cnt, 0);
                }
                break;
            case ONE:
                if (cnt != 1) {
                    throw exceptions::InvalidParameterCount(clear_cmd, cnt, 1);
                }
                break;
            case MULTIPLE:
                if (min_cnt_.count(clear_cmd) && cnt < min_cnt_[clear_cmd]) {
                    throw exceptions::InvalidMinimalParameterCount(clear_cmd, cnt, min_cnt_[clear_cmd]);
                }
                break;
        }
    }
    command_vec_[clear_cmd] = now;
}
bool ArgParser::CheckArgument(const std::string &s) {
    return command_vec_.count(s);
}

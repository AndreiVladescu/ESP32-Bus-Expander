#pragma once

#include <string>

class TerminalCommand {
public:
    TerminalCommand(const std::string& root = "", const std::string& sub = "", const std::string& args = "")
        : root(root), subcommand(sub), args(args) {}

    std::string getRoot() const { return root; }
    void setRoot(const std::string& r) { root = r; }

    std::string getSubcommand() const { return subcommand; }
    void setSubcommand(const std::string& s) { subcommand = s; }

    std::string getArgs() const { return args; }
    void setArgs(const std::string& a) { args = a; }

private:
    std::string root;
    std::string subcommand;
    std::string args;
};

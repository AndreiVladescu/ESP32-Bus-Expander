#pragma once
#include <string>
#include <vector>
#include <Models/TerminalCommand.h>

class TerminalCommandTransformer {
public:
    TerminalCommand transform(const std::string& raw) const;
    std::vector<TerminalCommand> transformMany(const std::string& raw) const;
    std::vector<TerminalCommand> transformRepeatCommand(const std::string& raw) const;
    bool isPipelineCommand(const std::string& raw) const;
    bool isMacroCommand(const std::string& raw) const;
    bool isBuiltinCommand(const std::string& raw) const;
    bool isRepeatCommand(const std::string& raw) const;
    bool isGlobalCommand(const TerminalCommand& cmd) const; 
    bool isScreenCommand(const TerminalCommand& cmd) const;
private:
    std::string normalizeRaw(const std::string& raw) const;
    void autoCorrectRoot(TerminalCommand& cmd) const;
    void autoCorrectSubCommand(TerminalCommand& cmd) const;
    int scoreTightEditDistance(const std::string& a, const char* b) const;

    // aliases for protocols
    struct Alias { const char* from; const char* to; };
    inline static const Alias aliases[] = {
        {"5ghz",   "wifi"},

        {nullptr, nullptr}
    };
};

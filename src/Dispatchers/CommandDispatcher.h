#pragma once

#include <string>
#include <vector>
#include "Models/TerminalCommand.h"
#include "Enums/ModeEnum.h"
#include "Providers/DependencyProvider.h"
#include "Interfaces/ITerminalView.h"

class CommandDispatcher {
public:
    // Constructor
    explicit CommandDispatcher(DependencyProvider& provider);

    // Initialize
    void setup();

    // Main loop that handles user input
    void run();

    // Process raw user action
    void dispatch(const std::string& raw);

private:
    size_t MAX_ALLOWED_COMMAND_LENGTH = 512;
    DependencyProvider& provider;
    GlobalState& state = GlobalState::getInstance();

    // Handle a command
    void dispatchCommand(const TerminalCommand& cmd);

    // Switch to a different mode
    void setCurrentMode(ModeEnum newMode);

    // Release mode resources if needed
    void releaseMode(ModeEnum currentMode, ModeEnum newMode);

    // Read user input with cursor support
    std::string getUserAction();

    // Handle ANSI escape sequences (arrows, etc.)
    bool handleEscapeSequence(char c, std::string& inputLine, size_t& cursorIndex, const std::string& mode);

    // Handle Tab key for autocompletion
    bool handleTabCompletion(char c, std::string& inputLine, size_t& cursorIndex, const std::string& mode);

    // Handle backspace logic
    bool handleBackspace(char c, std::string& inputLine, size_t& cursorIndex, const std::string& mode);

    // Handle printable characters insertion
    bool handlePrintableChar(char c, std::string& inputLine, size_t& cursorIndex, const std::string& mode);

    // Handle Enter key and dispatch line
    bool handleEnterKey(char c, const std::string& inputLine);
};

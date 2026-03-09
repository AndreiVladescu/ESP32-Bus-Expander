#pragma once

/*
The DependencyProvider is responsible for creating, holding,
and injecting shared instances of core components
(such as services, controllers, etc) throughout the application.
*/

#include "Services/WifiService.h"
#include "Transformers/ArgTransformer.h"
#include "Transformers/TerminalCommandTransformer.h"
#include "Managers/UserInputManager.h"
#include "Managers/CommandHistoryManager.h"
#include "Controllers/WifiController.h"


class DependencyProvider
{
public:
    DependencyProvider(ITerminalView& terminalView, IInput& terminalInput);

    // Core
    ITerminalView& getTerminalView();
    IInput& getTerminalInput();

    // Services
    WifiService &getWifiService();
    WifiOpenScannerService &getWifiOpenScannerService();

    // Controllers
    WifiController &getWifiController();

    // Transformers
    ArgTransformer &getArgTransformer();
    TerminalCommandTransformer &getCommandTransformer();

    // Managers
    UserInputManager &getUserInputManager();
    CommandHistoryManager &getCommandHistoryManager();

    // Disable
    void disableAllProtocols();

private:
    // Core components
    ITerminalView& terminalView;
    IInput& terminalInput;

    // Services
    WifiService wifiService;
    WifiOpenScannerService wifiOpenScannerService;
    LittleFsService littleFsService;
    NvsService nvsService;

    // Controllers
    WifiController wifiController;

    // Transformers
    ArgTransformer argTransformer;
    TerminalCommandTransformer commandTransformer;

    // Managers
    CommandHistoryManager commandHistoryManager;
    UserInputManager userInputManager;
};
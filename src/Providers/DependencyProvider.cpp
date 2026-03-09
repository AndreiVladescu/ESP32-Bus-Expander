#include "DependencyProvider.h"

DependencyProvider::DependencyProvider(ITerminalView& terminalView, IInput& terminalInput)
    : 
      // Core components
      terminalView(terminalView),
      terminalInput(terminalInput),

      // Services
      wifiService(),
      wifiOpenScannerService(),
      nvsService(),
      littleFsService(),

      // Transformers
      argTransformer(),

      // Managers
      commandHistoryManager(),
      userInputManager(terminalView, terminalInput, argTransformer),

      // Controllers
      wifiController(terminalView, terminalInput, wifiService, wifiOpenScannerService, littleFsService, nvsService, argTransformer, userInputManager)

{
}

// Core
ITerminalView& DependencyProvider::getTerminalView() { return terminalView; }
IInput& DependencyProvider::getTerminalInput() { return terminalInput; }

// Services
WifiService &DependencyProvider::getWifiService() { return wifiService; }
WifiOpenScannerService &DependencyProvider::getWifiOpenScannerService() { return wifiOpenScannerService; }

// Controllers
WifiController &DependencyProvider::getWifiController() { return wifiController; }

// Transformers
ArgTransformer &DependencyProvider::getArgTransformer() { return argTransformer; }
TerminalCommandTransformer &DependencyProvider::getCommandTransformer() { return commandTransformer; }

// Managers
CommandHistoryManager &DependencyProvider::getCommandHistoryManager() { return commandHistoryManager; }
UserInputManager &DependencyProvider::getUserInputManager() { return userInputManager; }

// Disable interfaces
void DependencyProvider::disableAllProtocols()
{
}

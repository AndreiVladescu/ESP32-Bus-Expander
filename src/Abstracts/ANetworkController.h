#pragma once

#include <Arduino.h>
#include <string>
#include "Interfaces/ITerminalView.h"
#include "Interfaces/IInput.h"
#include "Services/WifiService.h"
#include "Services/WifiOpenScannerService.h"
#include "Services/NmapService.h"
#include "Services/ICMPService.h"
#include "Services/NvsService.h"
#include "Services/HttpService.h"
#include "Services/ModbusService.h"
#include "Services/LittleFsService.h"
#include "Transformers/ArgTransformer.h"
#include "Transformers/JsonTransformer.h"
#include "Managers/UserInputManager.h"
#include "States/GlobalState.h"
#include "Models/TerminalCommand.h"
#include "Shells/ModbusShell.h"

class ANetworkController {
public:
    ANetworkController(
        ITerminalView& terminalView,
        IInput& terminalInput,
        WifiService& wifiService,
        WifiOpenScannerService& wifiOpenScannerService,
        LittleFsService& littleFsService,
        NvsService& nvsService,
        ArgTransformer& argTransformer,
        UserInputManager& userInputManager,
        NmapService& nmapService,
        ICMPService& icmpService,
        HttpService& httpService,
        JsonTransformer& jsonTransformer,
        ModbusShell& modbusShell
    );

protected:
    void handleNmap(const TerminalCommand& cmd);
    void handlePing(const TerminalCommand& cmd);
    void handleDiscovery(const TerminalCommand& cmd);
    void handleModbus(const TerminalCommand& cmd);

    // HTTP
    void handleHttp(const TerminalCommand &cmd);
    void handleHttpGet(const TerminalCommand &cmd);
    void handleHttpAnalyze(const TerminalCommand &cmd);
    
    // Lookup
    void handleLookup(const TerminalCommand& cmd);
    void handleLookupMac(const TerminalCommand& cmd);
    void handleLookupIp(const TerminalCommand& cmd);


protected:
    ITerminalView&     terminalView;
    IInput&            terminalInput;

    WifiService&       wifiService;

    NvsService&        nvsService;

    WifiOpenScannerService& wifiOpenScannerService;
    NmapService&       nmapService;
    ICMPService&       icmpService;
    HttpService&       httpService;
    LittleFsService&   littleFsService;

    ModbusShell&       modbusShell;

    ArgTransformer&    argTransformer;
    JsonTransformer&   jsonTransformer;
    UserInputManager&  userInputManager;
    GlobalState&       globalState = GlobalState::getInstance();
};

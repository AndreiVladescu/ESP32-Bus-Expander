#pragma once

#include <Arduino.h>
#include <string>
#include <Interfaces/ITerminalView.h>
#include <States/GlobalState.h>

class SerialTerminalView : public ITerminalView {
public:

    void initialize() override;
    void welcome() override;
    void print(const std::string& text) override;
    void print(const uint8_t data) override;
    void println(const std::string& text) override;
    void printPrompt(const std::string& mode = "HIZ") override;
    void clear() override;
    void waitPress() override;
    void setBaudrate(unsigned long baudrate);
    
private:
    unsigned long baudrate = BAUD;
    const uint8_t rxPin = RX_PIN;
    const uint8_t txPin = TX_PIN;
};

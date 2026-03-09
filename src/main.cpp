#ifndef UNIT_TEST

#include "Providers/DependencyProvider.h"
#include "Dispatchers/CommandDispatcher.h"
#include "Views/SerialTerminalView.h"
#include "Inputs/SerialTerminalInput.h"

void setup() {    
    // Serial View/Input
    SerialTerminalView serialView;
    SerialTerminalInput serialInput;

    DependencyProvider provider(serialView,  serialInput);
    CommandDispatcher dispatcher(provider);
    dispatcher.setup();
    dispatcher.run(); // Forever
}

void loop() {
    // Empty as all logic is handled in dispatcher
}

#endif

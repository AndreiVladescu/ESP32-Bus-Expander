#ifndef NVS_SERVICE_H
#define NVS_SERVICE_H

#include <Preferences.h>
#include <string>
#include "States/GlobalState.h"

class NvsService {
public:
    ~NvsService();

    // Open/Close namespace
    void open();
    void close();
    bool hasKey(const std::string& key);

    // Read/write string
    void saveString(const std::string& key, const std::string& value);
    std::string getString(const std::string& key, const std::string& defaultValue = "");

    // Read/write int
    void saveInt(const std::string& key, int value);
    int getInt(const std::string& key, int defaultValue = 0);

    // Utils
    void remove(const std::string& key);
    void clearNamespace();

private:
    Preferences preferences;
    GlobalState& globalState = GlobalState::getInstance();
};

#endif // NVS_SERVICE_H

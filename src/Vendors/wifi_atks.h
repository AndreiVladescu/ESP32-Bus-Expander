#ifndef __WIFI_ATKS_H__
#define __WIFI_ATKS_H__

#include <WiFi.h>

// Random SSID if no ssid provided
void beaconCreate(const char* ssid = "", uint8_t channel = 0, int spam=false);

#endif

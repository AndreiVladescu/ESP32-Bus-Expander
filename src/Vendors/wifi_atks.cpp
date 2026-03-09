// Borrowed from https://github.com/justcallmekoko/ESP32Marauder/
// Learned from https://github.com/risinek/esp32-wifi-penetration-tool/
// Arduino IDE needs to be tweeked to work, follow the instructions:
// https://github.com/justcallmekoko/ESP32Marauder/wiki/arduino-ide-setup But change the file in:
// C:\Users\<YOur User>\AppData\Local\Arduino15\packages\m5stack\hardware\esp32\2.0.9
#include "wifi_atks.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "vector"
#include <Arduino.h>


void generateRandomWiFiMac(uint8_t *mac) {
    for (int i = 1; i < 6; i++) { mac[i] = random(0, 255); }
}

char emptySSID[32];
const char* Beacons[] PROGMEM = {"Mom Use This One\n",
                                "Abraham Linksys\n",
                                "Benjamin FrankLAN\n",
                                "Martin Router King\n",
                                "John Wilkes Bluetooth\n",
                                "Pretty Fly for a Wi-Fi\n",
                                "Bill Wi the Science Fi\n",
                                "I Believe Wi Can Fi\n",
                                "Tell My Wi-Fi Love Her\n",
                                "No More Mister Wi-Fi\n",
                                "LAN Solo\n",
                                "The LAN Before Time\n",
                                "Silence of the LANs\n",
                                "House LANister\n",
                                "Winternet Is Coming\n",
                                "Ping's Landing\n",
                                "The Ping in the North\n",
                                "This LAN Is My LAN\n",
                                "Get Off My LAN\n",
                                "The Promised LAN\n",
                                "The LAN Down Under\n",
                                "FBI Surveillance Van 4\n",
                                "Area 51 Test Site\n",
                                "Drive-By Wi-Fi\n",
                                "Planet Express\n",
                                "Wu Tang LAN\n",
                                "Darude LANstorm\n",
                                "Never Gonna Give You Up\n",
                                "Hide Yo Kids, Hide Yo Wi-Fi\n",
                                "Loading…\n",
                                "Searching…\n",
                                "VIRUS.EXE\n",
                                "Virus-Infected Wi-Fi\n",
                                "Starbucks Wi-Fi\n",
                                "Text 64ALL for Password\n",
                                "The Password Is 1234\n",
                                "Free Public Wi-Fi\n",
                                "No Free Wi-Fi Here\n",
                                "Get Your Own Damn Wi-Fi\n",
                                "It Hurts When IP\n",
                                "Dora the Internet Explorer\n",
                                "404 Wi-Fi Unavailable\n",
                                "Porque-Fi\n",
                                "Titanic Syncing\n",
                                "Test Wi-Fi Please Ignore\n",
                                "Drop It Like It's Hotspot\n",
                                "Life in the Fast LAN\n",
                                "The Creep Next Door\n",
                                "Ye Olde Internet\n"};

// goes to next channel
const uint8_t channels[] = {
    36, 40, 44, 48,
    52, 56, 60, 64,
    100, 104, 108, 112,
    116, 120, 124, 128,
    132, 136, 140, 144,
    149, 153, 157, 161, 165
}; // 5 GHz Wi-Fi channels
const size_t channelCount = sizeof(channels) / sizeof(channels[0]);
uint8_t channelIndex = 0;
uint8_t wifi_channel = 1;

void nextChannel() {

    if (channelCount <= 1) return;

    uint8_t ch = channels[channelIndex];

    channelIndex++;
    if (channelIndex >= channelCount)
        channelIndex = 0;

    if (ch != wifi_channel) {
        wifi_channel = ch;
        esp_wifi_set_channel(wifi_channel, WIFI_SECOND_CHAN_NONE);
    }
}

void setChannel(uint8_t ch) {
    esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
}

void beaconCreate(const char* ssid, uint8_t channel, int spam) {

    // beacon frame definition
    uint8_t beaconPacket[109] = {/*  0 - 3  */ 0x80,
                                 0x00,
                                 0x00,
                                 0x00, // Type/Subtype: managment beacon frame
                                 /*  4 - 9  */ 0xFF,
                                 0xFF,
                                 0xFF,
                                 0xFF,
                                 0xFF,
                                 0xFF, // Destination: broadcast
                                 /* 10 - 15 */ 0x01,
                                 0x02,
                                 0x03,
                                 0x04,
                                 0x05,
                                 0x06, // Source
                                 /* 16 - 21 */ 0x01,
                                 0x02,
                                 0x03,
                                 0x04,
                                 0x05,
                                 0x06, // Source

                                 // Fixed parameters
                                 /* 22 - 23 */ 0x00,
                                 0x00, // Fragment & sequence number (will be done by the SDK)
                                 /* 24 - 31 */ 0x83,
                                 0x51,
                                 0xf7,
                                 0x8f,
                                 0x0f,
                                 0x00,
                                 0x00,
                                 0x00, // Timestamp
                                 /* 32 - 33 */ 0xe8,
                                 0x03, // Interval: 0x64, 0x00 => every 100ms - 0xe8, 0x03 => every 1s
                                 /* 34 - 35 */ 0x31,
                                 0x00, // capabilities Tnformation

                                 // Tagged parameters

                                 // SSID parameters
                                 /* 36 - 37 */ 0x00,
                                 0x20, // Tag: Set SSID length, Tag length: 32
                                 /* 38 - 69 */ 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20,
                                 0x20, // SSID

                                 // Supported Rates
                                 /* 70 - 71 */ 0x01,
                                 0x08,          // Tag: Supported Rates, Tag length: 8
                                 /* 72 */ 0x82, // 1(B)
                                 /* 73 */ 0x84, // 2(B)
                                 /* 74 */ 0x8b, // 5.5(B)
                                 /* 75 */ 0x96, // 11(B)
                                 /* 76 */ 0x24, // 18
                                 /* 77 */ 0x30, // 24
                                 /* 78 */ 0x48, // 36
                                 /* 79 */ 0x6c, // 54

                                 // Current Channel
                                 /* 80 - 81 */ 0x03,
                                 0x01,          // Channel set, length
                                 /* 82 */ 0x01, // Current Channel

                                 // RSN information
                                 /*  83 -  84 */ 0x30,
                                 0x18,
                                 /*  85 -  86 */ 0x01,
                                 0x00,
                                 /*  87 -  90 */ 0x00,
                                 0x0f,
                                 0xac,
                                 0x02,
                                 /*  91 -  92 */ 0x02,
                                 0x00,
                                 /*  93 - 100 */ 0x00,
                                 0x0f,
                                 0xac,
                                 0x04,
                                 0x00,
                                 0x0f,
                                 0xac,
                                 0x04, /*Fix: changed 0x02(TKIP) to 0x04(CCMP) is default. WPA2 with TKIP not
                                          supported by many devices*/
                                 /* 101 - 102 */ 0x01,
                                 0x00,
                                 /* 103 - 106 */ 0x00,
                                 0x0f,
                                 0xac,
                                 0x02,
                                 /* 107 - 108 */ 0x00,
                                 0x00};

    // temp variables
    int i = 0;
    int j = 0;
    char tmp;
    uint8_t macAddr[6];
    int ssidLen = strlen(ssid);
    char finalSsid[33];

    if (ssidLen == 0) {
        auto beaconSize = sizeof(Beacons) / sizeof(Beacons[0]);
        int randomIndex = random(0, beaconSize);
        strncpy(finalSsid, Beacons[randomIndex], sizeof(finalSsid) - 1);
        finalSsid[sizeof(finalSsid) - 1] = '\0';
    } else {
        strncpy(finalSsid, ssid, ssidLen - 1);
        finalSsid[ssidLen - 1] = '\0';
    }
    auto finalSsidLen = strlen(finalSsid);

    // go to next channel or set specific channel
    if (channel == 0) {
        nextChannel();
    } else {
        setChannel(channel);
        wifi_channel = channel;
    }
    
    // set MAC address
    generateRandomWiFiMac(macAddr);

    // write MAC address into beacon frame
    memcpy(&beaconPacket[10], macAddr, 6);
    memcpy(&beaconPacket[16], macAddr, 6);

    // reset SSID
    memcpy(&beaconPacket[38], emptySSID, 32);

    // write new SSID into beacon frame
    memcpy(&beaconPacket[38], finalSsid, finalSsidLen);
    // set channel for beacon frame
    beaconPacket[82] = wifi_channel;
    beaconPacket[34] = 0x31; // wpa

    // send packet
    for (int k = 0; k < 3; k++) {
        esp_wifi_80211_tx(WIFI_IF_STA, beaconPacket, sizeof(beaconPacket), 0);
        if (!spam) vTaskDelay(1 / portTICK_RATE_MS);
    }
}
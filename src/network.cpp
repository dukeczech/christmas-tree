#include <WiFi.h>
#include <ESPmDNS.h>
#include "network.h"


Network::Network()
{
}

bool Network::init(String ssid, String pass)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());

    while(WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Use mdns for host name resolution
    // http://esp32.local
    if(!MDNS.begin("esp32"))
    {
        Serial.println("Error setting up MDNS responder!");
        while(1)
        {
            delay(1000);
            break;
        }
    }
    Serial.println("mDNS responder started");

    return true;
}

String Network::getLocalIP() const
{
    return WiFi.localIP().toString();
}

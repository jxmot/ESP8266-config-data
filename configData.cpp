//////////////////////////////////////////////////////////////////////////////
/*
    configData.cpp
    
    This class makes use of SPIFFS, it expects the file `config.dat` to be
    present. The `config.dat` must properly formatted as JSON.
    
    This class must also be aware of the contents of the `config.dat` file.
*/
#include "FS.h"
#include "configData.h"
#include <ArduinoJson.h>

// Sources of information that I found useful when creating this code -
// 
// http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html
// https://github.com/esp8266/arduino-esp8266fs-plugin
//
// http://www.instructables.com/id/Using-ESP8266-SPIFFS/
//////////////////////////////////////////////////////////////////////////////
/*
    
*/
configData::configData() 
{
    error = 0;
    
    SPIFFS.begin();
    File cfgData = SPIFFS.open("/config.dat", "r");

    // check to see if the file opened...
    if (!cfgData) {
        // it didn't open, note the likely error.
        error = -1;
        errmsg = "The configuration data file doesn't exist.";
    } else {
        size_t size = cfgData.size();
        if (size > 1024) {
            error = -1;
            errmsg = "Config file size is too large";
        } else {
            // Allocate a buffer to store contents of the file.
            std::unique_ptr<char[]> buf(new char[size]);

            // https://bblanchon.github.io/ArduinoJson/
            // 
            // We don't use String here because ArduinoJson library requires the input
            // buffer to be mutable. If you don't use ArduinoJson, you may as well
            // use configFile.readString instead.
            cfgData.readBytes(buf.get(), size);
            
            // Using the sample `data/config.dat` file where its contents are - 
            //      {"wifi-ssid":"your ssid here","wifi-pass":"your wifi password here","ser-baud":115200}
            // the tool found at - 
            //      https://bblanchon.github.io/ArduinoJson/assistant/
            // indicates a size of (131 + 90), we will determine the value 
            // programmatically - 
            const size_t bufferSize = JSON_OBJECT_SIZE(3) + 90;
            StaticJsonBuffer<bufferSize> jsonBuffer;
            
            JsonObject& json = jsonBuffer.parseObject(buf.get());
            
            if (!json.success()) {
                error = -1;
                errmsg = "Failed to parse config file";
            } else {
                /*
                    This is another place where you can modify things...
                    add, modifiy, or remove as needed.
                    
                    Data obtained should be saved locally, when `JsonObject`
                    goes out of scope it will be deallocated from memory.
                    
                    Don't rely on the object being retained in memory!
                */
                const char *tmp = json["wifi-ssid"];
                wifissid = String(tmp);
                tmp = json["wifi-pass"];
                wifipass = String(tmp);
                serbaud  = json["ser-baud"];
            }
        }
        cfgData.close();
    }
}

int configData::getError(String &s) 
{
    s = errmsg;
    return error;
}
//////////////////////////////////////////////////////////////////////////////
/*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in configData.h
*/
char *configData::getSSID()
{
    return (char *)wifissid.c_str();
}

String configData::getSSIDString()
{
    return wifissid;
}

char *configData::getPASS()
{
    return (char *)wifipass.c_str();
}

String configData::getPASSString()
{
    return wifipass;
}

int configData::getBAUD()
{
    return serbaud;
}

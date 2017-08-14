//////////////////////////////////////////////////////////////////////////////
/*
    esp8266-config-data.ino
    
    A demonstration of SPIFFS and using it as a method for containing
    and retreiving configuration data for ESP8266 applications.
    
    
*/
#include <ESP8266WiFi.h>

#include "configData.h"
#include "debugLog.h"

// These are global so that the rest of the application code can
// use them.
debugLog *dlog;
configData *cfgdat;

/*
    setup() - read the configuration file, and parse its (known) contents
    into member variables.
*/
void setup() {
    // a necessary delay...
    delay(300);

    // instantiate the `configData` object, during construction
    // it will read the configuration file and make its data 
    // availble.
    cfgdat = new configData();

    // let's check for errors before continuing...
    String errMsg;
    if(!cfgdat->getError(errMsg)) {
        // no errors!
        
        // set up the logger, typically sent out via Serial
        // but can be modified as needed.
        dlog = new debugLog(cfgdat->getBAUD());
    
        // just to prove we read something from the configuration file
        dlog->println();
        dlog->println(cfgdat->getSSIDString());
        dlog->println(cfgdat->getPASSString());
        dlog->println(cfgdat->getBAUD());

        WiFi.mode(WIFI_STA);
        // Use the functions that return `const char *` because
        // WiFi.begin() doesn't take String as an arg.
        WiFi.begin(cfgdat->getSSID(), cfgdat->getPASS());
    } else {
        // an error has occurred, the message will provide
        // additional information.
        dlog->println(errMsg);
    }

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        dlog->print(".");
    }

    dlog->println("");
    dlog->println("WiFi connected");  
    dlog->println("IP address: ");
    dlog->println(WiFi.localIP().toString());
}


void loop() {
    // while I was researching SPIFFS I read that calling 
    // yield() was necessary to allow flash memory operations
    // to occur.
    yield();
}


//////////////////////////////////////////////////////////////////////////////
/*
    debugLog.cpp
    
    A wrapper for making `Serial.print??()` calls. Allows for programmatic
    muting of output.
    
*/
#include <ESP8266WiFi.h>
#include "debugLog.h"

/*
    Use this constructor when you've already called
    `Serial.begin()`.
*/
debugLog::debugLog(bool mute)  {
    isMuted = mute;
}
 
/*
    Use this one when you want this class to 
    initialize serial communication.
*/
debugLog::debugLog(int baud, bool mute) {
    isMuted = mute;
    Serial.begin(baud);
}

/*
    Various output functions
*/
void debugLog::print(String message) {
    if(!isMuted) Serial.print(message);
}

void debugLog::print(int value) {
    if(!isMuted) Serial.print(value);
}

void debugLog::println(String message) {
    if(!isMuted) Serial.println(message);
}

void debugLog::println(int value) {
    if(!isMuted) Serial.println(value);
}

void debugLog::println() {
    if(!isMuted) Serial.println();
}

/*
    Mute control, toggle the current state, set it 
    explicitly, or retrieve the current mute setting.
*/
bool debugLog::togglemute() {
    isMuted = !isMuted;
    return isMuted;
}

bool debugLog::setmute(bool mute) {
    isMuted = mute;
    return isMuted;
}

bool debugLog::getmute() {
    return isMuted;
}


# ESP8266-config-data

* [Overview](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-overview)
    * [History](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-history)
* [Requirements](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-requirements)
    * [Flash Memory Tool](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-flash-memory-tool)
        * [Installation](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-installation)
* [Running the Application](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-running-the-application)
    * [Next Steps](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-next-steps)
* [Additional Notes](https://bitbucket.org/jxmot/esp8266-config-data/overview#markdown-header-additional-notes)

# Overview

This repository contains code intended for the ESP8266. Its purpose is to demonstrate how SPIFFS might be used for containing an application's configuration data. For example the data might include - 

* WiFi SSID and password
* The baud rate to use for console output
* API Keys for web services
* Server URI's
* And more!

## History

I was working on a project for the ESP8266 and decided that placing my *sensitive* information in a header or source file wasn't a good idea. The *sensitive* data was things like API keys and wifi logon information.

After some experimentation I determined that SPIFFS is exactly what I needed. And what you see in this repository was developed from my notes and experimentation. Think of what's here as a starting point for other ESP8266 applications.

# Requirements

You will need the following - 

* ESP8266 - I'm using a NodeMCU 1.0, and mine is a 12-E
* Arduino IDE - Installed and made ready for use with the ESP8266
    * In addition to being able to compile code for the ESP8266 you **will** need an IDE plug-in for downloading the file(s) to the ESP8266 *flash memory*.
    
## Flash Memory Tool

I dowloaded the most *recent* version of the plugin by going to <https://github.com/esp8266/arduino-esp8266fs-plugin> and clicking the "releases page" link in the README.

**NOTE :** I am running *Windows 10*. And this file, its instructions and any other information may or may not be influenced by that fact. Where possible I will note any windows specific items.

### Installation

There are some discrepancies in the available on-line sources in regards to *where* to place the plug-in's `jar` file. In *Windows* I've found that the plugin will work as long as it's in one of two places. They are - 

* `C:\Users\jim\Documents\Arduino` - you might have to create a `tools` folder here, and then copy the contents of the plugin zip file into it.

**OR**

* `C:\Program Files (x86)\Arduino\tools` - copy the contents of the plug-in zip file into this folder.

I've tested the plug-in separately in each of the locations and have had no issues.

# Running the Application

Start with an unmodified version of the code from this repository. Please use the following steps - 

1. Run the *Arduino IDE* and go to the *Tools* menu and find **`Flash Size:`** and choose **'4M (1M SPIFFS)'**.
2. Open the **ino** file in the *Arduino IDE* and upload it to the ESP8266. **Do not** open the serial monitor.
3. Then go to the *Tools* menu and click on **`ESP8266 Sketch Data Upload`**.

Your SPIFFS along with the file it contains will be uploaded to the ESP8266. After that has completed open the *serial monitor* and reset the ESP8266. 

You should see this in the serial monitor - 

```
your ssid here
your wifi password here
115200
```

## Next Steps

Let's edit the configuration data and change the SSID and password to something *usable*.

1. Edit the `config.dat` file, it's found in `/data`.
2. The contents currently look like this - 

`{"wifi-ssid":"your ssid here","wifi-pass":"your wifi password here","ser-baud":115200}`

Edit the file and change `"your ssid here"` and `"your wifi password here"` to match your SSID and passowd.

3. Save and close the file.
4. Run the *Arduino IDE* and go to the *Tools* menu and find **`Flash Size:`** and choose **'4M (1M SPIFFS)'**.
5. Open the **ino** file in the *Arduino IDE* and upload it to the ESP8266. **Do not** open the serial monitor.
6. Then go to the *Tools* menu and click on **`ESP8266 Sketch Data Upload`**.

After the SPIFFS has uploaded you can open the *serial monitor* and reset the ESP8266. You should now see something *like this* - 

```
[SSID]
[PASSWORD]
115200
..wifi evt: 3
.
WiFi connected
IP address: 
192.168.0.20
```

Where `[SSID]` and `[PASSWORD]` are the values you edited in the `data/config.dat` file.

# Additional Notes

* **`configData.cpp`** - A sizable portion of this code came from one or more examples that I found online. I've made some modifications to tailor the code to my needs. However there are a couple of *specific* lines where I left the code "as-is".
    * `line 38: if (size > 1024)` - This checks the size of the file that has been opened. This check for `(size > 1024)` was left as I found it. I'm not sure if there is any size limits other than not over running the capacity of the chosen SPIFFS (*I'm using 1meg*).
    * `line 51: StaticJsonBuffer<200> jsonBuffer;` - According to the **ArduinoJson** documentation (<https://bblanchon.github.io/ArduinoJson/>) this line is utilizing memory allocated on the *stack*. An alternative would be to use the *heap*. At this point my preference is *heap*, although I've left the code as I found it.
    * Adjustments to the values (`1024` and `200`) will likely be needed if a larger JSON file is to be read and parsed. I don't have a way to *estimate* the value for memory allocation other than "Oops, something's not working".
    
I expect to revisit this repository and make changes as I learn more about **SPIFFS** and **ArduinoJson**.


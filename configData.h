#ifndef SETTINGS_H
#define SETTINGS_H

class configData {
    
    public:
        configData();
        int getError(String &s);

    private:
        int error;
        String errmsg;
 
    //////////////////////////////////////////////////////////////////////////
    /*
        This is one of the places where you would customize this class to be 
        used with your application specific configuration data.
        
        The other place is in configData.cpp
    */
    public:
        char *getSSID();
        String getSSIDString();
        
        char *getPASS();
        String getPASSString();
        
        int getBAUD();
        
    private:
        String wifissid;
        String wifipass;
        int serbaud;
};

#endif // SETTINGS_H


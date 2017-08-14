#ifndef DEBUG_H
#define DEBUG_H

class debugLog {
    public:
        // when Serial.begin() was call prior to instantiating this class
        debugLog(bool mute = false);
        // pass is a baud rate it Serial.begin() will be called
        debugLog(int baud, bool mute = false);
        // overload as needed....
        void print(String message);
        void print(int value);
        void println(String message);
        void println(int value);
        void println();
        
        bool togglemute();
        bool setmute(bool mute);
        bool getmute();

    private:
        bool isMuted;
};

#endif // DEBUG_H


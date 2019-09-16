#pragma once

#include <string>
#include "ofxSelflash.h"

using namespace fl2d;

class NetworkEvent : public flEvent {
    public:
        //接続
        static string CONNECTED;
        //切断
        static string DISCONNECTED;
        //受信
        static string RECEIVED;
        
    protected:
        
    private:
        string _data;
        string _remoteIp;
        int _remotePort;
        
    public:
        NetworkEvent(string type, string data, string remoteIp = "", int remotePort = 0);
        ~NetworkEvent();
        
        inline const string& data() { return _data; }
        inline string remoteIp() { return _remoteIp; }
        inline int remotePort() { return _remotePort; }
        
    protected:
        
    private:
    
};

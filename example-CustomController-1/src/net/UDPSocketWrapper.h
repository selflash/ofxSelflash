#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxSelflash.h"

#include "NetworkEvent.h"

using namespace fl2d;

class UDPSocketWrapper : public flEventDispatcher {
    public:
        static string getLocalAddress();
        
    protected:
        bool _usedListeners;
        
        //UDPソケット
        ofxUDPManager* _socket;
        
        bool _isBinded;
        bool _isConnected;
        
        string _localIp;
        int _localPort;
        string _targetIp;
        int _targetPort;
        string _remoteIp;
        int _remotePort;
        
        string _sendData;
        string _receivedData;
        
    private:
        
    public:
        UDPSocketWrapper();
        ~UDPSocketWrapper();
        
        virtual void setup();
        virtual void update();
        
        virtual bool bind(int port);
        virtual bool connect(string ip, int port);
        virtual int sendMessage(string message);
        virtual bool close();
        
        virtual bool isBinded();
        virtual bool isConnected();
        
        virtual string localIp();
        virtual int localPort();
        
        virtual string targetIp();
        virtual int targetPort();
        
        virtual string remoteIp();
        virtual int remotePort();
        
        virtual string sendData();
        virtual string receivedData();
        
    protected:
        
    private:
        void _addListeners();
        void _removeListeners();
        void _update(ofEventArgs& event) { update(); }
};

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxSelflash.h"

#include "UDPSocketWrapper.h"
#include "NetworkEvent.h"

class NetworkManager : public flEventDispatcher {
    //----------------------------------
    //Server
    public:
    
    protected:
    
    private:
        //サーバーソケット
        ofxTCPServer* _serverSocket;
    
        bool _enabledWithTCPServer;
        bool _isListenWithTCPServer;
        string _localIpWithTCPServer;
        int _localPortWithTCPServer;
        string _sendDataWithTCPServer;
        string _receivedDataWithTCPServer;
    
        //----------------------------------
        //アプリ1
        bool _connectedToApp1;
        int _app1ID;
        string _app1_Host;
        int _app1_Port;
        //アプリ2
        bool _connectedToApp2;
        int _app2ID;
        string _app2_Host;
        int _app2_Port;
        //アプリ3
        bool _connectedToApp3;
        int _app3ID;
        string _app3_Host;
        int _app3_Port;
        //----------------------------------
    
    public:
        void listenWithTCPServer(int port);
        bool sendMessageWithTCPServer(int clientID, const string& message);
        bool sendToAllWithTCPServer(const string& message);
        bool closeWithTCPServer();
    
        bool enabledWithTCPServer();
        bool isListenWithTCPServer();
        string localIpWithTCPServer();
        int localPortWithTCPServer();
        const string& sendDataWithTCPServer();
        const string& receivedDataWithTCPServer();
    
        //----------------------------------
        //アプリ1
        bool connectedToApp1();
        int app1ID();
        string app1_Host();
        int app1_Port();
        //アプリ1に接続を試みます
        bool connectToApp1(string ip = "", int port = -1, bool blocking = false);
        //アプリ1との切断
        bool disconnectToApp1();
        //アプリ1へメッセージ送信
        bool sendMessageToApp1(const string& message);
    
        //アプリ2
        bool connectedToApp2();
        int app2ID();
        string app2_Host();
        int app2_Port();
        //アプリ2と接続
        bool connectToApp2(string ip = "", int port = -1, bool blocking = false);
        //アプリ2と切断
        bool disconnectToApp2();
        //アプリ2へメッセージ送信
        bool sendMessageToApp2(const string& message);
    
        //アプリ3
        bool connectedToApp3();
        int app3ID();
        string app3_Host();
        int app3_Port();
        //アプリ3と接続
        bool connectToApp3(string ip = "", int port = -1, bool blocking = false);
        //アプリ3と切断
        bool disconnectToApp3();
        //アプリ3へメッセージ送信
        bool sendMessageToApp3(const string& message);
        //----------------------------------
    
    protected:
    
    private:
        void _updateServerSocket();
    //----------------------------------
    
    //----------------------------------
    //TCP
    public:
    
    protected:
    
    private:
        //TCPソケット
        ofxTCPClient* _tcpSocket;
    
        float _counter;
        int _connectTime;
        int _deltaTime;
        bool _enabled_TCP;
        bool _isConnected_TCP;
        string _targetIp_TCP;
        int _targetPort_TCP;
        bool _blocking_TCP;
        string _sendData_TCP;
        string _receivedData_TCP;
    
    public:
        bool connect_TCP(string ip = "", int port = -1, bool blocking = false);
        int sendMessage_TCP(const string& message);
        bool close_TCP();
    
        bool enabled_TCP();
        bool isConnected_TCP();
        string targetIp_TCP();
        int targetPort_TCP();
        const string& sendData_TCP();
        const string& receivedData_TCP();
    
    protected:
    
    private:
        void _updateTCPSocket();
    //----------------------------------
    
    //----------------------------------
    //UDP
    public:
    
    protected:
    
    private:
        vector<UDPSocketWrapper*> _udpSockets;
    
    public:
        vector<UDPSocketWrapper*>& udpSockets() { return _udpSockets; }
    
        //----------------------------------
        //UDPソケット
        bool bindWithUDP(int index, int port);
        bool connectWithUDP(int index, string ip, int port);
        int sendMessageWithUDP(int index, string message);
        bool closeWithUDP(int index);
    
        bool isBindedWithUDP(int index);
        bool isConnectedWithUDP(int index);
        string localIpWithUDP(int index);
        int localPortWithUDP(int index);
        string targetIpWithUDP(int index);
        int targetPortWithUDP(int index);
        string remoteIpWithUDP(int index);
        int remotePortWithUDP(int index);
        string sendDataWithUDP(int index);
        string receivedDataWithUDP(int index);
        //----------------------------------
    
        bool sendToAllWithUDP(string message);
        bool closeAllUDP();
    
    protected:
    
    private:
    //----------------------------------
    
    
    
    
    
    
    
    
    
    
    public:
    
    protected:
    
    private:
        bool _usedListeners;
    
    public:
        NetworkManager();
        virtual ~NetworkManager();
    
        virtual void setup(int totalNum = 1);
        virtual void update();
    
        virtual void close();
    
    protected:
    
    private:
        void _addListeners();
        void _removeListeners();
        void _update(ofEventArgs& event) { update(); };
    
        void _socketEventHandler(flEvent& event);
};


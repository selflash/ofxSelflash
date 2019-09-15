#include "NetworkEvent.h"

//--------------------------------------
//接続
string NetworkEvent::CONNECTED = "connected";
//切断
string NetworkEvent::DISCONNECTED = "disconnected";
//受信
string NetworkEvent::RECEIVED = "received";
//--------------------------------------

//--------------------------------------------------------------
//
NetworkEvent::NetworkEvent(string type, string data, string remoteIp, int remotePort):flEvent(type) {
    _data = data;
    _remoteIp = remoteIp;
    _remotePort = remotePort;
};

//--------------------------------------------------------------
//
NetworkEvent::~NetworkEvent() {
    _data = "";
    _remoteIp = "";
    _remotePort = 0;
};

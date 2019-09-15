#include "NetworkManager.h"

//--------------------------------------------------------------
//
bool NetworkManager::connectedToApp1() { return _connectedToApp1; }
//--------------------------------------------------------------
//
int NetworkManager::app1ID() { return _app1ID; }
//--------------------------------------------------------------
//
string NetworkManager::app1_Host() { return _app1_Host; }
//--------------------------------------------------------------
//
int NetworkManager::app1_Port() { return _app1_Port; }
//--------------------------------------------------------------
//アプリ1に接続を試みます
bool NetworkManager::connectToApp1(string ip, int port, bool blocking) {
    cout << "[NetworkManager]connectToApp1()" << endl;
    //    return connectTCPSocket(ip, port, blocking);
    return true;
}
//--------------------------------------------------------------
//アプリ1との切断
bool NetworkManager::disconnectToApp1() {
    cout << "[NetworkManager]disconnectToApp1()" << endl;
    //    return closeTCPSocket();
    return true;
}
//--------------------------------------------------------------
//アプリ1へメッセージ送信
bool NetworkManager::sendMessageToApp1(const string& message) {
    cout << "[NetworkManager]sendMessageToKinectApp()" << endl;
    if(!_connectedToApp1) return false;
    return sendMessageWithTCPServer(_app1ID, message);
}

//--------------------------------------------------------------
//
bool NetworkManager::connectedToApp2() { return _connectedToApp2; }
//--------------------------------------------------------------
//
int NetworkManager::app2ID() { return _app2ID; }
//--------------------------------------------------------------
//
string NetworkManager::app2_Host() { return _app2_Host; }
//--------------------------------------------------------------
//
int NetworkManager::app2_Port() { return _app2_Port; }
//--------------------------------------------------------------
//アプリ2に接続を試みます
bool NetworkManager::connectToApp2(string ip, int port, bool blocking) {
    cout << "[NetworkManager]connectToApp2(" << ip << ", " << port << ")" << endl;
    return connect_TCP(ip, port, blocking);
}
//--------------------------------------------------------------
//アプリ2との切断
bool NetworkManager::disconnectToApp2() {
    cout << "[NetworkManager]disconnectToApp2()" << endl;
    return close_TCP();
}
//--------------------------------------------------------------
//アプリ2へメッセージ送信
bool NetworkManager::sendMessageToApp2(const string& message) {
    cout << "[NetworkManager]sendMessageToApp2()" << endl;
    if(!_connectedToApp2) return false;
    return sendMessageWithTCPServer(_app2ID, message);
}

//--------------------------------------------------------------
//
bool NetworkManager::connectedToApp3() { return _connectedToApp3; }
//--------------------------------------------------------------
//
int NetworkManager::app3ID() { return _app3ID; }
//--------------------------------------------------------------
//
string NetworkManager::app3_Host() { return _app3_Host; }
//--------------------------------------------------------------
//
int NetworkManager::app3_Port() { return _app3_Port; }
//--------------------------------------------------------------
//アプリ3に接続を試みます
//bool NetworkManager::connectToApp3(string& ip, int& port, bool& blocking) {
//    cout << "[NetworkManager]connectToApp3()" << endl;
////    return connectTCPSocket(ip, port, blocking);
//}
//--------------------------------------------------------------
//アプリ3との切断
//bool NetworkManager::disconnectToApp3() {
//    cout << "[NetworkManager]disconnectToApp3()" << endl;
////    return closeTCPSocket();
//}
//--------------------------------------------------------------
//アプリ3へメッセージ送信
bool NetworkManager::sendMessageToApp3(const string& message) {
    cout << "[NetworkManager]sendMessageToApp3()" << endl;
    if(!_connectedToApp3) return false;
    return sendMessageWithTCPServer(_app3ID, message);
}




















//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//コンストラクタ
NetworkManager::NetworkManager() {
    //    debug(true);
    cout << "[NetworkManager]NetworkManager()" << endl;
    _target = this;
    
    //--------------------------------------
    //サーバー
    _serverSocket = NULL;
    
    _enabledWithTCPServer = false;
    _isListenWithTCPServer = false;
    _localIpWithTCPServer = "";
    _localPortWithTCPServer = 0;
    
    _connectedToApp1 = false;
    _app1ID = -1;
    _app1_Host = "-";
    _app1_Port = 0;
    
    _connectedToApp2 = false;
    _app2ID = -1;
    _app2_Host = "-";
    _app2_Port = 0;
    
    _connectedToApp3 = false;
    _app3ID = -1;
    _app3_Host = "-";
    _app3_Port = 0;
    //--------------------------------------
    
    //--------------------------------------
    //TCPソケット
    _tcpSocket = NULL;
    
    _enabled_TCP = false;
    _isConnected_TCP = false;
    _targetIp_TCP = "";
    _targetPort_TCP = 0;
    _blocking_TCP = false;
    _sendData_TCP = "";
    _receivedData_TCP = "";
    //--------------------------------------
    
    //--------------------------------------
    //UDPソケット
    
    //--------------------------------------
    
    _usedListeners = false;
    _addListeners();
}

//--------------------------------------------------------------
//デストラクタ
NetworkManager::~NetworkManager() {
    cout << "[NetworkManager]~NetworkManager()" << endl;
    _target = NULL;
    
    _removeListeners();
    _usedListeners = false;
    
    //--------------------------------------
    //サーバー
    delete _serverSocket;
    _serverSocket = NULL;
    _enabledWithTCPServer = false;
    _isListenWithTCPServer = false;
    _localIpWithTCPServer = "";
    _localPortWithTCPServer = 0;
    
    _connectedToApp1 = false;
    _app1ID = -1;
    _app1_Host = "";
    _app1_Port = 0;
    
    _connectedToApp2 = false;
    _app2ID = -1;
    _app2_Host = "";
    _app2_Port = 0;
    
    _connectedToApp3 = false;
    _app3ID = -1;
    _app3_Host = "";
    _app3_Port = 0;
    //--------------------------------------
    
    //--------------------------------------
    //TCPソケット
    delete _tcpSocket;
    _tcpSocket = NULL;
    
    _enabled_TCP = false;
    _isConnected_TCP = false;
    _targetIp_TCP = "";
    _targetPort_TCP = 0;
    _blocking_TCP = false;
    _sendData_TCP = "";
    _receivedData_TCP = "";
    //--------------------------------------
    
    //--------------------------------------
    //UDPソケット
    closeAllUDP();
    
    int i; int l;
    l = _udpSockets.size();
    for(i = 0; i < l; i++) {
        delete _udpSockets[i];
    }
    _udpSockets.clear();
    //--------------------------------------
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//初期化
void NetworkManager::setup(int totalNum) {
    cout << "[NetworkManager]setup(" << totalNum << ")" << endl;
    
    //    //--------------------------------------
    //    //サーバー
    //    _serverSocket = new ofxTCPServer();
    //    //区切り文字を設定。クライアントとサーバーで揃えないといけない
    //    _serverSocket->setMessageDelimiter(";");
    //    //--------------------------------------
    //    //--------------------------------------
    //    //TCPソケット
    //    _tcpSocket = new ofxTCPClient();
    //    //区切り文字を設定。クライアントとサーバーで揃えないといけない
    //    _tcpSocket->setMessageDelimiter(";");
    //    _tcpSocket->setVerbose(true);
    //    //--------------------------------------
    //--------------------------------------
    //UDPソケット
    int l = totalNum;
    for(int i = 0; i < l; i++) {
        UDPSocketWrapper* udpSocket = new UDPSocketWrapper();
        udpSocket->setup();
        udpSocket->addEventListener(NetworkEvent::RECEIVED, this, &NetworkManager::_socketEventHandler);
        _udpSockets.push_back(udpSocket);
    }
    //--------------------------------------
    //    cout << "_udpSockets.size() = " << _udpSockets.size() << endl;
}

//--------------------------------------------------------------
//更新
void NetworkManager::update() {
    //    cout << "[NetworkManager]update()" << endl;
    
    if(_enabledWithTCPServer) _updateServerSocket();
    if(_enabled_TCP) _updateTCPSocket();
}

//==============================================================
// PUBLIC METHOD
//==============================================================

//--------------------------------------------------------------
//
void NetworkManager::close() {
    cout << "[NetworkManager]close()" << endl;
    
    if(_enabledWithTCPServer) closeWithTCPServer();
    if(_enabled_TCP) close_TCP();
    
    closeAllUDP();
}



















//==============================================================
// SERVER SOCKET API
//==============================================================

//--------------------------------------------------------------
//接続待ち
void NetworkManager::listenWithTCPServer(int port) {
    cout << "[NetworkManager]listenWithTCPServer()" << endl;
    
    _localPortWithTCPServer = port;
    _isListenWithTCPServer = _serverSocket->setup(_localPortWithTCPServer);
    
    if(_isListenWithTCPServer) _enabledWithTCPServer = true;
    
    //return _isListenWithTCPServer;
}

//--------------------------------------------------------------
//メッセージ送信
bool NetworkManager::sendMessageWithTCPServer(int clientID, const string& message) {
    cout << "[NetworkManager]sendMessageWithTCPServer()" << endl;
    _sendDataWithTCPServer = message;
    return _serverSocket->send(clientID, _sendDataWithTCPServer);
}

//--------------------------------------------------------------
//メッセージ送信
bool NetworkManager::sendToAllWithTCPServer(const string& message) {
    cout << "[NetworkManager]sendToAllWithTCPServer()" << endl;
    
    int i; int l;
    l = _serverSocket->getLastID();
    for(i = 0; i < l; i++) {
        //--------------------------------------
        //接続確認
        if(_serverSocket->isClientConnected(i)) {
            _serverSocket->send(i, message);
        }
    }
    
    return true;
}

//--------------------------------------------------------------
//切断
bool NetworkManager::closeWithTCPServer() {
    cout << "[NetworkManager]closeWithTCPServer()" << endl;
    
    for(int i = 0; i < _serverSocket->getLastID(); i++) {
        //if(server.isClientConnected(i)) {
        _serverSocket->disconnectClient(i);
        //}
    }
    
    bool b = _serverSocket->close();
    
    _enabledWithTCPServer = false;
    
    return b;
}

//--------------------------------------------------------------
//
bool NetworkManager::enabledWithTCPServer() { return _enabledWithTCPServer; }
//--------------------------------------------------------------
//
bool NetworkManager::isListenWithTCPServer() { return _isListenWithTCPServer; }
//--------------------------------------------------------------
//
string NetworkManager::localIpWithTCPServer() { return _localIpWithTCPServer; }
//--------------------------------------------------------------
//
int NetworkManager::localPortWithTCPServer() { return _localPortWithTCPServer; }
//--------------------------------------------------------------
//
const string& NetworkManager::sendDataWithTCPServer() { return _sendDataWithTCPServer; }
//--------------------------------------------------------------
//
const string& NetworkManager::receivedDataWithTCPServer() { return _receivedDataWithTCPServer; }




















//==============================================================
// TCP SOCKET API
//==============================================================

//--------------------------------------------------------------
//TCPソケットの接続を試みます
bool NetworkManager::connect_TCP(string ip, int port, bool blocking) {
    cout << "[NetworkManager]connect_TCP(" << ip << ", " << port << ", " << blocking << ")" << endl;
    _targetIp_TCP = ip == "" ? _targetIp_TCP : ip;
    _targetPort_TCP = port == -1 ? _targetPort_TCP : port;
    _blocking_TCP = blocking;
    
    _isConnected_TCP = false;
    
    try {
        _isConnected_TCP = _tcpSocket->setup(_targetIp_TCP, _targetPort_TCP, _blocking_TCP);
    } catch(...) {
        _isConnected_TCP = false;
    }
    
    _enabled_TCP = true;
    
    return _isConnected_TCP;
}
//--------------------------------------------------------------
//TCPソケットでメッセージ送信
int NetworkManager::sendMessage_TCP(const string& message) {
    if(!_isConnected_TCP) return 0;
    _sendData_TCP = message;
    return _tcpSocket->send(_sendData_TCP);
}
//--------------------------------------------------------------
//TCPソケットを切断
bool NetworkManager::close_TCP() {
    cout << "[NetworkManager]close_TCP()" << endl;
    bool b = _tcpSocket->close();
    
    if(b) {
        _enabled_TCP = false;
        _isConnected_TCP = false;
    }
    return b;
}

//--------------------------------------------------------------
//
bool NetworkManager::enabled_TCP() { return _enabled_TCP; }
//--------------------------------------------------------------
//
bool NetworkManager::isConnected_TCP() { return _isConnected_TCP; }
//--------------------------------------------------------------
//
string NetworkManager::targetIp_TCP() { return _targetIp_TCP; }
//--------------------------------------------------------------
//
int NetworkManager::targetPort_TCP() { return _targetPort_TCP; }
//--------------------------------------------------------------
//
const string& NetworkManager::sendData_TCP() { return _sendData_TCP; }
//--------------------------------------------------------------
//
const string& NetworkManager::receivedData_TCP() { return _receivedData_TCP; }




















//==============================================================
// UDP SOCKET API
//==============================================================

//--------------------------------------------------------------
//バインド
bool NetworkManager::bindWithUDP(int index, int port) {
    cout << "[NetworkManager]bindWithUDP(" << index << ", " << port << ")" << endl;
    if(!_udpSockets[index]) return false;
    return _udpSockets[index]->bind(port);
}

//--------------------------------------------------------------
//リモートPCとの接続
bool NetworkManager::connectWithUDP(int index, string ip, int port) {
    cout << "[NetworkManager]connectWithUDP(" << index << ", " << ip << ", " << port << ")" << endl;
    //_udpSocket->Connect("127.0.0.1", 9000);
    if(!_udpSockets[index]) return false;
    return _udpSockets[index]->connect(ip, port);
}
//--------------------------------------------------------------
//UDPソケットでメッセージ送信
int NetworkManager::sendMessageWithUDP(int index, string message) {
    cout << "[NetworkManager]sendMessageWithUDP(" << index << ", " << message << ")" << endl;
    if(!_udpSockets[index]) return 0;
    return _udpSockets[index]->sendMessage(message);
}
//--------------------------------------------------------------
//UDPソケットを切断
bool NetworkManager::closeWithUDP(int index) {
    cout << "[NetworkManager]closeWithUDP(" << index << ")" << endl;
    if(!_udpSockets[index]) return false;
    return _udpSockets[index]->close();
}
//--------------------------------------------------------------
//
bool NetworkManager::isBindedWithUDP(int index) {
    if(!_udpSockets[index]) return false;
    return _udpSockets[index]->isBinded();
}
//--------------------------------------------------------------
//
bool NetworkManager::isConnectedWithUDP(int index) {
    if(!_udpSockets[index]) return false;
    return _udpSockets[index]->isConnected();
}
//--------------------------------------------------------------
//
string NetworkManager::localIpWithUDP(int index) {
    if(!_udpSockets[index]) return "";
    return _udpSockets[index]->localIp();
}
//--------------------------------------------------------------
//
int NetworkManager::localPortWithUDP(int index) {
    if(!_udpSockets[index]) return 0;
    return _udpSockets[index]->localPort();
}
//--------------------------------------------------------------
//
string NetworkManager::targetIpWithUDP(int index) {
    if(!_udpSockets[index]) return "";
    return _udpSockets[index]->targetIp();
}
//--------------------------------------------------------------
//
int NetworkManager::targetPortWithUDP(int index) {
    if(!_udpSockets[index]) return 0;
    return _udpSockets[index]->targetPort();
}
//--------------------------------------------------------------
//
string NetworkManager::remoteIpWithUDP(int index) {
    if(!_udpSockets[index]) return "";
    return _udpSockets[index]->remoteIp();
}
//--------------------------------------------------------------
//
int NetworkManager::remotePortWithUDP(int index) {
    if(!_udpSockets[index]) return 0;
    return _udpSockets[index]->remotePort();
}
//--------------------------------------------------------------
//
string NetworkManager::sendDataWithUDP(int index) {
    if(!_udpSockets[index]) return "";
    return _udpSockets[index]->sendData();
}
//--------------------------------------------------------------
//
string NetworkManager::receivedDataWithUDP(int index) {
    if(!_udpSockets[index]) return "";
    return _udpSockets[index]->receivedData();
}

//--------------------------------------------------------------
//
bool NetworkManager::sendToAllWithUDP(string message) {
    int i; int l;
    l = _udpSockets.size();
    for(i = 0; i < l; i++) {
        _udpSockets[i]->sendMessage(message);
    }
    
    return true;
}

//--------------------------------------------------------------
//
bool NetworkManager::closeAllUDP() {
    int i; int l;
    l = _udpSockets.size();
    for(i = 0; i < l; i++) {
        _udpSockets[i]->close();
    }
    
    return true;
}






//==============================================================
// PROTECTED / PRIVATE METHOD
//==============================================================

//--------------------------------------------------------------
//
void NetworkManager::_addListeners() {
    cout << "[NetworkManager]_addListeners()" << endl;
    
    if(_usedListeners) return;
    _usedListeners = true;
    
    ofAddListener(ofEvents().update, this, &NetworkManager::_update);
}

//--------------------------------------------------------------
//
void NetworkManager::_removeListeners() {
    cout << "[NetworkManager]_remoteListeners()" << endl;
    
    if(!_usedListeners) return;
    _usedListeners = false;
    
    ofRemoveListener(ofEvents().update, this, &NetworkManager::_update);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//サーバーの更新
void NetworkManager::_updateServerSocket() {
    cout << "[NetworkManager]_updateServerSocket()" << endl;
    
    int i; int l;
    l = _serverSocket->getLastID();
    for(i = 0; i < l; i++) {
        //--------------------------------------
        //切断確認
        if(!_serverSocket->isClientConnected(i)) {
            //アプリ1なら
            if(i == _app1ID) {
                _app1ID = -1;
                _app1_Host = "-";
                _app1_Port = 0;
                _connectedToApp1 = false;
            }
            //アプリ2なら
            if(i == _app2ID) {
                _app2ID = -1;
                _app2_Host = "-";
                _app2_Port = 0;
                _connectedToApp2 = false;
            }
            //アプリ3なら
            if(i == _app3ID) {
                _app3ID = -1;
                _app3_Host = "-";
                _app3_Port = 0;
                _connectedToApp3 = false;
            }
            continue;
        }
        //--------------------------------------
        
        //--------------------------------------
        //クライアントのIPとポート番号を取得する
        string ip = _serverSocket->getClientIP(i);
        int port = _serverSocket->getClientPort(i);
        //--------------------------------------
        
        //--------------------------------------
        //受信すべきデータがあれば更新する
        string data = _serverSocket->receive(i);
        if(data.length() <= 0) continue;
        _receivedDataWithTCPServer = data;
        //--------------------------------------
        
        //--------------------------------------
        //アプリ1から接続許可要求
        if(data == "connectionRequest_kinectApp") {
            if(!_connectedToApp1) {
                _serverSocket->send(i, "connectionPermission");
                _connectedToApp1 = true;
                _app1ID = i;
                _app1_Host = ip;
                _app1_Port = port;
            }
        }
        //アプリ2から接続許可要求
        else if(data == "connectionRequest_frontApp") {
            if(!_connectedToApp2) {
                _serverSocket->send(i, "connectionPermission");
                _connectedToApp2 = true;
                _app2ID = i;
                _app2_Host = ip;
                _app2_Port = port;
            }
        }
        //アプリ3から接続許可要求
        else if(data == "connectionRequest_captureApp") {
            if(!_connectedToApp3) {
                _serverSocket->send(i, "connectionPermission");
                _connectedToApp3 = true;
                _app3ID = i;
                _app3_Host = ip;
                _app3_Port = port;
            }
        }
        //通信確認
        else if(data == "ping") {
            _serverSocket->send(i, "pong");
        }
        //その他
        else {
            NetworkEvent* networkEvent = new NetworkEvent(NetworkEvent::RECEIVED, data);
            //networkEvent->setProperty<string>("data", data);
            dispatchEvent(networkEvent);
        }
        //--------------------------------------
    }
}

//--------------------------------------------------------------
//TCPソケットの更新
void NetworkManager::_updateTCPSocket() {
    if(!_tcpSocket->isConnected()) {
        //5秒間隔で再接続を試みる
        _deltaTime = ofGetElapsedTimeMillis() - _connectTime;
        if(_deltaTime > 5000) {
            _isConnected_TCP = _tcpSocket->setup(_targetIp_TCP, _targetPort_TCP, _blocking_TCP);
            //            _isConnected_TCP = connectTCPSocket(_targetIp_TCP, _targetPort_TCP);
            _connectTime = ofGetElapsedTimeMillis();
        }
        return;
    }
    
    //--------------------------------------
    //受信すべきデータがあれば更新する
    string data = _tcpSocket->receive();
    if(data.length() <= 0) return;
    _receivedData_TCP = data;
    //--------------------------------------
    
    //--------------------------------------
    //通信確認
    if(data == "ping") {
        _tcpSocket->send("pong");
    }
    //その他
    else {
        NetworkEvent* networkEvent = new NetworkEvent(NetworkEvent::RECEIVED, data);
        //networkEvent->setProperty<string>("data", data);
        dispatchEvent(networkEvent);
    }
    //--------------------------------------
}








//--------------------------------------------------------------
//
void NetworkManager::_socketEventHandler(flEvent& event) {
    //    cout << "[NetworkManager]_socketEventHandler(" << event.type() << ")" << endl;
    
    UDPSocketWrapper* target = (UDPSocketWrapper*)(event.currentTarget());
    
    NetworkEvent& networkEvent = *(NetworkEvent*) &event;
    
    int i; int l;
    l = _udpSockets.size();
    for(i = 0; i < l; i++) {
        UDPSocketWrapper* udpSocket = _udpSockets[i];
        if(target == udpSocket) {
            string eventName = "udp" + ofToString(i) + "Received";
            NetworkEvent* newEvent = new NetworkEvent(eventName, networkEvent.data(), networkEvent.remoteIp(), networkEvent.remotePort());
            dispatchEvent(newEvent);
        }
    }
}


#include "UDPSocketWrapper.h"

#ifdef __APPLE__

//#include <stdio.h>
//#include <string.h>
//#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
//--------------------------------------------------------------
//http://www.geekpage.jp/programming/linux-network/
string UDPSocketWrapper::getLocalAddress() {
    string privateAddress= "";
    
    struct ifaddrs *ifa_list;
    int n = getifaddrs(&ifa_list);
    if (n != 0) { return ""; }
    
    char address[256], netmask[256];
    struct ifaddrs* ifa;
    for(ifa = ifa_list; ifa != NULL; ifa=ifa->ifa_next) {
        //ネットワークインターフェース名
        //            cout << "interface_name = " << ifa->ifa_name << endl;
        //            printf("interface_name = %s\n", ifa->ifa_name);
        //フラグを表示
        //            printf("ifa_flags = 0x%.8x\n", ifa->ifa_flags);
        //            cout << "flags = " << ifa->ifa_flags << endl;
        
        memset(address, 0, sizeof(address));
        memset(netmask, 0, sizeof(netmask));
        
        //IPv4
        if (ifa->ifa_addr->sa_family == AF_INET) {
            inet_ntop(
                      AF_INET,
                      &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr,
                      address, sizeof(address)
                      );
            
            inet_ntop(
                      AF_INET,
                      &((struct sockaddr_in*)ifa->ifa_netmask)->sin_addr,
                      netmask, sizeof(netmask)
                      );
            
            string::size_type index = string(address).find( "192" );
            if(index != string::npos) {
                //                cout << "IPv4" << endl;
                //                cout << "address = " << address << endl;
                //                cout << "netmask = " << netmask << endl;
                
                privateAddress = address;
            }
        }
        //IPv6
        else if (ifa->ifa_addr->sa_family == AF_INET6) {
            inet_ntop(
                      AF_INET6,
                      &((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr,
                      address, sizeof(address)
                      );
            
            inet_ntop(
                      AF_INET6,
                      &((struct sockaddr_in6*)ifa->ifa_netmask)->sin6_addr,
                      netmask, sizeof(netmask)
                      );
            
            //                cout << "IPv6" << endl;
            //                cout << "address = " << address << endl;
            //                cout << "netmask = " << netmask << endl;
            //                printf("  IPv6: %s netmask %s\n", address, netmask);
        }
        else {
            //                printf(" else:%d\n", ifa->ifa_addr->sa_family);
        }
    }
    
    freeifaddrs(ifa_list);
    
    privateAddress = privateAddress != "" ? privateAddress : "127.0.0.1";
    //    cout << "privateAddress = " << privateAddress << endl;
    return privateAddress;
}

#elif defined _WIN32

//--------------------------------------------------------------
//
string UDPSocketWrapper::getLocalAddress() {
    string privateAddress = "";
    
    privateAddress = privateAddress != "" ? privateAddress : "127.0.0.1";
    //    cout << "privateAddress = " << privateAddress << endl;
    return privateAddress;
}

#endif

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//コンストラクタ
UDPSocketWrapper::UDPSocketWrapper() {
    //    debug(true);
    if(debug()) cout << "[UDPSocketWrapper]UDPSocketWrapper()" << endl;
    _target = this;
    
    _usedListeners = false;
    
    //--------------------------------------
    _socket = NULL;
    
    _isBinded = false;
    _isConnected = false;
    
    _localIp = "";
    _localPort = 0;
    
    _targetIp = "";
    _targetPort = 0;
    
    _remoteIp = "";
    _remotePort = 0;
    
    _sendData = "";
    _receivedData = "";
    //--------------------------------------
    
    _addListeners();
}

//--------------------------------------------------------------
//デストラクタ
UDPSocketWrapper::~UDPSocketWrapper() {
    if(debug()) cout << "[UDPSocketWrapper]~UDPSocketWrapper()" << endl;
    _target = NULL;
    
    _removeListeners();
    _usedListeners = false;
    
    //--------------------------------------
    close();
    
    delete _socket;
    _socket = NULL;
    
    _isBinded = false;
    _isConnected = false;
    
    _localIp = "";
    _localPort = 0;
    
    _targetIp = "";
    _targetPort = 0;
    
    _remoteIp = "";
    _remotePort = 0;
    
    _sendData = "";
    _receivedData = "";
    //--------------------------------------
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//初期化
void UDPSocketWrapper::setup() {
    if(debug()) cout << "[UDPSocketWrapper]setup()" << endl;
    
    if(_socket) {
        _socket->Close();
        delete _socket;
        _socket = NULL;
    }
    
    _socket = new ofxUDPManager();
    _socket->Create();
    _socket->SetNonBlocking(true);
}

//--------------------------------------------------------------
//更新
void UDPSocketWrapper::update() {
    //    if(debug()) cout << "[UDPSocketWrapper]update()" << endl;
    
    if(!_isBinded) return;
    
    //--------------------------------------
    //メッセージ検出
    char rowData[100000];
    _socket->Receive(rowData, 100000);
    string data = rowData;
    //メッセージがなかったら何もしない
    if(data == "") return;
    _receivedData = data;
    //--------------------------------------
    
    //--------------------------------------
    //相手先のアドレス
    //char remoteIp[100000];
    _socket->GetRemoteAddr(_remoteIp, _remotePort);
    //_remoteIp = remoteIp;
    //--------------------------------------
    
    //--------------------------------------
    vector<string> dataList = ofSplitString(data, ";");
    //    cout << dataList.size() << endl;
    int i; int l;
    l = dataList.size();
    for(i = 0; i < l; i++) {
        //変数の使い回し
        data = dataList[i];
        if(data == "") continue;
        
        //--------------------------------------
        ////接続要求
        //if(data == "connectionRequest") {
        //    string message = "connectionPermission";
        //    _socket->Send(_sendData.c_str(), _sendData.length());
        //}
        ////接続許可
        //else if(data == "connectionPermission") {
        //
        //}
        //通信確認
        if(data == "ping") {
            string message = "pong";
            _socket->Send(_sendData.c_str(), _sendData.length());
        }
        //通信確認
        else if(data == "pong") {
            
        }
        //通信確認
        else if(data == "close") {
            _isConnected = false;
        }
        ////その他
        //else {
        //    NetworkEvent* networkEvent = new NetworkEvent(NetworkEvent::RECEIVED, data, _remoteIp, _remotePort);
        //    dispatchEvent(networkEvent);
        //}
        //--------------------------------------
        
        NetworkEvent* networkEvent = new NetworkEvent(NetworkEvent::RECEIVED, data, _remoteIp, _remotePort);
        dispatchEvent(networkEvent);
    }
}

//==============================================================
// PUBLIC METHOD
//==============================================================

//--------------------------------------------------------------
//バインド
bool UDPSocketWrapper::bind(int port) {
    if(debug()) cout << "[UDPSocketWrapper]bind(" << port << ")" << endl;
    
    setup();
    
    _localIp = UDPSocketWrapper::getLocalAddress();
    _localPort = port;
    _isBinded = _socket->Bind(_localPort);
    
    return _isBinded;
}

//--------------------------------------------------------------
//リモートとの接続
bool UDPSocketWrapper::connect(string ip, int port) {
    if(debug()) cout << "[UDPSocketWrapper]connect(" << ip << ", " << port << ")" << endl;
    //_udpSocket->Connect("127.0.0.1", 9000);
    
    _targetIp = ip;
    _targetPort = port;
    
    _isConnected = _socket->Connect(_targetIp.c_str(), _targetPort);
    if(debug()) cout << "_isConnected = " << _isConnected << endl;
    return _isConnected;
}
//--------------------------------------------------------------
//メッセージ送信
int UDPSocketWrapper::sendMessage(string message) {
    if (debug()) cout << "[UDPSocketWrapper]sendMessage(" << message << ")" << endl;
    if (!_isConnected) return 0;
    
    _sendData = message + "\x00";
    int sendedSize = _socket->Send(_sendData.c_str(), _sendData.length());
    return sendedSize;
}
//--------------------------------------------------------------
//切断
bool UDPSocketWrapper::close() {
    if(debug()) cout << "[UDPSocketWrapper]close()" << endl;
    
    sendMessage("close;");
    
    bool success = _socket->Close();
    if(debug()) cout << "success = " << success << endl;
    if(success) {
        _isBinded = false;
        _isConnected = false;
    }
    
    return success;
}

//==============================================================
// SETTER / GETTER
//==============================================================

//--------------------------------------------------------------
//
bool UDPSocketWrapper::isBinded() { return _isBinded; }
//--------------------------------------------------------------
//
bool UDPSocketWrapper::isConnected() { return _isConnected; }
//--------------------------------------------------------------
//
string UDPSocketWrapper::localIp() { return _localIp; }
//--------------------------------------------------------------
//
int UDPSocketWrapper::localPort() { return _localPort; }
//--------------------------------------------------------------
//
string UDPSocketWrapper::targetIp() { return _targetIp; }
//--------------------------------------------------------------
//
int UDPSocketWrapper::targetPort() { return _targetPort; }
//--------------------------------------------------------------
//
string UDPSocketWrapper::remoteIp() { return _remoteIp; }
//--------------------------------------------------------------
//
int UDPSocketWrapper::remotePort() { return _remotePort; }
//--------------------------------------------------------------
//
string UDPSocketWrapper::sendData() { return _sendData; }
//--------------------------------------------------------------
//
string UDPSocketWrapper::receivedData() { return _receivedData; }

//==============================================================
// PROTECTED / PRIVATE METHOD
//==============================================================

//--------------------------------------------------------------
//
void UDPSocketWrapper::_addListeners() {
    if(debug()) cout << "[UDPSocketWrapper]_addListeners()" << endl;
    
    if(_usedListeners) return;
    _usedListeners = true;
    
    ofAddListener(ofEvents().update, this, &UDPSocketWrapper::_update);
}

//--------------------------------------------------------------
//
void UDPSocketWrapper::_removeListeners() {
    if(debug()) cout << "[UDPSocketWrapper]_remoteListeners()" << endl;
    
    if(!_usedListeners) return;
    _usedListeners = false;
    
    ofRemoveListener(ofEvents().update, this, &UDPSocketWrapper::_update);
}

//==============================================================
// EVENT HANDLER
//==============================================================

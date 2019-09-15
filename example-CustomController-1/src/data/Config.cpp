#include "Config.h"

//--------------------------------------
//コマンドライン引数
vector<string> Config::commandLineParameter;
//--------------------------------------

//--------------------------------------
string Config::XML_DIRECTORY_PATH = "xml/";

string Config::CONFIG_XML_PATH = XML_DIRECTORY_PATH + "config.xml";
ofxXmlSettings Config::configXml;
//--------------------------------------

//--------------------------------------
//アプリケーションの設定
string Config::appName = "ofApp";
//起動モード develop or standAlone or editor or release
string Config::mode = "develop";
string Config::processMode = "auto";
//フレームレート
int Config::fps = 30;
//ウィンドウの位置
ofPoint Config::windowPosition;
//--------------------------------------

//--------------------------------------
string Config::inputFolderPath = "input";
vector<string> Config::outputFolderPathList;
string Config::uploaderFolderPath = "output";
//--------------------------------------

//--------------------------------------
//ネットワークの設定
//UDP
//
string Config::udp_local_ip0 = "127.0.0.1";
int Config::udp_local_port0 = 0;
//--------------------------------------

string Config::finishScript = "";

//--------------------------------------------------------------
//
void Config::load() {
    ofLog(OF_LOG_VERBOSE) << "[Config]load()" << endl;
    
    //config.xmlの読込
    loadConfigXml();
}

//--------------------------------------------------------------
//
void Config::loadConfigXml() {
    ofLog(OF_LOG_VERBOSE) << "[Config]loadConfigXml()" << endl;
    
    //config.xmlの読込
    if(configXml.loadFile(CONFIG_XML_PATH)) {
        cout << "[Config]loaded config.xml" << endl;
        
        //--------------------------------------
        Config::appName = Config::configXml.getValue("application:name", "0");
        Config::fps = Config::configXml.getValue("application:fps", 0);
        Config::windowPosition.x = Config::configXml.getValue("application:window:position:x", 0.0);
        Config::windowPosition.y = Config::configXml.getValue("application:window:position:y", 0.0);
        
        Config::inputFolderPath = Config::configXml.getValue("application:inputSettings:folderPath", "0");
//        Config::outputFolderPath = Config::configXml.getValue("application:outputFolderPath", "0");
        
        Config::configXml.pushTag("application");
        Config::configXml.pushTag("outputSettings");
        Config::configXml.pushTag("folderPathList");
        int numTags = Config::configXml.getNumTags("app");
        for(int i = 0; i < numTags; i++) {
            string path = Config::configXml.getValue("app", "0", i);
            Config::outputFolderPathList.push_back(path);
        }
        Config::uploaderFolderPath = Config::configXml.getValue("uploader", "0");
        Config::configXml.popTag();
        Config::configXml.popTag();
        Config::configXml.popTag();

//        float textureSize = Config::configXml.getAttribute("application:outputFolderPathList:uploader", "textureSize", 0.0);
//        cout << "textureSize = " << textureSize << endl;
        //--------------------------------------

        //--------------------------------------
        //ネットワークの設定
        //UDP
        //
        Config::udp_local_ip0 = Config::configXml.getValue("network:udp:local:ip0", "0");
        Config::udp_local_port0 = Config::configXml.getValue("network:udp:local:port0", 0);
        //--------------------------------------
    } else {
        cout << "** Error ** [Config]can't loaded config.xml" << endl;
    }
}

//--------------------------------------------------------------
//
void Config::save() {
    ofLog(OF_LOG_VERBOSE) << "[Config]save()" << endl;
    
    saveConfigXml();
}
//--------------------------------------------------------------
//
void Config::saveConfigXml() {
    ofLog(OF_LOG_VERBOSE) << "[Config]saveConfigXml()" << endl;
    
    //config.xmlの保存
    if(configXml.saveFile(CONFIG_XML_PATH)) {
        cout << "[Config]saved config.xml" << endl;
    } else {
        cout << "** Error ** [Config]can't saved config.xml" << endl;
    }    
}

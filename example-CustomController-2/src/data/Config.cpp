#include "Config.h"

string Config::SETTINGS_DIRECTORY_PATH = "settings/";
string Config::SETTINGS_FILE_NAME = "settings.txt";

//--------------------------------------
//アプリケーションの設定
string Config::appName = "ofApp";
//フレームレート
int Config::fps = 30;
//ウィンドウの位置
ofPoint Config::windowPosition;
//--------------------------------------

//--------------------------------------
//ネットワークの設定
//UDP
//
string Config::udp_local_ip0 = "127.0.0.1";
int Config::udp_local_port0 = 0;
//--------------------------------------

//--------------------------------------------------------------
//
void Config::load() {
    ofLog() << "[Config]load()" << endl;
    
    string fpath = SETTINGS_DIRECTORY_PATH + SETTINGS_FILE_NAME;
    fpath = ofToDataPath(fpath, true);
    //    ofLog() << fpath;
    std::string buff;
    std::ifstream ifs(fpath.c_str());
    if(!ifs.is_open()){
        ofLog(OF_LOG_ERROR) << "** Error ** [Config]Can't loaded settings.xml.";
    } else {
        string delimiter = "=";
        while(std::getline(ifs, buff)){
            //std::cout << buff << std::endl;
            vector<string> texts = ofSplitString(buff, delimiter);
            if(texts.size() == 2) {
                ofLog() << texts[0] << " : " << texts[1];
                
                string propName = texts[0];
                string value = texts[1];
                
                if(propName == "app_name") {
                    Config::appName = value;
                }
                else if(propName == "fps") {
                    Config::appName = value;
                }
                else if(propName == "window_x") {
                    Config::windowPosition.x = ofToFloat(value);
                }
                else if(propName == "window_y") {
                    Config::windowPosition.y = ofToFloat(value);
                }
                else if(propName == "udp_local_port") {
                    Config::appName = ofToInt(value);
                }
                else if(propName == "udp_remote_ip") {
                    Config::appName = value;
                }
                else if(propName == "udp_remote_port") {
                    Config::appName = ofToInt(value);
                }
            }
        }
    }
}

//--------------------------------------------------------------
//
void Config::save() {
    ofLog() << "[Config]save()";
    
    //settings.xml
//    if(configXml.saveFile(CONFIG_XML_PATH)) {
//        cout << "[Config]saved config.xml" << endl;
//    } else {
//        cout << "** Error ** [Config]can't saved config.xml" << endl;
//    }    
}

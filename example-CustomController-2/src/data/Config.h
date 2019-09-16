#pragma once

#include <string>

#include "ofxXmlSettings.h"

class Config {
    public:
        static string SETTINGS_DIRECTORY_PATH;
        static string SETTINGS_FILE_NAME;
    
        //--------------------------------------
        //アプリケーションの設定
        static string appName;
        //フレームレート
        static int fps;
        //ウィンドウの位置
        static ofPoint windowPosition;
        //--------------------------------------
    
        //--------------------------------------
        //ネットワークの設定
        //UDP
        static string udp_local_ip0;
        static int udp_local_port0;
        //--------------------------------------

    private:
        
    public:
        static void load();
        static void save();
    
    private:
};

#pragma once

#include <string>

#include "ofxXmlSettings.h"

class Config {
    public:
        //コマンドライン引数
        static vector<string> commandLineParameter;
        
        //--------------------------------------
        static string XML_DIRECTORY_PATH;
        //xml
        static string CONFIG_XML_PATH;
        static ofxXmlSettings configXml;
        //--------------------------------------
        
        //--------------------------------------
        //アプリケーションの設定
        static string appName;
        //起動モード develop or standAlone or editor or release
        static string mode;
        //auto or manual
        static string processMode;
        //フレームレート
        static int fps;
        //ウィンドウの位置
        static ofPoint windowPosition;
        //--------------------------------------

        //--------------------------------------
        static string inputFolderPath;
//        static string outputFolderPath;
        static vector<string> outputFolderPathList;
        static string uploaderFolderPath;
        //--------------------------------------
    
        //--------------------------------------
        //ネットワークの設定
        //UDP
        //
        static string udp_local_ip0;
        static int udp_local_port0;
        //--------------------------------------
    
        static string finishScript;

    private:
        
    public:
        static void load();
        static void loadConfigXml();
    
        static void save();
        static void saveConfigXml();
    
    private:
};

#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
using namespace fl2d;

#include "BasicController.h"

class UIComponents : public BasicController {
    
    public:
        //--------------------------------------
        TextField* label101;
        TextField* label102;
        TextField* label103;
        TextField* label104;
        TextField* label105;
        TextField* label106;
        TextField* label107;
        TextField* label108;
        TextField* label109;
        TextField* label110;
        TextField* label111;
        TextField* label112;
        TextField* label113;
        
        TextField* text101;
        TextField* text102;
        TextField* text103;
        TextField* text104;
        TextField* text105;
        TextField* text106;
        TextField* text107;
        TextField* text108;
        TextField* text109;
        TextField* text110;
        TextField* text111;
        TextField* text112;
        TextField* text113;
    
        ComboBox* comboBox101;
    
        Button* btn101;
        Button* btn102;
        Button* btn103;
        //--------------------------------------
        //--------------------------------------
        TextField* label201;
        TextField* label202;
        TextField* label203;
        TextField* label204;
        TextField* label205;
        TextField* label206;
        TextField* label207;
        TextField* label208;
        TextField* label209;
        TextField* label210;
        TextField* label211;
        TextField* label212;
        TextField* label213;
        
        TextField* text201;
        TextField* text202;
        TextField* text203;
        TextField* text204;
        TextField* text205;
        TextField* text206;
        TextField* text207;
        TextField* text208;
        TextField* text209;
        TextField* text210;
        TextField* text211;
        TextField* text212;
        TextField* text213;
        
        ComboBox* comboBox201;
        
        Button* btn201;
        Button* btn202;
        Button* btn203;
        //--------------------------------------
    
//        //--------------------------------------
//        //スライダー
//        Slider* slider001;
//        Slider* slider002;
//        
//        RangeSlider* rangeSlider001;
//        RangeSlider* rangeSlider002;
//        
//        SimpleSlider* simpleSlider001;
//        SimpleSlider* simpleSlider002;
//        //--------------------------------------
//        //--------------------------------------
//        //RGBスライダー
//        ColorSlider* colorSlider001;
//        //--------------------------------------
//        //--------------------------------------
//        //ボタン
//        Button* btn001;
//        Button* btn002;
//        Button* btn003;
//        Button* btn004;
//        Button* btn005;
//        //--------------------------------------
//        //--------------------------------------
//        //2Dパッド
//        Pad2D* pad001;
//        Pad2D* pad002;
//        Pad2D* pad003;
//        Pad2D* pad004;
//        Pad2D* pad005;
//        //--------------------------------------
//        //--------------------------------------
//        //ラジオボタン
//        RadioButton* radio001;
//        RadioButton* radio002;
//        RadioButton* radio003;
//        RadioButton* radio004;
//        RadioButton* radio005;
//        //--------------------------------------
//        //--------------------------------------
//        //インプットテキストフィールド
//        TextField* text001;
//        TextField* text002;
//        TextField* text003;
//        TextField* text004;
//        TextField* text005;
//        //--------------------------------------
//        //--------------------------------------
//        //カラーピッカー
//        CircleColorPicker* colorPicker001;
//        //--------------------------------------
//        //--------------------------------------
//        //ジョイスティック
//        Joystick* joystick001;
//        //--------------------------------------
//        //--------------------------------------
//        //ナンバーダイアラー
//        NumberDialer* dialer001;
//        NumberDialer* dialer002;
//        NumberDialer* dialer003;
//        //--------------------------------------
//        //--------------------------------------
//        //コンボボックス
//        ComboBox* comboBox001;
//        ComboBox* comboBox002;
//        ComboBox* comboBox003;
//        //--------------------------------------
//        
//        //--------------------------------------
//        ScrollKit* scrollKit001;
//        Sprite* body001;
//        //--------------------------------------
    
    protected:
    
    private:
    
    public:
        UIComponents();
        ~UIComponents();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        virtual void _uiEventHandler(Event& event);
};
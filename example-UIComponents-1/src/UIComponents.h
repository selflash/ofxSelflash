#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

class UIComponents : public flSprite {
    
    public:
        //--------------------------------------
        //スライダー
        flSlider* slider001;
        flSlider* slider002;
        
        flRangeSlider* rangeSlider001;
        flRangeSlider* rangeSlider002;
        //--------------------------------------
        //--------------------------------------
        //RGBスライダー
        flColorSlider* colorSlider001;
        //--------------------------------------
        //--------------------------------------
        //ボタン
        flButton* btn001;
        flButton* btn002;
        flButton* btn003;
        flButton* btn004;
        flButton* btn005;
        //--------------------------------------
        //--------------------------------------
        //2Dパッド
        flPad2D* pad001;
        flPad2D* pad002;
        flPad2D* pad003;
        flPad2D* pad004;
        flPad2D* pad005;
        //--------------------------------------
        //--------------------------------------
        //ラジオボタン
        flRadioButton* radio001;
        flRadioButton* radio002;
        flRadioButton* radio003;
        flRadioButton* radio004;
        flRadioButton* radio005;
        //--------------------------------------
        //--------------------------------------
        //インプットテキストフィールド
        flTextField* text001;
        flTextField* text002;
        flTextField* text003;
        flTextField* text004;
        flTextField* text005;
        //--------------------------------------
        //--------------------------------------
        //カラーピッカー
        flCircleColorPicker* colorPicker001;
        //--------------------------------------
        //--------------------------------------
        //ジョイスティック
        flJoystick* joystick001;
        //--------------------------------------
        //--------------------------------------
        //ナンバーダイアラー
        flNumberDialer* dialer001;
        flNumberDialer* dialer002;
        flNumberDialer* dialer003;
        //--------------------------------------
        //--------------------------------------
        //コンボボックス
        flComboBox* comboBox001;
        flComboBox* comboBox002;
        flComboBox* comboBox003;
        //--------------------------------------
        
        //--------------------------------------
        flScrollKit* scrollKit001;
        flSprite* body001;
        //--------------------------------------
    
    private:
    
    public:
        UIComponents();
        ~UIComponents();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _uiEventHandler(flEvent& event);
};
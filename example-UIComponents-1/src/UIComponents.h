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
        flColorSlider* colorSlider002;
        //--------------------------------------
        //--------------------------------------
        //Vec2スライダー
        flVec2Slider* vec2Slider001;
        //--------------------------------------
        //--------------------------------------
        //Vec3スライダー
        flVec3Slider* vec3Slider001;
        //--------------------------------------
        //--------------------------------------
        //ボタン
        flButton* button001;
        flButton* button002;
        flButton* button003;
        flButton* button004;
        flButton* button005;
        flButton* button006;
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
        //チェックボックス
        flCheckBox* check001;
        flCheckBox* check002;
        flCheckBox* check003;
//        flCheckBox* check004;
//        flCheckBox* check005;
        //--------------------------------------
        //--------------------------------------
        //ラジオボタン
        flRadioButtonGroup* radioButtonGroup;
        flRadioButton* radio001;
        flRadioButton* radio002;
        flRadioButton* radio003;
//        flRadioButton* radio004;
//        flRadioButton* radio005;
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
        //ジョイスティック1D
        flJoystick1* joystick1001;
        flJoystick1* joystick1002;
        flJoystick1* joystick1003;
        flJoystick1* joystick1004;
        flJoystick1* joystick1005;
        flJoystick1* joystick1006;
        flJoystick1* joystick1007;
    
        flJoystick1* joystick1101;
        flJoystick1* joystick1102;
        //ジョイスティック2D
        flJoystick2* joystick2001;
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
        //ヒストグラムビュワー
        flHistgramViewer* hViewer001;
        flHistgramViewer* hViewer002;
        flHistgramViewer* hViewer003;
        //--------------------------------------

        //--------------------------------------
        flAngler* angler000;
        //--------------------------------------
    
        //--------------------------------------
        flScrollKit* scrollKit001;
        flSprite* body001;
        //--------------------------------------
    
    private:
    
    public:
        UIComponents();
        virtual ~UIComponents();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _uiEventHandler(flEvent& event);
};

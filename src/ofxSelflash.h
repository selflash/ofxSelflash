#pragma once

// version 0.9.0

//flash.utils
#include "flmath.h"
#include "flstringutil.h"

#include "flDefinition.h"

//flash.core
#include "flObject.h"

//flash.display
#include "flStage.h"
#include "flMovieClip.h"
#include "flSprite.h"
#include "flDisplayObjectContainer.h"
#include "flInteractiveObject.h"
#include "flBitmapData.h"
#include "flBitmap.h"
#include "flGraphics.h"
#include "flShape.h"
#include "flDisplayObject.h"
#include "flBlendMode.h"

//flash.events
#include "flEventDispatcher.h"
#include "flEvent.h"
#include "flFocusEvent.h"
#include "flMouseEvent.h"
#include "flKeyboardEvent.h"
#include "flSliderEvent.h"
#include "flRotarySliderEvent.h"
#include "flAnglerEvent.h"
#include "flButtonEvent.h"
#include "flCheckBoxEvent.h"
#include "flRadioButtonEvent.h"
#include "flNumberDialerEvent.h"
#include "flRangeSliderEvent.h"
#include "flColorSliderEvent.h"
#include "flVec2SliderEvent.h"
#include "flVec3SliderEvent.h"
#include "flColorPickerEvent.h"
#include "flPadEvent.h"
#include "flJoystick1Event.h"
#include "flJoystick2Event.h"
#include "flComboBoxEvent.h"
#include "flHistgramViewerEvent.h"

//flash.geom
#include "flColorTransform.h"
#include "flMatrix.h"
//#include "Particle2D.h"
#include "flRectangle.h"
#include "flTransform.h"

//flash.texts
#include "flFont.h"
#include "flTextField.h"
#include "flTextFieldAutoSize.h"

//flash.ui
#include "flMouse.h"
#include "flKeyboard.h"
#include "flButton.h"
#include "flCheckBox.h"
#include "flRadioButton.h"
#include "flNumberDialer.h"
#include "flSlider.h"
#include "flRangeSlider.h"
#include "flColorSlider.h"
#include "flVec2Slider.h"
#include "flVec3Slider.h"
#include "flRotarySlider.h"
#include "flAngler.h"
#include "flCircleColorPicker.h"
#include "flPad2D.h"
#include "flPad3D.h"
#include "flJoyStick2.h"
#include "flJoyStick1.h"
#include "flScrollKit.h"
#include "flComboBox.h"
#include "flHistgramViewer.h"

//those class are basic template.
//if you use them, include in your project.
//#include "flBasicController.h"
//#include "flBasicDraggableObject.h"

class ofxSelflash {
    public:
    
    private:
        static bool _isSetuped;

    public:
//        static inline bool manualUpdate() { return fl2d::flDefinition::AUTO_UPDATE; }
//        static inline ofEventOrder updatePriority() { return fl2d::flDefinition::UPDATE_PRIORITY; }
//        static inline bool autoDraw() { return fl2d::flDefinition::AUTO_DRAW; }
//        static inline ofEventOrder drawPriority() { return fl2d::flDefinition::DRAW_PRIORITY; }
    
        static inline void setup(fl2d::flSettings settings = fl2d::flSettings()) {
            if(_isSetuped) return;
            _isSetuped = true;

            fl2d::flFont::setup();
            fl2d::flStage::instance()->setup(settings);
        }
    
        static inline void clear() {
            if(!_isSetuped) return;
            _isSetuped = false;

            fl2d::flStage::clear();
            fl2d::flFont::clear();
        }
    
        static inline void update() { fl2d::flStage::instance()->update(); }
        static inline void draw() { fl2d::flStage::instance()->draw(); }

        static inline fl2d::flStage* stage() { return fl2d::flStage::instance(); }
    
    private:
    
};






/**
 TODO
 
 
 =========================================
 FlashFramework
 =========================================
 
 -----------------------------------------
 【flash.display】
 
 [flash.display.Bitmap]
 
 [flash.display.BitmapData]
 
 [flash.display.BlendMode]
 
 [flash.display.DisplayObject]
 ■ stageへの参照がとれない時がある
 □ stage()の型がDisplayObjectになってる
 
 [flash.display.DisplayObjectContainer]
 □ width, heightのsetterでの子への影響
 
 [flash.display.Graphics]
 ■ clear()の挙動が違う
 
 [flash.display.InteractiveObject]
 
 [flash.display.MovieClip]
 
 [flash.display.Sprite]
 □ startDrag()の実装方法がベストじゃない
 
 [flash.display.Stage]
 □ ハンドカーソルの表示
 □ 複数keyDown時の挙動
 -----------------------------------------
 
 -----------------------------------------
 【flash.events】
 
 [flash.events.Event]
 
 [flash.events.EventDispathcer]
 □ dispatch中のイベントハンドラ内でdispatch中のイベントをremoveEventListenerした時に上手く行かない
 
 [flash.events.MouseEvent]
 □ MouseEvent.CLICKの実装
 □ MouseEvent.DOUBLE_CLICKの実装
 
 [flash.events.TextEvent]
 
 [flash.events.SliderEvent]
 
 [flash.events.ColorSliderEvent]
 
 [flash.events.RangeSliderEvent]
 
 [flash.events.PadEvent]
 
 [flash.events.JoystickEvent]
 
 [flash.events.ComboBoxEvent]
 -----------------------------------------
 
 -----------------------------------------
 【flash.filters】
 
 [flash.filters.BlurFilter]
 -----------------------------------------
 
 -----------------------------------------
 【flash.geom】
 
 [flash.geom.flMatrix]
 
 [flash.geom.flRectangle]
 
 [flash.geom.Transform]
 -----------------------------------------
 
 -----------------------------------------
 【flash.media】
 -----------------------------------------
 
 -----------------------------------------
 【flash.net】
 -----------------------------------------
 
 -----------------------------------------
 【flash.text】
 [flash.texts.TextField]
 □ テキストのy座標が0より上に配置される
 -----------------------------------------
 
 -----------------------------------------
 【flash.ui】
 
 [flash.ui.Keyboard]
 
 [flash.ui.Mouse]
 
 [flash.ui.Slider]
 
 [flash.ui.ColorSlider]
 
 [flash.ui.SimpleSlider]
 
 [flash.ui.Pad2D]
 
 [flash.ui.Joystick]
 
 [flash.ui.NumberDialer]
 
 [flash.ui.ComboBox]
 -----------------------------------------
 
 -----------------------------------------
 【flash.utils】
 -----------------------------------------
 
 -----------------------------------------
 */


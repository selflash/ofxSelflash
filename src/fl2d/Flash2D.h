/**
 [メモ]
 ■基本設計は「完全コンストラクタ」パターンです。
 
 */

#pragma once

#include "FlashConfig.h"

typedef fl2d::FlashConfig FlashConfig;

//flash.core
#include "core/Object.h"

typedef fl2d::Object Object;



//flash.display
#include "display/Stage.h"
#include "display/MovieClip.h"
#include "display/Sprite.h"
#include "display/DisplayObjectContainer.h"
#include "display/InteractiveObject.h"
#include "display/BitmapData.h"
#include "display/Bitmap.h"
#include "display/Graphics.h"
#include "display/Shape.h"
#include "display/DisplayObject.h"
#include "display/BlendMode.h"

typedef fl2d::Stage flStage;
typedef fl2d::MovieClip flMovieClip;
typedef fl2d::Sprite flSprite;
typedef fl2d::DisplayObjectContainer flDisplayObjectContainer;
typedef fl2d::InteractiveObject flInteractiveObject;
typedef fl2d::BitmapData flBitmapData;
typedef fl2d::Bitmap flBitmap;
typedef fl2d::Shape flShape;
typedef fl2d::Graphics flGraphics;
typedef fl2d::DisplayObject flDisplayObject;
typedef fl2d::BlendMode flBlendMode;



//flash.events
#include "events/EventDispatcher.h"
#include "events/Event.h"
#include "events/SoundEvent.h"
#include "events/AnimationEvent.h"
#include "events/FocusEvent.h"
#include "events/MouseEvent.h"
#include "events/KeyboardEvent.h"
#include "events/SliderEvent.h"
#include "events/RotarySliderEvent.h"
#include "events/AnglerEvent.h"
#include "events/ButtonEvent.h"
#include "events/RadioButtonEvent.h"
#include "events/NumberDialerEvent.h"
#include "events/RangeSliderEvent.h"
#include "events/ColorSliderEvent.h"
#include "events/Vec2SliderEvent.h"
#include "events/Vec3SliderEvent.h"
#include "events/ColorPickerEvent.h"
#include "events/PadEvent.h"
#include "events/Joystick1DEvent.h"
#include "events/Joystick2DEvent.h"
#include "events/ComboBoxEvent.h"

typedef fl2d::EventDispatcher flEventDispatcher;
typedef fl2d::Event flEvent;
typedef fl2d::SoundEvent flSoundEvent;
typedef fl2d::AnimationEvent flAnimationEvent;
typedef fl2d::InteractiveObject flInteractiveObject;
typedef fl2d::FocusEvent flFocusEvent;
typedef fl2d::MouseEvent flMouseEvent;
typedef fl2d::KeyboardEvent flKeyboardEvent;
typedef fl2d::SliderEvent flSliderEvent;
typedef fl2d::RotarySliderEvent flRotarySliderEvent;
typedef fl2d::AnglerEvent flAnglerEvent;
typedef fl2d::ButtonEvent flButtonEvent;
typedef fl2d::RadioButtonEvent flRadioButtonEvent;
typedef fl2d::NumberDialerEvent flNumberDialerEvent;
typedef fl2d::RangeSliderEvent flRangeSliderEvent;
typedef fl2d::ColorSliderEvent flColorSliderEvent;
typedef fl2d::Vec2SliderEvent flVec2SliderEvent;
typedef fl2d::Vec3SliderEvent flVec3SliderEvent;
typedef fl2d::ColorPickerEvent flColorPickerEvent;
typedef fl2d::PadEvent flPadEvent;
typedef fl2d::Joystick1DEvent flJoystick1DEvent;
typedef fl2d::Joystick2DEvent flJoystick2DEvent;
typedef fl2d::ComboBoxEvent flComboBoxEvent;



//flash.geom
#include "geom/ColorTransform.h"
#include "geom/Matrix.h"
//#include "geom/Particle2D.h"
#include "geom/Rectangle.h"
#include "geom/Transform.h"

typedef fl2d::ColorTransform flColorTransform;
typedef fl2d::Matrix flMatrix;
//typedef fl2d::Particle2D flParticle2D;
typedef fl2d::Rectangle flRectangle;
typedef fl2d::Transform flTransform;



//flash.net
#include "net/Loader.h"

typedef fl2d::Loader flLoader;



//flash.texts
#include "texts/Font.h"
#include "texts/TextField.h"
#include "texts/TextFieldAutoSize.h"

typedef fl2d::Font flFont;
typedef fl2d::TextField flTextField;
typedef fl2d::TextFieldAutoSize flTextFieldAutoSize;



//flash.ui
#include "ui/Mouse.h"
#include "ui/Keyboard.h"
#include "ui/Button.h"
#include "ui/RadioButton.h"
#include "ui/NumberDialer.h"
#include "ui/Slider.h"
#include "ui/RangeSlider.h"
#include "ui/ColorSlider.h"
#include "ui/Vec2Slider.h"
#include "ui/Vec3Slider.h"
#include "ui/RotarySlider.h"
#include "ui/Angler.h"
#include "ui/CircleColorPicker.h"
#include "ui/Pad2D.h"
#include "ui/Pad3D.h"
#include "ui/Joystick2D.h"
#include "ui/Joystick1D.h"
#include "ui/ScrollKit.h"
#include "ui/ComboBox.h"

typedef fl2d::Mouse flMouse;
typedef fl2d::Keyboard flKeyboard;
typedef fl2d::Button flButton;
typedef fl2d::RadioButton flRadioButton;
typedef fl2d::NumberDialer flNumberDialer;
typedef fl2d::Slider flSlider;
typedef fl2d::RangeSlider flRangeSlider;
typedef fl2d::ColorSlider flColorSlider;
typedef fl2d::Vec2Slider flVec2Slider;
typedef fl2d::Vec3Slider flVec3Slider;
typedef fl2d::RotarySlider flRotarySlider;
typedef fl2d::Angler flAngler;
typedef fl2d::CircleColorPicker flCircleColorPicker;
typedef fl2d::Pad2D flPad2D;
typedef fl2d::Pad3D flPad3D;
typedef fl2d::Joystick1D flJoystick1D;
typedef fl2d::Joystick2D flJoystick2D;
typedef fl2d::ScrollKit flScrollKit;
typedef fl2d::ComboBox flComboBox;

class Flash2D {
    public:
        
    private:
        static bool _isSetuped;

    public:
        static inline void setup() {
            if(_isSetuped) return;
            _isSetuped = true;
            
            fl2d::Font::setup();
        }
    
        static inline void clear() {
            if(!_isSetuped) return;
            _isSetuped = false;
            
            fl2d::Stage::clear();
            
            fl2d::Font::clear();
        }
};

//グローバル
//Stage* getStage(){ return Stage::instance(); }

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
 
 [flash.geom.Matrix]
 
 [flash.geom.Rectangle]
 
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
 【flash.gl】
 
 [flash.gl.FrameBufferObject]

 -----------------------------------------
 */

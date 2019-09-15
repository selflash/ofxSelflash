#pragma once

#include "flmath.h"
#include "flstringutil.h"

#include "FlashConfig.h"
typedef fl2d::FlashConfig FlashConfig;

//flash.core
#include "Object.h"

typedef fl2d::Object Object;

//flash.display
#include "Stage.h"
#include "MovieClip.h"
#include "Sprite.h"
#include "DisplayObjectContainer.h"
#include "InteractiveObject.h"
#include "BitmapData.h"
#include "Bitmap.h"
#include "Graphics.h"
#include "Shape.h"
#include "DisplayObject.h"
#include "BlendMode.h"

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
#include "EventDispatcher.h"
#include "Event.h"
#include "SoundEvent.h"
#include "AnimationEvent.h"
#include "FocusEvent.h"
#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "SliderEvent.h"
#include "RotarySliderEvent.h"
#include "AnglerEvent.h"
#include "ButtonEvent.h"
#include "CheckBoxEvent.h"
#include "RadioButtonEvent.h"
#include "NumberDialerEvent.h"
#include "RangeSliderEvent.h"
#include "ColorSliderEvent.h"
#include "Vec2SliderEvent.h"
#include "Vec3SliderEvent.h"
#include "ColorPickerEvent.h"
#include "PadEvent.h"
#include "Joystick1Event.h"
#include "Joystick2Event.h"
#include "ComboBoxEvent.h"
#include "HistgramViewerEvent.h"

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
typedef fl2d::CheckBoxEvent flCheckBoxEvent;
typedef fl2d::RadioButtonEvent flRadioButtonEvent;
typedef fl2d::NumberDialerEvent flNumberDialerEvent;
typedef fl2d::RangeSliderEvent flRangeSliderEvent;
typedef fl2d::ColorSliderEvent flColorSliderEvent;
typedef fl2d::Vec2SliderEvent flVec2SliderEvent;
typedef fl2d::Vec3SliderEvent flVec3SliderEvent;
typedef fl2d::ColorPickerEvent flColorPickerEvent;
typedef fl2d::PadEvent flPadEvent;
typedef fl2d::Joystick1Event flJoystick1Event;
typedef fl2d::Joystick2Event flJoystick2Event;
typedef fl2d::ComboBoxEvent flComboBoxEvent;
typedef fl2d::HistgramViewerEvent flHistgramViewerEvent;



//flash.geom
#include "ColorTransform.h"
#include "flMatrix.h"
//#include "Particle2D.h"
#include "flRectangle.h"
#include "flTransform.h"

typedef fl2d::ColorTransform flColorTransform;
//typedef fl2d::Matrix flMatrix;
//typedef fl2d::Particle2D flParticle2D;
//typedef fl2d::flRectangle flRectangle;
//typedef fl2d::Transform flTransform;

//flash.texts
#include "texts/Font.h"
#include "texts/TextField.h"
#include "texts/TextFieldAutoSize.h"

typedef fl2d::Font flFont;
typedef fl2d::TextField flTextField;
typedef fl2d::TextFieldAutoSize flTextFieldAutoSize;



//flash.ui
#include "Mouse.h"
#include "Keyboard.h"
#include "Button.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "NumberDialer.h"
#include "Slider.h"
#include "RangeSlider.h"
#include "ColorSlider.h"
#include "Vec2Slider.h"
#include "Vec3Slider.h"
#include "RotarySlider.h"
#include "Angler.h"
#include "CircleColorPicker.h"
#include "Pad2D.h"
#include "Pad3D.h"
#include "Joystick2.h"
#include "Joystick1.h"
#include "ScrollKit.h"
#include "ComboBox.h"
#include "HistgramViewer.h"

typedef fl2d::Mouse flMouse;
typedef fl2d::Keyboard flKeyboard;
typedef fl2d::Button flButton;
typedef fl2d::CheckBox flCheckBox;
typedef fl2d::RadioButtonGroup flRadioButtonGroup;
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
typedef fl2d::Joystick1 flJoystick1;
typedef fl2d::Joystick2 flJoystick2;
typedef fl2d::ScrollKit flScrollKit;
typedef fl2d::ComboBox flComboBox;
typedef fl2d::HistgramViewer flHistgramViewer;

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
 【flash.gl】
 
 [flash.gl.FrameBufferObject]
 
 -----------------------------------------
 */

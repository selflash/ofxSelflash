#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flPadEvent.h"
#include "flNumericDialer.h"
#include "flNumericDialerEvent.h"

using namespace glm;

namespace fl2d {
    
    class flPad2D : public flUIBase {
        
    public:
        flSprite* area = NULL;
        flSprite* lever = NULL;
        
    protected:
        
    private:
        flNumericDialer* _dialer01 = NULL;
        flNumericDialer* _dialer02 = NULL;
        flNumericDialer* _dialer03 = NULL;
        flNumericDialer* _dialer04 = NULL;

        int _digit = 2;

        float _width = 100.0;
        float _height = 100.0;
        float _areaWidth = 100.0;
        float _areaHeight = 100.0;
        float _leftValue = 0.0;
        float _rightValue = 1.0;
        float _topValue = 0.0;
        float _bottomValue = 1.0;
        float _n = 0;
        float _rangeWidth = 1.0;
        float _rangeHeight = 1.0;

        float _leverRadius = 7;
                
        float _xRatio = 0.5;
        float _yRatio = 0.5;
        vec2 _value = vec2(0.5, 0.5);

//        flTextField* _ratioText = NULL;
        flTextField* _valueText = NULL;

        ofPoint _draggablePoint;
        
    public:
        flPad2D(float width = 100, float height = 100);
        flPad2D(float width, float height, float left, float right, float top, float bottom);
        virtual ~flPad2D();
        
        virtual void label(flTextField* value);
        virtual void enabled(bool value);
        
        float xRatio();
        void xRatio(float value, bool dispatch = true);
        
        float yRatio();
        void yRatio(float value, bool dispatch = true);
        
        float xValue();
        void xValue(float value, bool dispatch = true);
        
        float yValue();
        void yValue(float value, bool dispatch = true);
        
        vec2 value();
        void value(float xValue, float yValue, bool dispatch = true);
        void value(vec2 value, bool dispatch = true);

        float rangeWidth();
        void rangeWidth(float value, bool dispatch = true);
        
        float rangeHeight();
        void rangeHeight(float value, bool dispatch = true);
        
        //------------------------------------------
        ofParameter<vec2>* _vec2Param = NULL;
        ofEventListeners _listeners;
        virtual inline void bind(ofParameter<vec2>& param) {
            _listeners.unsubscribeAll();
            _vec2Param = NULL;
            _bChangedByMyself["value"] = false;
            _bChangedByOfParm["value"] = false;
            
            _vec2Param = &param;
            _listeners.push(_vec2Param->newListener([&](vec2& val) {
                if(_bChangedByMyself["value"]) {
                    _bChangedByMyself["value"] = false;
                } else {
                    _bChangedByOfParm["value"] = true;
                    value(_vec2Param->get());
                }
            }));
            
            value(_vec2Param->get());
        }
        virtual inline void unbind() {
            _listeners.unsubscribeAll();
            _vec2Param = NULL;
        }
        //------------------------------------------
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _updateValue();        
        virtual void _changeValue(bool dispatch = true);
        
        virtual void _onOver();
        virtual void _onOut();
        virtual void _onPress();
        virtual void _onRelease();
        virtual void _onMove();
        
        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();
        
        virtual void _drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        virtual void _drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
        
    private:
        virtual void _mouseEventHandler(flEvent& event);
        void _uiEventHandler(flEvent& event);
    };
}

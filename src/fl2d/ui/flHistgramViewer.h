#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flHistgramViewerEvent.h"

namespace fl2d {
    
    class flHistgramViewer : public flSprite {
        
    public:
        
    protected:
        
    private:
        float _uiWidth;
        float _uiHeight;
        
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        
        flTextField* _label;
        
        float _value;
        float _tempValue;
        float _min;
        float _weight;        
        ofPoint* _startPos;
        
        //        float _average;
        
        ofPolyline _line;
        vector<float> _valueHistory;
        //        vector<float> _avelageHistroy;
        float _valueScale = 0.5f;
        //        vector<float> _valueHistory;
        
    public:
        flHistgramViewer(float width = 100, float height = 18);
        virtual ~flHistgramViewer();
        
        flTextField* label();
        void label(flTextField* value);
        
        inline float value() { return _value; }
        inline void value(float value, bool dispatch = true) {
            //            if(_value == value) return;
            
            _value = value;
            _valueHistory[_valueHistory.size() - 1] = _value;
            
            //            //------------------------------------------
            //            if(dispatch) {
            //                //イベント
            //                NumberDialerEvent* event = new NumberDialerEvent(NumberDialerEvent::CHANGE);
            //                //            event->_target = this;
            //                event->data<float>(_value);
            //                dispatchEvent(event);
            //            }
            //            //------------------------------------------
        }
        
        //        inline float average() { return _average; }
        
        inline float weight() { return _weight; };
        inline void weight(float value) { _weight = value; }
        
    protected:
        //virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        
        virtual void _over();
        virtual void _out();
        virtual void _press();
        virtual void _release();
        
    private:
        void _mouseEventHandler(flEvent& event);
    };
    
}

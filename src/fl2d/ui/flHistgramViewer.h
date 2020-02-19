#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flHistgramViewerEvent.h"

namespace fl2d {
    
    class flHistgramViewer : public flUIBase {
        
    public:
        
    protected:
        
    private:
        flTextField* _valueText;

        float _uiWidth;
        float _uiHeight;
        
        float _value;
        float _tempValue;
        float _min;
        float _weight;        
        ofPoint _startPos;
        
        //        float _average;
        
        ofPolyline _line;
        vector<float> _valueHistory;
        //        vector<float> _avelageHistroy;
        float _valueScale = 0.5f;
        //        vector<float> _valueHistory;
        
    public:
        flHistgramViewer(float width = 100, float height = 18);
        virtual ~flHistgramViewer();
        
        virtual void label(flTextField* value);
        
        inline float value() { return _value; }
        inline void value(float value, bool dispatch = true) {
//            if(_value == value) return;
            float preValue = _value;

            _value = value;
            _valueHistory[_valueHistory.size() - 1] = _value;
            
            //------------------------------------------
            if(preValue != _value) {
                _valueText->text(ofToString(_value, 2));

                //------------------------------------------
                if(dispatch) {
                    //イベント
                    flHistgramViewerEvent* event = new flHistgramViewerEvent(flHistgramViewerEvent::CHANGE);
                    //            event->_target = this;
                    event->__value = _value;
                    dispatchEvent(event);
                }
                //------------------------------------------
            }
        }
        
        //        inline float average() { return _average; }
        
        inline float weight() { return _weight; };
        inline void weight(float value) { _weight = value; }
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _over();
        virtual void _out();
        virtual void _press();
        virtual void _release();
        
        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();
        
        virtual void _drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);

    private:
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}

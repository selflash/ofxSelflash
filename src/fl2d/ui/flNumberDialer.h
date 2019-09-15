#pragma once

#include "ofMain.h"

#include "flmath.h"
#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flNumberDialerEvent.h"

namespace fl2d {
    
    class flNumberDialer : public flSprite {
        
    public:
        //水平
        static string HORIZONTALLY;
        //垂直
        static string VERTICALLY;
        
        flSprite* track;
        
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
        
        string _type;
        string _dragVector;
        
        flTextField* _valueText;
        float _value;
        float _tempValue;
        float _stepValue;
        
        float _max;
        float _min;
        
        float _weight;
        bool _roundEnabled;
        bool _invertEnabled;
        
        ofPoint* _startPos;
        
    public:
        flNumberDialer(float width = 100, float height = 18);
        virtual ~flNumberDialer();
        
        flTextField* label();
        void label(flTextField* value);
        
        string type();
        void type(string value);
        
        inline string dragVector() { return _dragVector; }
        inline void dragVector(string value) { _dragVector = value; }
        
        float value();
        void value(float value, bool dispatch = true);
        
        float stepValue();
        void stepValue(float value, bool dispatch = true);
        
        float min();
        void min(float value, bool dispatch = true);
        
        float max();
        void max(float value, bool dispatch = true);
        
        float weight();
        void weight(float value);
        
        bool roundEnabled();
        void roundEnabled(bool value);
        
        bool invertEnabled();
        void invertEnabled(bool value);
        
    protected:
        //virtual void _setup();
        virtual void _update();
        //virtual void _draw();
        
        virtual void _drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        
        virtual void _over();
        virtual void _out();
        virtual void _press();
        virtual void _release();
        
    private:
        void _mouseEventHandler(flEvent& event);
    };
    
}

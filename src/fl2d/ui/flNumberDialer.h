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
        
    protected:
        
    private:
        flSprite* _track;

        flTextField* _label;
        flTextField* _valueText;

        float _uiWidth;
        float _uiHeight;
        
        string _type;
        string _dragVector;
        
        float _value;
        float _tempValue;
        float _stepValue;
        
        float _max;
        float _min;
        
        float _weight;
        bool _roundEnabled;
        bool _invertEnabled;
        
        ofPoint _startPos;
        
        bool _enabled;

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
        
//        bool enabled();
//        void enabled(bool value);

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
        void _mouseEventHandler(flEvent& event);
    };
    
}

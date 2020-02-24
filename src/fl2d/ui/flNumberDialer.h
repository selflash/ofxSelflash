#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flNumberDialerEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flNumberDialer : public flUIBase {
        
    public:
        //水平
        static string HORIZONTALLY;
        //垂直
        static string VERTICALLY;
        
    protected:
        
    private:
        flSprite* _track;

        flTextField* _valueText;

        float _uiWidth;
        float _uiHeight;
        
        //direction of the slider.
        string _direction;
        string _dragDirection;
        
        float _value;
        float _tempValue;
        //Gets or sets a nonzero number that describes the unit of change between values.
        float _stepSize;
        
        float _max;
        float _min;
        
        float _weight;
        bool _roundEnabled;
        bool _invertEnabled;
        
        ofPoint _startPos;

    public:
        flNumberDialer(float width = 100, float height = 18);
        virtual ~flNumberDialer();
        
        virtual void label(flTextField* value);
        virtual void enabled(bool value);

        string direction();
        virtual void direction(string value);
        
        inline string dragDirection() { return _dragDirection; }
        inline void dragDirection(string value) { _dragDirection = value; }
        
        float value();
        void value(float value, bool dispatch = true);
        
        float stepSize();
        void stepSize(float value, bool dispatch = true);
        
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

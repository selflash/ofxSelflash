#pragma once

#include "ofMain.h"

#include "../../utils/MathUtil.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "../events/NumberDialerEvent.h"

namespace fl2d {
    
    class NumberDialer : public Sprite {
        
        public:
            //水平
            static string HORIZONTALLY;
            //垂直
            static string VERTICALLY;
        
            Sprite* track;
            
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

            TextField* _label;

            string _type;
            string _dragVector;
        
            TextField* _valueText;
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
            NumberDialer(float width = 100, float height = 18);
            virtual ~NumberDialer();
            
            TextField* label();
            void label(TextField* value);
        
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
            void _mouseEventHandler(Event& event);
    };
    
}

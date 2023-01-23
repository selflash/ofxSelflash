#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flNumericDialerEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flNumericDialer : public flUIBase {
        
        public:
            //水平
            static string HORIZONTALLY;
            //垂直
            static string VERTICALLY;
        
        protected:
        
        private:
            flSprite* _track = NULL;

            bool _roundEnabled = false;

            //direction of the slider.
            string _direction = HORIZONTALLY;
            string _dragDirection = VERTICALLY;

            float _uiWidth = 100;
            float _uiHeight = 18;
        
            float _min = numeric_limits<float>::quiet_NaN();
            float _max = numeric_limits<float>::quiet_NaN();
            //Gets or sets a nonzero number that describes the unit of change between values.
            float _stepSize = 1.0;
            float _tempValue = 0.0;
            float _value = 0.0;
        
            flTextField* _valueText = NULL;
            int _digit = 2;

            float _weight = 1.0;
            bool _invertEnabled = false;
            ofPoint _startPos;

        public:
            flNumericDialer(float width = 100);
            virtual ~flNumericDialer();
        
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
        
			//0.0 - 1.0
            float weight();
            void weight(float value);
        
            bool roundEnabled();
            void roundEnabled(bool value);     

            int digit();
            void digit(int value);
        
            bool invertEnabled();
            void invertEnabled(bool value);

        //------------------------------------------
        ofParameter<float>* _floatParam = NULL;
		ofParameter<int>* _intParam = NULL;
        ofEventListeners _paramListeners;
        virtual inline void bind(ofParameter<float>& param) {
            _paramListeners.unsubscribeAll();
            _floatParam = NULL;
			_intParam = NULL;
            _bChangedByMyself["value"] = false;
            _bChangedByOfParm["value"] = false;
            
            _floatParam = &param;
            _paramListeners.push(_floatParam->newListener([&](float& val) {
                if(_bChangedByMyself["value"]) {
                    _bChangedByMyself["value"] = false;
                } else {
                    _bChangedByOfParm["value"] = true;
                    value(val);
                }
            }));
            
            _bChangedByOfParm["value"] = true;
            value(_floatParam->get());
			_bChangedByOfParm["value"] = false;
		}
		virtual inline void bind(ofParameter<int>& param) {
            _paramListeners.unsubscribeAll();
            _floatParam = NULL;
			_intParam = NULL;
            _bChangedByMyself["value"] = false;
            _bChangedByOfParm["value"] = false;
            
			_intParam = &param;
            _paramListeners.push(_intParam->newListener([&](int& val) {
                if(_bChangedByMyself["value"]) {
                    _bChangedByMyself["value"] = false;
                } else {
                    _bChangedByOfParm["value"] = true;
                    value(val);
                }
            }));
            
            _bChangedByOfParm["value"] = true;
            value(_intParam->get());
			_bChangedByOfParm["value"] = false;
		}
        virtual inline void unbind() {
            _paramListeners.unsubscribeAll();
            _floatParam = NULL;
			_intParam = NULL;
        }
        //------------------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _dispatchEvent();

            virtual void _onOver();
            virtual void _onOut();
            virtual void _onPress();
            virtual void _onRelease();

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

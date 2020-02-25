#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flJoyStick1Event.h"

namespace fl2d {
    
    class flJoyStick1 : public flUIBase {
        public:
            //水平
            static string HORIZONTALLY;
            //垂直
            static string VERTICALLY;
        
            flSprite* lever = NULL;
        
        protected:
        
        private:
            string _type = HORIZONTALLY;

            flTextField* _valueText = NULL;
            int _digit = 2;

            float _uiLength = 0.0;
            float _uiWidth = 0.0;
            float _uiHeight = 0.0;

            float _leverRadius = 0.0;
            float _maxDistance = 0.0;
            ofPoint _center;
            ofPoint _draggablePoint;
            bool _flg = false;
            float _targetValue = 0.0;

            float _value = 0.0;

        public:
            flJoyStick1(float length = 100);
            virtual ~flJoyStick1();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            string type();
            void type(string value);
        
            float value();
        
            //-1.0 ~ 1.0
            void moveLever(float value = 1.0);
        
            //------------------------------------------
            ofParameter<float>* _floatParam = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<float>& param) {
                _listeners.unsubscribeAll();
                _floatParam = NULL;
                
                _floatParam = &param;
                _listeners.push(_floatParam->newListener([&](float& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        moveLever(_floatParam->get());
                    }
                }));
                
//                moveLever(_floatParam->get());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _floatParam = NULL;
            }
            //------------------------------------------
        
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _changeValue(bool dispatch = true);

//            virtual void _areaOver();
//            virtual void _areaOut();
//            virtual void _areaPress();
//            virtual void _areaRelease();
        
            virtual void _leverOver();
            virtual void _leverOut();
            virtual void _leverPress();
            virtual void _leverRelease();
            virtual void _leverMove();
        
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
    };
    
}

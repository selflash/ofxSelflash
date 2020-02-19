#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flSlider.h"
#include "flColorSliderEvent.h"

namespace fl2d {
    
    class flColorSlider : public flUIBase {
        
        public:
            flSlider* redSlider = NULL;
            flSlider* greenSlider = NULL;
            flSlider* blueSlider = NULL;
            flSlider* alphaSlider = NULL;
        
        protected:
            flTextField* _hexText = NULL;
            flTextField* _redLabel = NULL;
            flTextField* _greenLabel = NULL;
            flTextField* _blueLabel = NULL;
            flTextField* _alphaLabel = NULL;
        
            ofColor _colorValue;
            int _hexValue;
        
        private:
        
        public:
            flColorSlider(float width, bool alphaEnabled = true);
            flColorSlider(int r, int g, int b);
            flColorSlider(int r, int g, int b, int a);
            flColorSlider(float width = 200, int r = 255, int g = 255, int b = 255, int a = 255);
            virtual ~flColorSlider();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            virtual ofColor colorValue();
            virtual void colorValue(ofColor& value, bool dispatch = true);
        
            virtual int hexValue();
            virtual void hexValue(int value, bool dispatch = true);
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int redValue();
            virtual void redValue(int value, bool dispatch = true);
            template <class T>
            const T redValue() {
                if (typeid(T) == typeid(float)) {
                    return float(redSlider->value()) / 255.0;
                } else {
                    return redSlider->value();
                }
            }
            template <class T>
            void redValue(const T& value, bool dispatch = true) {
                if (typeid(T) == typeid(float)) {
                    redSlider->value(value * 255.0, dispatch);
                } else {
                    redSlider->value(value, dispatch);
                }
            }
            //----------------------------------
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int greenValue();
            virtual void greenValue(int value, bool dispatch = true);
            template <class T>
            const T greenValue() {
                if (typeid(T) == typeid(float)) {
                    return float(greenSlider->value()) / 255.0;
                } else {
                    return greenSlider->value();
                }
            }
            template <class T>
            void greenValue(const T& value, bool dispatch = true) {
                if (typeid(T) == typeid(float)) {
                    greenSlider->value(value * 255.0, dispatch);
                } else {
                    greenSlider->value(value, dispatch);
                }
            }
            //----------------------------------
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int blueValue();
            virtual void blueValue(int value, bool dispatch = true);
            template <class T>
            const T blueValue() {
                if (typeid(T) == typeid(float)) {
                    return float(blueSlider->value()) / 255.0;
                } else {
                    return blueSlider->value();
                }
            }
            template <class T>
            void blueValue(const T& value, bool dispatch = true) {
                if (typeid(T) == typeid(float)) {
                    blueSlider->value(value * 255.0, dispatch);
                } else {
                    blueSlider->value(value, dispatch);
                }
            }
            //----------------------------------
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int alphaValue();
            virtual void alphaValue(int value, bool dispatch = true);
            template <class T>
            const T alphaValue() {
                if (typeid(T) == typeid(float)) {
                    return float(alphaSlider->value()) / 255.0;
                } else {
                    return alphaSlider->value();
                }
            }
            template <class T>
            void alphaValue(const T& value, bool dispatch = true) {
                if (typeid(T) == typeid(float)) {
                    alphaSlider->value(value * 255.0, dispatch);
                } else {
                    alphaSlider->value(value, dispatch);
                }
            }
            //----------------------------------
        
            //----------------------------------
            ofParameter<ofColor>* _param;
            virtual inline void bind(ofParameter<ofColor>& param) {
                _listeners.unsubscribeAll();
                _param = NULL;
                
                _param = &param;
                _listeners.push(_param->newListener([&](ofColor& val) {
                    if(_changedValueByMyself) {
                        _changedValueByMyself = false;
                    } else {
                        colorValue(val);
                    }
                }));
                
                hexValue(_param->get().getHex());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _param = NULL;
            }
            //----------------------------------

        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();

            virtual void _changeValue(bool dispatch = true);

        private:
            void _updateColor();

            void _eventHandler(flEvent& event);

    };
    
}

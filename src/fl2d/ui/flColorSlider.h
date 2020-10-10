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
            int _digit = 2;

            flTextField* _hexText = NULL;
            flTextField* _redLabel = NULL;
            flTextField* _greenLabel = NULL;
            flTextField* _blueLabel = NULL;
            flTextField* _alphaLabel = NULL;
        
            ofColor _colorValue;
            int _hexValue = 0xffffff;
        
        private:
        
        public:
            flColorSlider(float width, bool alphaEnabled = true);
            flColorSlider(int red, int green, int blue);
            flColorSlider(int red, int green, int blue, int alpha);
            flColorSlider(float width = 200, int red = 255, int green = 255, int blue = 255, int alpha = 255);
            virtual ~flColorSlider();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            virtual ofColor colorValue();
//            virtual void colorValue(ofColor& value, bool dispatch = true);
            virtual void colorValue(ofColor value, bool dispatch = true);

            virtual int hexValue();
            virtual void hexValue(int value, bool dispatch = true);
        
            //----------------------------------
            //å^ÇìnÇ≥Ç»Ç©Ç¡ÇΩÇÁintÇ≈èàóùÇ≥ÇÍÇÈ
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
            //å^ÇìnÇ≥Ç»Ç©Ç¡ÇΩÇÁintÇ≈èàóùÇ≥ÇÍÇÈ
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
            //å^ÇìnÇ≥Ç»Ç©Ç¡ÇΩÇÁintÇ≈èàóùÇ≥ÇÍÇÈ
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
            //å^ÇìnÇ≥Ç»Ç©Ç¡ÇΩÇÁintÇ≈èàóùÇ≥ÇÍÇÈ
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
			ofParameter<ofFloatColor>* _floatColorParam = NULL;
			ofParameter<ofColor>* _colorParam = NULL;
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<ofFloatColor>& param) {
                _listeners.unsubscribeAll();
				_floatColorParam = NULL;
                _colorParam = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

				_floatColorParam = &param;
                _listeners.push(_floatColorParam->newListener([&](ofFloatColor& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        colorValue(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                hexValue(_floatColorParam->get().getHex());
				_bChangedByOfParm["value"] = false;
			}            
			virtual inline void bind(ofParameter<ofColor>& param) {
                _listeners.unsubscribeAll();
				_floatColorParam = NULL;
                _colorParam = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

                _colorParam = &param;
                _listeners.push(_colorParam->newListener([&](ofColor& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        colorValue(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                hexValue(_colorParam->get().getHex());
				_bChangedByOfParm["value"] = false;
			}
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
				_floatColorParam = NULL;
                _colorParam = NULL;
            }
            //----------------------------------

        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();

            virtual void _dispatchEvent();

        private:
            void _updateColor();

            void _eventHandler(flEvent& event);

    };
    
}

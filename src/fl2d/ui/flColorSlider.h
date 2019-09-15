#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flSlider.h"
#include "flColorSliderEvent.h"

namespace fl2d {
    
    class flColorSlider : public flSprite {
        
    public:
        flSlider* redSlider;
        flSlider* greenSlider;
        flSlider* blueSlider;
        flSlider* alphaSlider;
        
    protected:
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        flTextField* _label;
        flTextField* _label1Text;
        flTextField* _label2Text;
        flTextField* _label3Text;
        flTextField* _label4Text;
        
        flTextField* _hexText;
        
        ofFloatColor _colorValue;
        int _hexValue;
        
    private:
        
        
    public:
        flColorSlider(float width, bool alpha = true);
        flColorSlider(int r, int g, int b);
        flColorSlider(int r, int g, int b, int a);
        flColorSlider(float width = 200, int r = 255, int g = 255, int b = 255, int a = 255);
        virtual ~flColorSlider();
        
        flTextField* label();
        void label(flTextField* value);
        
        void textColor(int color);
        
        virtual ofFloatColor colorValue();
        virtual void colorValue(ofFloatColor& value, bool dispatch = true);
        
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
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _eventHandler(flEvent& event);
        
    };
    
}

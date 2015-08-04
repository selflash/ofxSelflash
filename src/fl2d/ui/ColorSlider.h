#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "Slider.h"
#include "../events/ColorSliderEvent.h"

namespace fl2d {
    
    class ColorSlider : public Sprite {
        
    public:
        Slider* redSlider;
        Slider* greenSlider;
        Slider* blueSlider;
        Slider* alphaSlider;
        
    protected:
        TextField* _labelText;
        TextField* _label1Text;
        TextField* _label2Text;
        TextField* _label3Text;
        TextField* _label4Text;
        
        TextField* _hexText;
        
        ofFloatColor* _colorValue;
        int _hexValue;
        
    private:

        
    public:
        ColorSlider(float width = 200);
        ~ColorSlider();
        
        virtual string label();
        virtual void label(string value, int color = 0xffffff);
        
        virtual void textColor(int color = 0xffffff);
        
        virtual const ofFloatColor& colorValue();
        virtual void colorValue(const ofFloatColor& value, bool dispatch = true);

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
        void _eventHandler(Event& event);

    };
    
}
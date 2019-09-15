#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flButtonEvent.h"

namespace fl2d {
    
    class flButton : public flSprite {
        
    public:
        
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
        ofFloatColor _deactiveColor;
        
        flTextField* _label;
        string _labelTextNotSelected;
        string _labelTextSelected;
        
        bool _toggleEnabled;
        bool _selected;
        
        void* _pointerValue;
        string _stringValue;
        float _floatValue;
        int _intValue;
        
        bool _enabled;
        
    public:
        flButton(float width = 100, float height = 18);
        virtual ~flButton();
        
        flTextField* label();
        
        string labelText();
        void labelText(string value, string state = "default");
        
        inline ofFloatColor backgroundNormalColor() { return _normalColor; }
        inline void backgroundNormalColor(int color) {
            _normalColor.setHex(color);
            
            if(_enabled) {
                _label->textColor(0xffffff);
            } else {
                _label->textColor(0x999999);
            }
            
            flGraphics* g;
            g = graphics();
            g->clear();
            g->lineStyle(1, _lineColor.getHex());
            if(_enabled) {
                g->beginFill(_normalColor.getHex());
            } else {
                g->beginFill(_normalColor.getHex() * 0.5);
            }
            g->drawRect(0, 0, _uiWidth, _uiHeight);
            g->endFill();
        }
        
        bool toggleEnabled();
        void toggleEnabled(bool value);
        
        bool selected();
        void selected(bool value, bool dispatch = true);
        
        void* pointerValue();
        void pointerValue(void* value);
        
        string stringValue();
        void stringValue(string value);
        
        float floatValue();
        void floatValue(float value);
        
        int intValue();
        void intValue(int value);
        
        bool enabled();
        void enabled(bool value);
        
    protected:
        //virtual void _setup();
        //virtual void _update();
        //virtual void _draw();
        
        virtual void _over();
        virtual void _out();
        virtual void _press();
        virtual void _release();
        
    private:
        void _mouseEventHandler(flEvent& event);
    };
    
}

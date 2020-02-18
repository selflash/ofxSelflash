#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flButtonEvent.h"

namespace fl2d {
    
    class flButton : public flUIBase {
        
    public:
        
    protected:
        
    private:
        float _uiWidth;
        float _uiHeight;
        
        flTextField* _buttonLabel;
        string _labelTextNotSelected;
        string _labelTextSelected;
        
        bool _toggleEnabled;
        bool _selected;
        
        void* _pointerValue;
        string _stringValue;
        float _floatValue;
        int _intValue;
        
    public:
        flButton(float width = 100, float height = 18);
        virtual ~flButton();
        
        virtual flTextField* label();
        virtual void label(flTextField* value);

        string labelText();
        void labelText(string value, string state = "default");
        
//        inline ofFloatColor backgroundNormalColor() { return _normalColor; }
//        inline void backgroundNormalColor(int color) {
//            _normalColor.setHex(color);
//            
//            if(_enabled) {
//                _label->textColor(0xffffff);
//            } else {
//                _label->textColor(0x999999);
//            }
//            
//            flGraphics* g;
//            g = graphics();
//            g->clear();
//            if(_enabled) {
//                g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
//                g->beginFill(_normalColor.getHex());
//            } else {
//                g->lineStyle(1, flDefinition::UI_LINE_DISABLE_NORMAL_COLOR.getHex());
//                g->beginFill(_normalColor.getHex() * 0.5);
//            }
//            g->drawRect(0, 0, _uiWidth, _uiHeight);
//            g->endFill();
//        }
        
        virtual bool enabled();
        virtual void enabled(bool value);

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
        
    protected:
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
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}

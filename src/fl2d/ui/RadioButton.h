#pragma once

#include "ofMain.h"

#include "FlashConfig.h"
#include "Shape.h"
#include "Sprite.h"
#include "TextField.h"
#include "Event.h"
#include "RadioButtonEvent.h"

namespace fl2d {
    class RadioButtonGroup;
    class RadioButton : public Sprite {
        friend class RadioButtonGroup;
        
    public:
        
    protected:
        
    private:
        float _uiWidth;
        float _uiHeight;
        
        ofFloatColor _labelNormalColor;
        ofFloatColor _labelOverColor;
        ofFloatColor _labelActiveColor;
        ofFloatColor _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        ofFloatColor _deactiveColor;
        
        TextField* _label;
        
        bool _selected;
        
        bool _enabled;
        
        bool _hitAreaAlpha = 0.0;
        RadioButtonGroup* _groupOwner;
        
    public:        
        virtual ~RadioButton();
        
        TextField* label();
        
        string labelText();
        void labelText(string value);
        
        bool selected();
        void selected(bool value, bool dispatch = true);
        
        bool enabled();
        void enabled(bool value);
        
        inline void activeColor(ofFloatColor value) { _activeColor = value; };
        
    protected:
        virtual void _normal();
        virtual void _over();
        virtual void _press();
        
        virtual void _drawGraphics(const ofFloatColor& outerColor);
        virtual void _drawGraphics(const ofFloatColor& outerColor, const ofFloatColor& innerColor);
        
        
    private:
        RadioButton(float width = 100);
        
        void _setGroupOwner(RadioButtonGroup* groupOwner);
        
        void _mouseEventHandler(Event& event);
    };
    
    class RadioButton;
    class RadioButtonGroup : public EventDispatcher {
        friend class RadioButton;
    public:
        
    private:
        vector<RadioButton*> _radioButtonList;
        
    public:
        RadioButtonGroup();
        virtual ~RadioButtonGroup();
        
        RadioButton* createRadioButton();
        void removeRadioButton(RadioButton* radioButton);
        
    private:
        void _notice(RadioButton* radioButton);
        void _uiEventHandler(Event& event);
    };
}

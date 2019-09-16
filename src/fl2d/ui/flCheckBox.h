#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flEvent.h"
#include "flCheckBoxEvent.h"

namespace fl2d {
    
    class flCheckBox : public flSprite {
        
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
        
        flTextField* _label;
        
        bool _selected;
        
        bool _enabled;
        
        bool _hitAreaAlpha = 0.0;
        
        int _shapeType = 0;
        
    public:
        flCheckBox(float width = 100);
        virtual ~flCheckBox();
        
        flTextField* label();
        
        string labelText();
        void labelText(string value);
        
        bool selected();
        void selected(bool value, bool dispatch = true);
        
        bool enabled();
        void enabled(bool value);
        
        inline void activeColor(ofFloatColor value) { _activeColor = value; };

        inline int shapeType() { return _shapeType; };
        inline void shapeType(int value) { _shapeType = value; };

    protected:
        virtual void _normal();
        virtual void _over();
        virtual void _press();
        
        virtual void _drawGraphics(const ofFloatColor& outerColor);
        virtual void _drawGraphics(const ofFloatColor& outerColor, const ofFloatColor& innerColor);
        
    private:
        
        void _mouseEventHandler(flEvent& event);
    };
    
}

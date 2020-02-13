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
        
        flTextField* _label;
        
        bool _selected;
        
        bool _enabled;
        
        float _hitAreaAlpha = 0.0;
        
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
        
//        inline void activeColor(ofFloatColor value) { _activeColor = value; };

        inline int shapeType() { return _shapeType; };
        inline void shapeType(int value) {
            _shapeType = value;
            if(_enabled) {
                if(_selected) {
                    _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
                    _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
                } else {
                    _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
                    _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR);
                }
            } else {
                if(_selected) {
                    _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
                    _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
                } else {
                    _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
                    _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR);
                }
            }
        };

    protected:
        virtual void _over();
        virtual void _out();
        virtual void _down();
        virtual void _up();

        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();

        virtual void _drawGraphics(const ofColor& outerColor);
        virtual void _drawGraphics(const ofColor& outerColor, const ofFloatColor& innerColor);
        
    private:

        void _mouseEventHandler(flEvent& event);
    };
    
}

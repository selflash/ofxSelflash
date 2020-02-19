#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flCheckBoxEvent.h"

namespace fl2d {
    
    class flCheckBox : public flUIBase {
        
    public:
        
    protected:
        
    private:
        float _uiWidth;
        float _uiHeight;
        
        bool _selected = false;
        float _hitAreaAlpha = 0.0;        
        int _shapeType = 0;
        
    public:
        flCheckBox(float width = 100);
        virtual ~flCheckBox();
        
        virtual flTextField* label();
        virtual void label(flTextField* value);

        string labelText();
        void labelText(string value);
        
        bool selected();
        void selected(bool value, bool dispatch = true);
        
        virtual bool enabled();
        virtual void enabled(bool value);
        
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
        virtual void _press();
        virtual void _release();

        virtual void _setNormalColor();
        virtual void _setOverColor();
        virtual void _setSelectedOverColor();
        virtual void _setActiveColor();
        virtual void _setDisableNormalColor();
        virtual void _setDisableActiveColor();

        virtual void _drawGraphics(const ofColor& outerColor);
        virtual void _drawGraphics(const ofColor& outerColor, const ofFloatColor& innerColor);
        
    private:
        inline void _mouseEventHandler(flEvent& event);
    };
    
}

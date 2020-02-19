#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flEvent.h"
#include "flRadioButtonEvent.h"

namespace fl2d {
    class flRadioButtonGroup;
    class flRadioButton : public flUIBase {
        friend flRadioButtonGroup;
        
        public:
        
        protected:
        
        private:
            float _uiWidth = 0.0;
            float _uiHeight = 0.0;
        
            float _hitAreaAlpha = 0.0;
            int _shapeType = 1;
            bool _selected = false;

            flRadioButtonGroup* _groupOwner = NULL;
        
        public:
            virtual void label(flTextField* value);
            virtual void enabled(bool value);

            string labelText();
            void labelText(string value);
        
            bool selected();
            void selected(bool value, bool dispatch = true);
        
            inline int shapeType() { return _shapeType; };
            inline void shapeType(int value) {
                _shapeType = value;
                
                if(_enabled) {
                    if(_selected) {
                        if(isMouseOver()) {
                            _setOverColor();
                        } else {
                            _setActiveColor();
                        }
                    } else {
                        if(isMouseOver()) {
                            _setSelectedOverColor();
                        } else {
                            _setNormalColor();
                        }
                    }
                } else {
                    if(!_selected) {
                        _setDisableNormalColor();
                    } else {
                        _setDisableActiveColor();
                    }
                }
            };
        
        protected:
            flRadioButton(float width = 100);
            virtual ~flRadioButton();

            virtual void _setup();
            virtual void _update();
            virtual void _draw();

            virtual void _changeValue(bool dispatch = true);

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
            virtual void _drawGraphics(const ofColor& outerColor, const ofColor& innerColor);
        
        private:
            void _setGroupOwner(flRadioButtonGroup* groupOwner);
            virtual void _mouseEventHandler(flEvent& event);
    };
    
    class flRadioButton;
    class flRadioButtonGroup : public flEventDispatcher {
        friend flRadioButton;
        
        public:
        
        private:
            vector<flRadioButton*> _radioButtonList;
        
        public:
            flRadioButtonGroup();
            virtual ~flRadioButtonGroup();
        
            flRadioButton* createRadioButton();
            flRadioButton* removeRadioButton(flRadioButton* radioButton);
        
        private:
            void _notice(flRadioButton* radioButton, string message);
            void _uiEventHandler(flEvent& event);
    };
}

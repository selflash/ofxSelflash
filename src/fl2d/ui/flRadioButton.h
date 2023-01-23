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

            virtual void _dispatchEvent();

            virtual void _onOver();
            virtual void _onOut();
            virtual void _onPress();
            virtual void _onRelease();
        
            virtual void _setNormalColor();
            virtual void _setOverColor();
            virtual void _setSelectedOverColor();
            virtual void _setActiveColor();
            virtual void _setDisableNormalColor();
            virtual void _setDisableActiveColor();

            virtual void _drawGraphics(const ofColor& outerColor, float thickness = 1.0);
            virtual void _drawGraphics(const ofColor& outerColor, const ofColor& innerColor, float thickness = 1.0);
        
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
            bool _toolTipEnabled = false;
            string _toolTipText = "";
        
        public:
            flRadioButtonGroup();
            virtual ~flRadioButtonGroup();
        
            flRadioButton* createRadioButton();
            flRadioButton* removeRadioButton(flRadioButton* radioButton);
        
            bool toolTipEnabled();
            void toolTipEnabled(bool value);
            inline string toolTipText() { return _toolTipText; }
            inline void toolTipText(string value) {
                _toolTipText = value;
                vector<flRadioButton*>::iterator it = _radioButtonList.begin();
                while (it != _radioButtonList.end()) {
                    flRadioButton* radioButton = ((flRadioButton*)*it);
                    radioButton->toolTipText(_toolTipText);
                }
            }

        private:
            void _notice(flRadioButton* radioButton, string message);
            void _uiEventHandler(flEvent& event);
    };
}

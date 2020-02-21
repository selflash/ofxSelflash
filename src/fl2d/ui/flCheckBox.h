#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flCheckBoxEvent.h"

namespace fl2d {
    
    class flCheckBox : public flUIBase {
        
        public:
        
        protected:
        
        private:
            float _uiWidth = 0.0;
            float _uiHeight = 0.0;

            float _hitAreaAlpha = 0.0;
            int _shapeType = 0;
            bool _selected = false;

        public:
            flCheckBox(float width = 100);
            virtual ~flCheckBox();
        
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
            }
        
            //------------------------------------------
            ofParameter<bool>* _boolParam = NULL;
            virtual inline void bind(ofParameter<bool>& param) {
                _listeners.unsubscribeAll();
                _boolParam = NULL;
                
                _boolParam = &param;
                _listeners.push(_boolParam->newListener([&](bool& val) {
                    if(_bChangedByMyself) {
                        _bChangedByMyself = false;
                    } else {
                        _bChangedByOfParm = true;
                        selected(val);
                    }
                }));
                
                _bChangedByOfParm = true;
                selected(_boolParam->get());
            }
            virtual inline void unbind() {
                _listeners.unsubscribeAll();
                _boolParam = NULL;
            }
            //------------------------------------------

        protected:
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
            virtual void _drawGraphics(const ofColor& outerColor, const ofFloatColor& innerColor);
        
        private:
            virtual void _mouseEventHandler(flEvent& event);
    };
    
}

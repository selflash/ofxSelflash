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
			ofParameter<bool> _selected = false;

        public:
            flCheckBox(float width = 100);
            virtual ~flCheckBox();
        
			virtual flTextField* label();
            virtual void label(flTextField* value);

			virtual bool enabled();
			virtual void enabled(bool value);

            string labelText();
            void labelText(string value);
        
			ofParameter<bool>& selected();
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
            ofEventListeners _listeners;
            virtual inline void bind(ofParameter<bool>& param) {
                _listeners.unsubscribeAll();
                _boolParam = NULL;
                _bChangedByMyself["value"] = false;
                _bChangedByOfParm["value"] = false;

                _boolParam = &param;
                _listeners.push(_boolParam->newListener([&](bool& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        _bChangedByOfParm["value"] = true;
                        selected(val);
                    }
                }));
                
                _bChangedByOfParm["value"] = true;
                selected(_boolParam->get());
				_bChangedByOfParm["value"] = false;
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

            virtual void _drawGraphics(const ofColor& outerColor);
            virtual void _drawGraphics(const ofColor& outerColor, const ofFloatColor& innerColor);
        
        private:
            virtual void _mouseEventHandler(flEvent& event);
    };
    
}

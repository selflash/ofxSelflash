#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flButtonEvent.h"

namespace fl2d {
    
    class flButton : public flUIBase {
        
        public:
        
        protected:
        
        private:
            float _uiWidth = 0.0;
            float _uiHeight = 0.0;
        
            flTextField* _buttonLabel = NULL;
            string _labelTextNotSelected = "";
            string _labelTextSelected = "";
        
            bool _toggleEnabled = false;
            bool _selected = false;
        
            void* _pointerValue = NULL;
            string _stringValue = "";
            float _floatValue = 0.0;
            int _intValue = 0;
        
            bool _flg = false;

        public:
            flButton(float width = 100, float height = 18);
            virtual ~flButton();
        
            virtual void label(flTextField* value);
        
            virtual void enabled(bool value);

            string labelText();
            void labelText(string value, string state = "default");

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
        
            void press(bool dispatch = true);
        
            //------------------------------------------
            ofParameter<bool>* _boolParam = NULL;
            virtual inline void bind(ofParameter<bool>& param) {
                _listeners.unsubscribeAll();
                _boolParam = NULL;
                
                _boolParam = &param;
                _listeners.push(_boolParam->newListener([&](bool& val) {
                    if(_bChangedByMyself["value"]) {
                        _bChangedByMyself["value"] = false;
                    } else {
                        if(val == true) {
                            _press();
                        }
//                        value(val);
                    }
                }));
                
//                value(_floatParam->get());
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
        
            virtual void _drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);

        private:
            virtual void _mouseEventHandler(flEvent& event);
    };
    
}

#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"

namespace fl2d {
    
    class flBasicController : public flSprite, public flAbstractController {
        public:

        protected:
            float _backWidth = 0.0;
            float _backHeight = 0.0;
            //float _minBackWidth = 0.0;
            float _minBackHeight = 0.0;
			float _maxBackWidth = 0.0;
			float _maxBackHeight = 0.0;
			float _normalBackWidth = 0.0;
            float _normalBackHeight = 0.0;

			flGraphics _minimalGraphics;
			flGraphics _maximumGraphics;
			flGraphics _normalGraphics;

			float _margin = 6.0;
			float _marginLeft = 6.0;
			float _marginTop = (6.0 + 18) + 6.0;
			float _spacing = 150.0;
			float _lineSpacing = 18 + 6.0;

			flSprite* _titleBar = NULL;
			float _titleBarHeight = (_margin + 18) + _margin;
			string _title = "";
        
            bool _isMinimize = false;
            bool _isMaximize = false;
        
            bool _onTop = true;
            bool _dragEnabled = true;

			bool _isLocked = false;

			ofEventListeners _listeners;
        
        private:
        
        public:
            flBasicController();
            virtual ~flBasicController();
        
            virtual void setup();
        
            virtual void minimize();
            virtual void maximize();
            virtual void normalize();
            virtual void resize(float w, float h);

			virtual inline string title() { return _title; }
			virtual inline void title(string value) { _title = value; }
        
            virtual inline float backWidth() { return _backWidth; }
            virtual inline float backHeight() { return _backHeight; }
            //virtual inline float minBackWidth() { return _minBackWidth; }
            virtual inline float minBackHeight() { return _minBackHeight; }
            virtual inline float normalBackWidth() { return _normalBackWidth; }
            virtual inline float normalBackHeight() { return _normalBackHeight; }
        
            virtual inline bool dragEnabled() { return _dragEnabled; }
            virtual inline void dragEnabled(bool value) {
                _dragEnabled = value;
                useHandCursor(_dragEnabled);

                if(!_dragEnabled) {
                    if(stage() != NULL) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerMouseEventHandler);
                    stopDrag();
                }
            }

			virtual bool lock() { return _isLocked; }
			virtual void lock(bool value) { 
				_isLocked = value;
				
				for (int i = 0; i < numChildren(); i++) {
					flDisplayObject* displayObject = (flDisplayObject*)getChildAt(i);
					//ofLog(OF_LOG_VERBOSE) << "displayObject->name() = " << displayObject->name();

					if (displayObject->typeID() == FL_TYPE_UIBASE) {
						//ofLog(OF_LOG_VERBOSE) << "displayObject.name = " << displayObject->name();
						((flUIBase*)displayObject)->enabled(_isLocked);
					}
				}
			}
        
        protected:
			virtual void _setup();
			//virtual void _update();
			virtual void _draw();

			virtual void _relocateTitleBarButtons();

            virtual void _flBasicControllerEventHandler(flEvent& event);
            virtual void _flBasicControllerMouseEventHandler(flEvent& event);

        private:
        
    };
    
}

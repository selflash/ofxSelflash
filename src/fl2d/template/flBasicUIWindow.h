#pragma once

#include "ofMain.h"
#include "flBasicDraggableObject.h"
#include "flAbstractController.h"

namespace fl2d {
    
    class flBasicUIWindow : public flBasicDraggableObject, public flAbstractController {
		public:
        
		protected:
			float _windowWidth = 0.0;
			float _windowHeight = 0.0;

			float _defaultWindowWidth = 0.0;
			float _defaultWindowHeight = 0.0;

			float _minimumWindowWidth = 0.0;
			float _minimumWindowHeight = 0.0;

			float _maximumWindowWidth = 0.0;
			float _maximumWindowHeight = 0.0;

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

			flSprite* _menuBar = NULL;
			int _menuBarHeight = (_margin + 18) + _margin;

			bool _isMinimize = false;
			bool _isMaximize = false;
			bool _preModeIsMaximize = false;

			bool _isLocked = false;

			ofEventListeners _listeners;

			bool _dragEnabled = true;
			bool _preDragEnabled = false;
			bool _moveFrontOnSelect = true;        

			bool _resizable = false;
			flBasicDraggableObject* _sizingHandle = NULL;

		private:
        
		public:
			flBasicUIWindow();
			virtual ~flBasicUIWindow();

			//virtual void setup();
			//virtual void update();
			//virtual void draw();

			virtual void minimize();
			virtual void normalize();
			virtual void maximize();
			virtual void resize(float w, float h);

			virtual inline bool resizable() { return _resizable; }
			virtual inline void resizable(bool value) { 
				_resizable = value;
				if(_sizingHandle) _sizingHandle->visible(_resizable);
			}

			virtual inline string title() { return _title; }
			virtual inline void title(string value) { _title = value; }

			virtual inline float windowWidth() { return _windowWidth; }
			virtual inline float windowHeight() { return _windowHeight; }

			virtual inline float defaultWindowWidth() { return _defaultWindowWidth; }
			virtual inline float defaultWindowHeight() { return _defaultWindowHeight; }

			virtual inline float minimumWindowWidth() { return _minimumWindowWidth; }
			virtual inline float minimumWindowHeight() { return _minimumWindowHeight; }

			virtual inline float maximumWindowWidth() { return _maximumWindowWidth; }
			virtual inline float maximumWindowHeight() { return _maximumWindowHeight; }

			virtual bool lock();
			virtual void lock(bool value);

		protected:
			virtual void _setup();
			virtual void _afterSetup();
			virtual void _update();
			virtual void _draw();

			virtual void _relocateTitleBarButtons();

			virtual void _eventHandler(flEvent& event);
			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

		private:
        
    };
    
}

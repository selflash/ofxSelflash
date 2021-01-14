#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"
#include "flBasicDraggableObject.h"

namespace fl2d {

	class flBasicImageViewer : public flBasicDraggableObject, public flAbstractController  {
		public:

		protected:
			float _backWidth;
			float _backHeight;
			float _minBackWidth;
			float _minBackHeight;
			float _normalBackWidth;
			float _normalBackHeight;

			int _mode = 0;

			bool _isLocked = false;

			ofEventListeners _listeners;

			bool _isActive = false;

			flBasicDraggableObject* rightBottomCorner;

			flBitmap* _bitmap = NULL;
			float _defaultImageWidth;
			float _defaultImageHeight;

		private:

		public:
			flBasicImageViewer(flBitmap* bitmap, int w, int h);
			virtual ~flBasicImageViewer();

			virtual void setup();

			bool active();
			void active(bool value);

			virtual void minimize();
			virtual void normalize();
			virtual void maximize();
			virtual void resize(float w, float h);

			virtual inline float backWidth() { return _backWidth; }
			virtual inline float backHeight() { return _backHeight; }
			virtual inline float minBackWidth() { return _minBackWidth; }
			virtual inline float minBackHeight() { return _minBackHeight; }
			virtual inline float normalBackWidth() { return _normalBackWidth; }
			virtual inline float normalBackHeight() { return _normalBackHeight; }

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
			virtual void _update();
			virtual void _draw();

			virtual void _updateGraphics(int x, int y);

			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

		private:

	};

}
#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicUIWindow.h"

namespace fl2d {

	class flBasicImageViewer : public flBasicUIWindow {
		public:

		protected:
			flBitmap* _bitmap = NULL;
			float _defaultImageWidth;
			float _defaultImageHeight;

			bool _isActive = false;
			float _scaleOnActive = 2.0;

			bool _colorPickerEnabled = false;
			ofPoint _point;
			ofParameter<ofFloatColor> _pickedColor = ofFloatColor(0.0, 0.0, 0.0, 0.0);

		private:

		public:
			flBasicImageViewer(flBitmap* bitmap, int w, int h);
			virtual ~flBasicImageViewer();

			//virtual void draw();

			virtual void normalize();
			virtual void maximize();
			virtual void resize(float w, float h);

			bool active();
			void active(bool value);

			virtual inline float scaleOnActive() { return _scaleOnActive; }
			virtual inline void scaleOnActive(float value) { _scaleOnActive = value; }

			virtual inline bool colorPickerEnabled() { return _colorPickerEnabled; }
			virtual inline void colorPickerEnabled(bool value) { _colorPickerEnabled = value; }
			
			virtual ofParameter<ofFloatColor>& pickedColor() { return _pickedColor; }

		protected:
			virtual void _setup();
			//virtual void _afterSetup();
			//virtual void _update();
			virtual void _draw();
			virtual void _afterDraw();

			virtual void _updateGraphics(float w, float h);

			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

		private:

	};

}
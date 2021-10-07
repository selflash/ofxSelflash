#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"
#include "flBasicUIWindow.h"

namespace fl2d {

	class flBasicImageViewer : public flBasicUIWindow {
		public:

		protected:
			flBitmap* _bitmap = NULL;
			float _defaultImageWidth;
			float _defaultImageHeight;

			int _mode = 0;

			bool _isActive = false;
			float _scaleOnActive = 2.0;

		private:

		public:
			flBasicImageViewer(flBitmap* bitmap, int w, int h);
			virtual ~flBasicImageViewer();

			virtual void normalize();
			virtual void maximize();

			bool active();
			void active(bool value);

			virtual inline float scaleOnActive() { return _scaleOnActive; }
			virtual inline void scaleOnActive(float value) { _scaleOnActive = value; }

		protected:
			virtual void _setup();
			virtual void _update();
			virtual void _draw();
			virtual void _resize(float w, float h);

			virtual void _updateGraphics(float w, float h);

			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

		private:

	};

}
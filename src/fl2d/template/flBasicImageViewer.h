#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"
#include "flBasicDraggableObject.h"

namespace fl2d {

	class flBasicImageViewer : public flBasicDraggableObject, public flAbstractController  {
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

			bool _isLocked = false;

			ofEventListeners _listeners;



			int _mode = 0;

			bool _isActive = false;
			float _scaleOnActive = 2.0;

			//flBasicDraggableObject* _sizingHandle = NULL;

			flBitmap* _bitmap = NULL;
			float _defaultImageWidth;
			float _defaultImageHeight;

		private:

		public:
			flBasicImageViewer(flBitmap* bitmap, int w, int h);
			virtual ~flBasicImageViewer();

			virtual void setup();

			virtual void minimize();
			virtual void normalize();
			virtual void maximize();
			virtual void resize(float w, float h);

			virtual inline string title() { return _title; }
			virtual inline void title(string value) { _title = value; }

			virtual inline float backWidth() { return _backWidth; }
			virtual inline float backHeight() { return _backHeight; }
			//virtual inline float minBackWidth() { return _minBackWidth; }
			virtual inline float minBackHeight() { return _minBackHeight; }
			virtual inline float normalBackWidth() { return _normalBackWidth; }
			virtual inline float normalBackHeight() { return _normalBackHeight; }

			virtual bool lock();
			virtual void lock(bool value);

			bool active();
			void active(bool value);

			virtual inline float scaleOnActive() { return _scaleOnActive; }
			virtual inline void scaleOnActive(float value) { _scaleOnActive = value; }

		protected:
			virtual void _setup();
			virtual void _update();
			virtual void _draw();
			virtual void _afterDraw();
			virtual void _resize(float w, float h);

			virtual void _hoge(
				const float srcWidth, const float srcHeight, 
				const float windowWidth, const float windowHeight, 
				float& dstWidth, float& dstHeight
			);

			virtual void _relocateTitleBarButtons();
			virtual void _updateGraphics(float w, float h);

			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

		private:

	};

}
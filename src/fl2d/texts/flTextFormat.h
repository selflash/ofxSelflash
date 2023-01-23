/**

 ActionScript3.0 Reference
 flash.text.TextFormat
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/text/TextFormat.html

 */

#pragma once

#include "ofMain.h"

namespace fl2d {

	class flTextFormat {

		public:

		protected:

		private:
			string _align;
			bool _bold = false;
			ofColor _color;
			string _font;
			int _size = 10.0;

		public:
			flTextFormat(
				string font = "", 
				int size = 10.0,
				ofColor color = ofColor::white, 
				bool bold = false, 
				bool italic = false, 
				bool underline = false,
				string align = ""
			);
			virtual ~flTextFormat();

			virtual string align() { return _align; }
			virtual void align(string value) { _align = value; }

			virtual bool bold() { return _bold; }
			virtual void bold(bool value) { _bold = value; }

			virtual ofColor color() { return _color; }
			virtual void color(ofColor value) { _color = value; }

			virtual string font() { return _font; }
			virtual void font(string value) { _font = value; }

			virtual int size() { return _size; }
			virtual void size(int value) { _size = value; }

		protected:

		private:
	};
}

#include "flTextFormat.h"

namespace fl2d {

	//==============================================================
	// Constructor / Destructor
	//==============================================================

	//--------------------------------------------------------------
	flTextFormat::flTextFormat(
		string font,
		int size,
		ofColor color,
		bool bold,
		bool italic,
		bool underline,
		string align
	) {
		_font = font;
		_size = size;
		_color = color;
		_bold = bold;
	}

	//--------------------------------------------------------------
	flTextFormat::~flTextFormat() {

	}

}
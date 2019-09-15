#include "flFont.h"

namespace fl2d {
    
    ofTrueTypeFont* flFont::_font = new ofTrueTypeFont();
    float flFont::_maxStringWidth = 0.0;
    float flFont::_maxStringHeight = 0.0;
    
    //--------------------------------------------------------------
    //
    void flFont::setup() {
        float fontSize = 10;
		if (!_font->load(flDefinition::_FONT_PATH, fontSize, true, true)) {
			ofLogError() << "Font has not loaded.";
		};
        
        std::string text = "";
        text += "1234567890-^¥!#$%&'()0=~|'";
        text += "qwertyuiop@[QWERTYUIOP`{";
        text += "asdfghjkl;:]ASDFGHJKL+*}";
        text += "zxcvbnm,./_ZXCVBNM<>?_";
        _maxStringWidth = _font->stringWidth(text);
        _maxStringHeight = _font->stringHeight(text);
        
        //        _font->setLetterSpacing(2);
        _font->setLineHeight(getMaxStringHeight());
    }
    
    //--------------------------------------------------------------
    //
    void flFont::clear() {
        _maxStringWidth = 0.0;
        _maxStringHeight = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    void flFont::registerFont(ofTrueTypeFont* font) {
        _font = font;
    }
    
    //--------------------------------------------------------------
    //
    ofRectangle flFont::getStringBoundingBox(const std::string& text, float x, float y) {
        return _font->getStringBoundingBox(text, x, y);
    }
    
    //--------------------------------------------------------------
    //
    void flFont::drawString(const std::string& text, float x, float y) {
        if(text == "") return;
        
        _font->drawString(text, x, y);
    }
    //--------------------------------------------------------------
    //
    void flFont::drawStringHighlight(
                                   const std::string& text,
                                   float x, float y,
                                   const ofColor& background,
                                   const ofColor& foreground
                                   ) {
        if(text != "") {
            ofPushStyle();
            ofSetColor(background);
            ofRectangle boundingBox = _font->getStringBoundingBox(text, x, y);
            ofDrawRectangle(
                            boundingBox.x - 2,
                            boundingBox.y - 2,
                            boundingBox.width + 4,
                            boundingBox.height + 4
                            );
            ofPopStyle();
            
            ofPushStyle();
            ofSetColor(foreground);
            _font->drawString(text, x, y);
            ofPopStyle();
        }
    }
    
    //--------------------------------------------------------------
    //
    float flFont::getLineHeight() { return _font->getLineHeight(); }
    
    //--------------------------------------------------------------
    //
    float flFont::getMaxStringWidth() { return _maxStringWidth; }
    
    //--------------------------------------------------------------
    //
    float flFont::getMaxStringHeight() { return _maxStringHeight; }
    
}

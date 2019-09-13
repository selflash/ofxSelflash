#include "Font.h"

namespace fl2d {
    
    ofTrueTypeFont* Font::_font = new ofTrueTypeFont();
    float Font::_maxStringWidth = 0.0;
    float Font::_maxStringHeight = 0.0;
    
    //--------------------------------------------------------------
    //
    void Font::setup() {
        float fontSize = 10;
        _font->load(FlashConfig::_FONT_PATH, fontSize, true, true);
        
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
    void Font::clear() {
        _maxStringWidth = 0.0;
        _maxStringHeight = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    void Font::registerFont(ofTrueTypeFont* font) {
        _font = font;
    }
    
    //--------------------------------------------------------------
    //
    ofRectangle Font::getStringBoundingBox(const std::string& text, float x, float y) {
        return _font->getStringBoundingBox(text, x, y);
    }

    //--------------------------------------------------------------
    //
    void Font::drawString(const std::string& text, float x, float y) {
        if(text == "") return;
        
        _font->drawString(text, x, y);
    }
    //--------------------------------------------------------------
    //
    void Font::drawStringHighlight(
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
    float Font::getLineHeight() { return _font->getLineHeight(); }
    
    //--------------------------------------------------------------
    //
    float Font::getMaxStringWidth() { return _maxStringWidth; }
    
    //--------------------------------------------------------------
    //
    float Font::getMaxStringHeight() { return _maxStringHeight; }

}

#include "Font.h"

namespace fl2d {
    
    ofTrueTypeFont* Font::_font = new ofTrueTypeFont();
    float Font::_maxStringWidth = 0.0;
    float Font::_maxStringHeight = 0.0;
    
    //--------------------------------------------------------------
    //
    void Font::setup() {
        _font->loadFont(FlashConfig::_FONT_PATH, 10, true, true);
        
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
        _font->drawString(text, x, y);
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
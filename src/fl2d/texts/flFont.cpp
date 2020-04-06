#include "flFont.h"

namespace fl2d {
    bool flFont::_loaded = false;
    map<int, ofTrueTypeFont> flFont::_fonts;
    const int flFont::_normalFontSize = 10;
    map<int, float> flFont::_maxStringWidth;
    map<int, float> flFont::_maxStringHeight;
    
    //--------------------------------------------------------------
    bool flFont::loaded() {
        return _loaded;
    }

    //--------------------------------------------------------------
    void flFont::setup() {
        ofTrueTypeFont font;
        _loadFont(font, flDefinition::_FONT_PATH, _normalFontSize);
        _fonts[_normalFontSize] = font;
        
        _loaded = true;
    }
    
    //--------------------------------------------------------------
    void flFont::clear() {
        _fonts.clear();
        _maxStringWidth.clear();
        _maxStringHeight.clear();
    }
    
    //--------------------------------------------------------------
    void flFont::loadFont(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            ofTrueTypeFont font;
            _loadFont(font, flDefinition::_FONT_PATH, fontSize);
            _fonts[fontSize] = font;
        }
    }
    
    //--------------------------------------------------------------
    ofTrueTypeFont flFont::_loadFont(ofTrueTypeFont& font, string path, int fontSize) {
        // Fonts
        //        ofTrueTypeFont::setGlobalDpi(72);
        
        ofTrueTypeFontSettings settings(path, fontSize);//[CX^X
        settings.addRanges(ofAlphabet::Emoji);//G��
        settings.addRanges(ofAlphabet::Japanese);//{
        settings.addRange(ofUnicode::Space);//Xy[X
        settings.addRange(ofUnicode::IdeographicSpace);//SpXy[X
        settings.addRange(ofUnicode::Latin);//At@xbg
        settings.addRange(ofUnicode::Latin1Supplement);//LAANTt�L��
        settings.addRange(ofUnicode::NumberForms);//H
        settings.addRange(ofUnicode::Arrows);//
        settings.addRange(ofUnicode::MathOperators);//L
        settings.addRange(ofUnicode::Hiragana);//
        settings.addRange(ofUnicode::Katakana);//J^Ji
        settings.addRange(ofUnicode::MiscSymbolsAndPictographs);//G��
        settings.addRange(ofUnicode::Emoticons);//G[eBR
        
        string text = "";
        text += "1234567890-^!#$%&'()0=~|'";
        text += "qwertyuiop@[QWERTYUIOP`{";
        text += "asdfghjkl;:]ASDFGHJKL+*}";
        text += "zxcvbnm,./_ZXCVBNM<>?_";
        text += u8"����������";
        text += u8"����������";
        text += u8"����������";
        text += u8"�����Ă�";
        text += u8"�Ȃɂʂ˂�";
        text += u8"�͂Ђӂւ�";
        text += u8"�܂݂ނ߂�";
        text += u8"����";
        text += u8"������";
        text += u8"�����";
        
        // [h
        //ofTrueTypeFont font;
        if(font.load(settings)){
            ofLog() << path << " has been loaded.";
            
            font.setLetterSpacing(1.2);//�݁e ftHg1.0 �݁eJ1.0����lw��
            float maxStringWidth = font.stringWidth(text);
            float maxStringHeight = font.stringHeight(text);
            //            _font.setLetterSpacing(2);// �݁ew��
            font.setLineHeight(maxStringHeight);// s�ew��
            
            _maxStringWidth[fontSize] = maxStringWidth;
            _maxStringHeight[fontSize] = maxStringHeight;
        } else {
            ofLog(OF_LOG_ERROR) << path << " has not been loaded.";
        }
        
        return font;
    }
    
    //--------------------------------------------------------------
    //    void flFont::registFont(ofTrueTypeFont font) {
    //        _normalFont = _normalFont;
    //    }
    
    //--------------------------------------------------------------
    void flFont::drawString(const std::string& text) {
        drawString(text, 0, 0);
    }
    void flFont::drawString(const std::string& text, float x, float y) {
        if(text == "") return;
        const ofTrueTypeFont& font = _fonts[_normalFontSize];
        font.drawString(text, x, y);
    }
    void flFont::drawString(const std::string& text, int fontSize) {
        drawString(text, fontSize, 0, 0);
    }
    void flFont::drawString(const std::string& text, int fontSize, float x, float y) {
        if(text == "") return;
        if (_fonts.find(fontSize) == _fonts.end()) {
            ofTrueTypeFont font;
            _loadFont(font, flDefinition::_FONT_PATH, fontSize);
            _fonts[fontSize] = font;
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        font.drawString(text, x, y);
    }
    
    //--------------------------------------------------------------
    void flFont::drawStringHighlight(const string& text, const ofColor& background, const ofColor& foreground) {
        drawStringHighlight(text, 0, 0, background, foreground);
    }
    void flFont::drawStringHighlight(
                                     const string& text,
                                     float x, float y,
                                     const ofColor& background,
                                     const ofColor& foreground
                                     ) {
        if(text != "") {
            const ofTrueTypeFont& font = _fonts[_normalFontSize];
            
            ofPushStyle();
            ofSetColor(background);
            const ofRectangle& boundingBox = font.getStringBoundingBox(text, x, y);
            ofDrawRectangle(
                            boundingBox.x - 2,
                            boundingBox.y - 2,
                            boundingBox.width + 4,
                            boundingBox.height + 4
                            );
            ofPopStyle();
            
            ofPushStyle();
            ofSetColor(foreground);
            
            font.drawString(text, x, y);
            
            ofPopStyle();
        }
    }
    void flFont::drawStringHighlight(const string& text, int fontSize, const ofColor& background, const ofColor& foreground) {
        drawStringHighlight(text, fontSize, 0, 0, background, foreground);
    }
    void flFont::drawStringHighlight(const string& text, int fontSize, float x, float y, const ofColor& background, const ofColor& foreground) {
        if(text != "") {
            if (_fonts.find(fontSize) == _fonts.end()) {
                ofTrueTypeFont font;
                _loadFont(font, flDefinition::_FONT_PATH, fontSize);
                _fonts[fontSize] = font;
            }
            
            const ofTrueTypeFont& font = _fonts[fontSize];
            
            ofPushStyle();
            ofSetColor(background);
            const ofRectangle& boundingBox = font.getStringBoundingBox(text, x, y);
            ofDrawRectangle(
                            boundingBox.x - 2,
                            boundingBox.y - 2,
                            boundingBox.width + 4,
                            boundingBox.height + 4
                            );
            ofPopStyle();
            
            ofPushStyle();
            ofSetColor(foreground);
            
            font.drawString(text, x, y);
            
            ofPopStyle();
        }
    }
    
    //--------------------------------------------------------------
    ofRectangle flFont::getStringBoundingBox(const string& text) {
        return getStringBoundingBox(text, 0.0, 0.0);
    }
    ofRectangle flFont::getStringBoundingBox(const string& text, float x, float y) {
        const ofTrueTypeFont& font = _fonts[_normalFontSize];
        return font.getStringBoundingBox(text, x, y);
    }
    ofRectangle flFont::getStringBoundingBox(const string& text, int fontSize) {
        return getStringBoundingBox(text, fontSize, 0.0, 0.0);
    }
    ofRectangle flFont::getStringBoundingBox(const string& text, int fontSize, float x, float y) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            ofTrueTypeFont font;
            _loadFont(font, flDefinition::_FONT_PATH, fontSize);
            _fonts[fontSize] = font;
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        return font.getStringBoundingBox(text, x, y);
    }
    
    //--------------------------------------------------------------
    float flFont::getLineHeight(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        return font.getLineHeight();
    }
    
    float flFont::getStringWidth(const string& text, int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        return font.stringWidth(text);
        
    }
    float flFont::getStringHeight(const string& text, int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        return font.stringHeight(text);
        
    }
    
    //--------------------------------------------------------------
    float flFont::getMaxStringWidth(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        return _maxStringWidth[fontSize];
    }
    
    //--------------------------------------------------------------
    float flFont::getMaxStringHeight(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        return _maxStringHeight[fontSize];
    }
}

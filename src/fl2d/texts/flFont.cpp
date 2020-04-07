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
        
        ofTrueTypeFontSettings settings(path, fontSize);//ê›íËàÍéÆÇî[ÇﬂÇÈÉCÉìÉXÉ^ÉìÉX
        settings.addRanges(ofAlphabet::Emoji);//äGï∂éö
        settings.addRanges(ofAlphabet::Japanese);//ì˙ñ{åÍ
        settings.addRange(ofUnicode::Space);//ÉXÉyÅ[ÉX
        settings.addRange(ofUnicode::IdeographicSpace);//ëSäpÉXÉyÅ[ÉX
        settings.addRange(ofUnicode::Latin);//ÉAÉãÉtÉ@ÉxÉbÉgìô
        settings.addRange(ofUnicode::Latin1Supplement);//ãLçÜÅAÉAÉNÉTÉìïtÇ´ï∂éöÇ»Ç«
        settings.addRange(ofUnicode::NumberForms);//êîéöÅH
        settings.addRange(ofUnicode::Arrows);//ñÓàÛ
        settings.addRange(ofUnicode::MathOperators);//êîéÆãLçÜ
        settings.addRange(ofUnicode::Hiragana);//Ç–ÇÁÇ™Ç»
        settings.addRange(ofUnicode::Katakana);//ÉJÉ^ÉJÉi
        settings.addRange(ofUnicode::MiscSymbolsAndPictographs);//äGï∂éöÇ»Ç«
        settings.addRange(ofUnicode::Emoticons);//ÉGÉÇÅ[ÉeÉBÉRÉì
        
        string text = "";
        text += "1234567890-^Åè!#$%&'()0=~|'";
        text += "qwertyuiop@[QWERTYUIOP`{";
        text += "asdfghjkl;:]ASDFGHJKL+*}";
        text += "zxcvbnm,./_ZXCVBNM<>?_";
        text += u8"あいうえお";
        text += u8"かきくけこ";
        text += u8"さしすせそ";
        text += u8"たちつてと";
        text += u8"なにぬねの";
        text += u8"はひふへほ";
        text += u8"まみむめも";
        text += u8"やゆよ";
        text += u8"らりるれろ";
        text += u8"わをん";
        
        // ê›íËÇÉçÅ[Éh
        //ofTrueTypeFont font;
        if(font.load(settings)){
            ofLog() << path << " has been loaded.";
            
            font.setLetterSpacing(1.2);//ï∂éöä‘ ÉfÉtÉHÉãÉgÇÕ1.0 ï∂éöä‘ÇÇÊÇËäJÇØÇÈèÍçáÇÕ1.0Çí¥Ç¶ÇÈílÇéwíËÇ∑ÇÈ
            float maxStringWidth = font.stringWidth(text);
            float maxStringHeight = font.stringHeight(text);
            //            _font.setLetterSpacing(2);// ï∂éöä‘ÇéwíËÇ∑ÇÈ
            font.setLineHeight(maxStringHeight);// çsä‘ÇéwíËÇ∑ÇÈ
            
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

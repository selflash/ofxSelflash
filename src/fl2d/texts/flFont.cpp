#include "flFont.h"

namespace fl2d {
    map<int, ofTrueTypeFont> flFont::_fonts;
    const int flFont::_normalFontSize = 10;
    map<int, float> flFont::_maxStringWidth;
    map<int, float> flFont::_maxStringHeight;
    
    //--------------------------------------------------------------
    //
    void flFont::setup() {
        _fonts[_normalFontSize] = _loadFont(flDefinition::_FONT_PATH, _normalFontSize);
    }
    
    //--------------------------------------------------------------
    //
    void flFont::clear() {
        _fonts.clear();
        _maxStringWidth.clear();
        _maxStringHeight.clear();
    }
    
    //--------------------------------------------------------------
    //
    void flFont::loadFont(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            _fonts[fontSize] = _loadFont(flDefinition::_FONT_PATH, fontSize);
        }
    }
    
    //--------------------------------------------------------------
    //
    ofTrueTypeFont flFont::_loadFont(string path, int fontSize) {
        // Fonts
        //        ofTrueTypeFont::setGlobalDpi(72);
        
        ofTrueTypeFontSettings settings(path, fontSize);//設定一式を納めるインスタンス
        settings.addRanges(ofAlphabet::Emoji);//絵文字
        settings.addRanges(ofAlphabet::Japanese);//日本語
        settings.addRange(ofUnicode::Space);//スペース
        settings.addRange(ofUnicode::IdeographicSpace);//全角スペース
        settings.addRange(ofUnicode::Latin);//アルファベット等
        settings.addRange(ofUnicode::Latin1Supplement);//記号、アクサン付き文字など
        settings.addRange(ofUnicode::NumberForms);//数字？
        settings.addRange(ofUnicode::Arrows);//矢印
        settings.addRange(ofUnicode::MathOperators);//数式記号
        settings.addRange(ofUnicode::Hiragana);//ひらがな
        settings.addRange(ofUnicode::Katakana);//カタカナ
        settings.addRange(ofUnicode::MiscSymbolsAndPictographs);//絵文字など
        settings.addRange(ofUnicode::Emoticons);//エモーティコン
        
        string text = "";
        text += "1234567890-^¥!#$%&'()0=~|'";
        text += "qwertyuiop@[QWERTYUIOP`{";
        text += "asdfghjkl;:]ASDFGHJKL+*}";
        text += "zxcvbnm,./_ZXCVBNM<>?_";
        text += "あいうえお";
        text += "かきくけこ";
        text += "さしすせそ";
        text += "たちつてと";
        text += "なにぬねの";
        text += "はひふへほ";
        text += "まみむめも";
        text += "らりるれろ";
        text += "やゆよ";
        text += "わをん";
        
        // 設定をロード
        ofTrueTypeFont font;
        if(font.load(settings)){
            //ofLog() << path << " has loaded.";

            font.setLetterSpacing(1.2);//文字間 デフォルトは1.0 文字間をより開ける場合は1.0を超える値を指定する
            float maxStringWidth = font.stringWidth(text);
            float maxStringHeight = font.stringHeight(text);
//            _font.setLetterSpacing(2);// 文字間を指定する
            font.setLineHeight(maxStringHeight);// 行間を指定する
            
            _maxStringWidth[fontSize] = maxStringWidth;
            _maxStringHeight[fontSize] = maxStringHeight;
        } else {
            ofLog(OF_LOG_ERROR) << path << " has not loaded.";
        }
        
        return font;
    }

    //--------------------------------------------------------------
    //
//    void flFont::registFont(ofTrueTypeFont font) {
//        _normalFont = _normalFont;
//    }

    //--------------------------------------------------------------
    //
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
            _fonts[fontSize] = _loadFont(flDefinition::_FONT_PATH, fontSize);
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        font.drawString(text, x, y);
    }

    //--------------------------------------------------------------
    //
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
                _fonts[fontSize] = _loadFont(flDefinition::_FONT_PATH, fontSize);
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
    //
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
            _fonts[fontSize] = _loadFont(flDefinition::_FONT_PATH, fontSize);
        }
        const ofTrueTypeFont& font = _fonts[fontSize];
        return font.getStringBoundingBox(text, x, y);
    }
    
    //--------------------------------------------------------------
    //
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
    //
    float flFont::getMaxStringWidth(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        return _maxStringWidth[fontSize];
    }
    
    //--------------------------------------------------------------
    //
    float flFont::getMaxStringHeight(int fontSize) {
        if (_fonts.find(fontSize) == _fonts.end()) {
            return 0.0;
        }
        return _maxStringHeight[fontSize];
    }
}

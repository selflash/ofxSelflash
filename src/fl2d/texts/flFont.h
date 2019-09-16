#pragma once

#include "ofMain.h"
#include "flDefinition.h"

namespace fl2d {
    
    class flFont {
    public:
        
    protected:
        
    private:
        static map<int, ofTrueTypeFont> _fonts;
        const static int _normalFontSize;
        static map<int, float> _maxStringWidth;
        static map<int, float> _maxStringHeight;
        
    public:
        static void setup();
        static void clear();
        static void loadFont(int fontSize);
//        static void registFont(ofTrueTypeFont font);

        static void drawString(const string& text);
        static void drawString(const string& text, float x, float y);
        static void drawString(const string& text, int fontSize);
        static void drawString(const string& text, int fontSize, float x, float y);

        static void drawStringHighlight(
                                        const string& text,
                                        const ofColor& background = ofColor::black,
                                        const ofColor& foreground = ofColor::white
                                        );
        static void drawStringHighlight(
                                        const string& text,
                                        float x, float y,
                                        const ofColor& background = ofColor::black,
                                        const ofColor& foreground = ofColor::white
                                        );
        static void drawStringHighlight(
                                        const string& text,
                                        int fontSize,
                                        const ofColor& background = ofColor::black,
                                        const ofColor& foreground = ofColor::white
                                        );
        static void drawStringHighlight(
                                        const string& text,
                                        int fontSize,
                                        float x, float y,
                                        const ofColor& background = ofColor::black,
                                        const ofColor& foreground = ofColor::white
                                        );

        static ofRectangle getStringBoundingBox(const string& text);
        static ofRectangle getStringBoundingBox(const string& text, float x, float y);
        static ofRectangle getStringBoundingBox(const string& text, int fontSize);
        static ofRectangle getStringBoundingBox(const string& text, int fontSize, float x, float y);

        static float getLineHeight(int fontSize = _normalFontSize);
        static float getStringWidth(const string& text, int fontSize = _normalFontSize);
        static float getStringHeight(const string& text, int fontSize = _normalFontSize);
        static float getMaxStringWidth(int fontSize = _normalFontSize);
        static float getMaxStringHeight(int fontSize = _normalFontSize);
        
    protected:
        
    private:
        static ofTrueTypeFont _loadFont(string path, int fontSize);
    };
    
}

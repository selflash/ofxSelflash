#pragma once

#include "ofMain.h"
#include "flDefinition.h"

namespace fl2d {
    
    class flFont {
    public:
        
    protected:
        
    private:
        static ofTrueTypeFont* _font;
        
        static float _maxStringWidth;
        static float _maxStringHeight;
        
    public:
        static void setup();
        static void clear();
        static void registerFont(ofTrueTypeFont* font);
        
        static ofRectangle getStringBoundingBox(const string& text, float x = 0.0, float y = 0.0);
        static void drawString(const string& text, float x = 0.0, float y = 0.0);
        static void drawStringHighlight(
                                        const string& text,
                                        float x = 0.0, float y = 0.0,
                                        const ofColor& background = ofColor::black,
                                        const ofColor& foreground = ofColor::white
                                        );
        static float getLineHeight();
        static float getMaxStringWidth();
        static float getMaxStringHeight();
        
    protected:
        
    private:
        
    };
    
}
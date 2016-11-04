#pragma once

#include "ofMain.h"
#include "../FlashConfig.h"

namespace fl2d {
    
    class Font {
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
            static float getLineHeight();
            static float getMaxStringWidth();
            static float getMaxStringHeight();
        
        protected:
            
        private:
        
    };
    
}
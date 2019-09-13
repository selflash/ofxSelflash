#pragma once

// version 1.0.0

#include "fl2d/Flash2D.h"
//using namespace fl2d;

#include "utils/MathUtil.h"

class ofxSelflash {
    public:
    
    protected:
    
    private:
    
    public:
        static inline bool autoUpdate() { return FlashConfig::AUTO_UPDATE; }
        static inline void autoUpdate(bool value) { FlashConfig::AUTO_UPDATE = value; }

        static inline ofEventOrder updatePriority() { return FlashConfig::UPDATE_PRIORITY; }
        static inline void updatePriority(ofEventOrder value) { FlashConfig::UPDATE_PRIORITY = value; }

        static inline bool autoDraw() { return FlashConfig::AUTO_DRAW; }
        static inline void autoDraw(bool value) { FlashConfig::AUTO_DRAW = value; }
    
        static inline ofEventOrder drawPriority() { return FlashConfig::DRAW_PRIORITY; }
        static inline void drawPriority(ofEventOrder value) { FlashConfig::DRAW_PRIORITY = value; }

        static inline void setup(const bool& use3D = false) {
//            cout << "[ofxSelflash]setup()" << endl;
            
            Flash2D::setup();
            flStage::instance();
        }
    
        static inline void clear() {
//            cout << "[ofxSelflash]clear()" << endl;
            Flash2D::clear();
        }
    
        static inline void update() { flStage::instance()->update(); }
        static inline void draw() { flStage::instance()->draw(); }

        static inline flStage* stage() { return flStage::instance(); }
    
    protected:
        
    private:
    
};

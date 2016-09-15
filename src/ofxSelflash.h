#pragma once

//Comment in, if you want to use api of 3d
//#define FLASH_3D
//Comment in, if you want to use AssimpModelLoader

// version 1.0.0

#include "./fl2d/Flash2D.h"
//using namespace fl2d;

#if defined(FLASH_3D)
#include "Flash3D.h"
//using namespace fl3d;
#endif

#include "./utils/MathUtil.h"
#include "./utils/NativeWindow.h"

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
            ofLog(OF_LOG_VERBOSE) << "[ofxSelflash]setup()";
            
            Flash2D::setup();
            
#if defined(FLASH_3D)
            if(use3D) Flash3D::setup();
#endif
            
            flStage::instance();
        }
    
        static inline void clear() {
            ofLog(OF_LOG_VERBOSE) << "[ofxSelflash]clear()";

            Flash2D::clear();
            
#if defined(FLASH_3D)
            Flash3D::clear();
#endif
        }
    
        static inline void update() { flStage::instance()->update(); }
        static inline void draw() { flStage::instance()->draw(); }

        static inline flStage* stage() { return flStage::instance(); }
    
    protected:
        
    private:
    
};

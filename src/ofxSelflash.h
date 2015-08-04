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
        static inline void setup(const bool& use3D = false) {
            ofLog(OF_LOG_VERBOSE) << "[ofxSelflash]setup()";
            
            Flash2D::setup();
            
#if defined(FLASH_3D)
            if(use3D) Flash3D::setup();
#endif
        }
    
        static inline void clear() {
            ofLog(OF_LOG_VERBOSE) << "[ofxSelflash]clear()";

            Flash2D::clear();
            
#if defined(FLASH_3D)
            Flash3D::clear();
#endif
        }

    
        static inline flStage* stage() { return flStage::instance(); }
    
    protected:
        
    private:
    
};

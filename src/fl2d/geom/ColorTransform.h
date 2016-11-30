#pragma once

/**
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlashLite/blob/master/src/geom/ofxFlashColorTransform.h
 
 ActionScript3.0 Reference
 flash.geom.ColorTransform
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/ColorTransform.html
 
 */

#include "../core/Object.h"

namespace fl2d {
    
    class ColorTransform : public Object {
        public:
            // A decimal value that is multiplied with the alpha transparency channel value.
            float alphaMultiplier;
            // A number from -255 to 255 that is added to the alpha transparency channel value after it has been multiplied by the alphaMultiplier value.
            float alphaOffset;
            // A decimal value that is multiplied with the blue channel value.
            float blueMultiplier;
            // A number from -255 to 255 that is added to the blue channel value after it has been multiplied by the blueMultiplier value.
            float blueOffset;
            // The RGB color value for a ColorTransform object.
            unsigned int color;
            // A decimal value that is multiplied with the green channel value.
            float greenMultiplier;
            // A number from -255 to 255 that is added to the green channel value after it has been multiplied by the greenMultiplier value.
            float greenOffset;
            // A decimal value that is multiplied with the red channel value.
            float redMultiplier;
            // A number from -255 to 255 that is added to the red channel value after it has been multiplied by the redMultiplier value.
            float redOffset;
        
        protected:
        
        private:
        
        public:
            ColorTransform(
                           float redMultiplier   = 1,
                           float greenMultiplier = 1,
                           float blueMultiplier  = 1,
                           float alphaMultiplier = 1,
                           float redOffset       = 0,
                           float greenOffset     = 0,
                           float blueOffset      = 0,
                           float alphaOffset     = 0
            );
            
            ~ColorTransform();
            
            void set(const ColorTransform& second);
            void concat(const ColorTransform& second);
            bool isEqual(const ColorTransform& second);
            
            string toString();
            
    };
    
}

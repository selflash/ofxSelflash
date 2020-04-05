/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlashLite/blob/master/src/geom/ofxFlashTransform.h
 
 ActionScript3.0 Reference
 flash.geom.Transform
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/Transform.html
 
 */

#pragma once

#include "ofMain.h"
#include "flColorTransform.h"
#include "flMatrix.h"
#include "flRectangle.h"

namespace fl2d {
    class flDisplayObject;
    class flSprite;
    
    class flTransform : public flObject {
        public:
        
            /**
             *  friends! http://www.cplusplus.com/doc/tutorial/inheritance/
             **/
            friend flDisplayObject;
            friend flSprite;
        
        protected:
        
        private:
//            bool bDirtyColorTransform;
//            bool bDirtyMatrix;
//            bool bDirtyMatrix3D;

            flColorTransform  _colorTransform;
            flColorTransform  _concatenatedColorTransform;
            flMatrix          __concatenatedMatrix;
            flMatrix          __concatenatedMatrixInv;
            flMatrix          __matrix;
//            flMatrix          _matrix3D;
            flRectangle      __pixelBounds;
            ofPoint         _transformedPoints[4];

        public:
            flTransform();
            virtual ~flTransform();
        
            /**
             *  Returns a Matrix3D object, which can transform the space of a specified display object in relation to the current display object's space.
             *  Not working due to cycling dependencies I need to work out.
             **/
            //    ofxFlashMatrix getRelativeMatrix3D( ofxFlashDisplayObject relativeTo ) { return ofxFlashMatrix(); }
        
            // A ColorTransform object containing values that universally adjust the colors in the display object.
            virtual inline flColorTransform& colorTransform() { return _colorTransform; }
        
            // [read-only] A ColorTransform object representing the combined color transformations applied to the display object and all of its parent objects, back to the root level.
            virtual inline flColorTransform& concatenatedColorTransform() { return _concatenatedColorTransform; }
        
            // [read-only] A flMatrix object representing the combined transformation matrixes of the display object and all of its parent objects, back to the root level.
            virtual inline const flMatrix& concatenatedMatrix() { return __concatenatedMatrix; }
        
            // A flMatrix object containing values that alter the scaling, rotation, and translation of the display object.
            virtual inline flMatrix& matrix() { return __matrix; }
            virtual inline void matrix(const flMatrix& mat) { __matrix = mat; }
        
            // Provides access to the Matrix3D object of a three-dimensional display object.
//            flMatrix matrix3D;
        
            // [read-only] A Rectangle object that defines the bounding rectangle of the display object on the stage.
            virtual inline const flRectangle& pixelBounds() { return __pixelBounds; }

        protected:
//            void update();
        
        private:
            void __updatePixelBounds(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);

    };
    
}

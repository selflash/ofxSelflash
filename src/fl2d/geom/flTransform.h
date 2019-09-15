/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlashLite/blob/master/src/geom/ofxFlashTransform.h
 
 ActionScript3.0 Reference
 flash.geom.Transform
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/Transform.html
 
 */

#include "ofMain.h"
#include "flColorTransform.h"
#include "flMatrix.h"
#include "flRectangle.h"

namespace fl2d {
    class flStage;
    class flDisplayObject;
    
    class flTransform : public flObject {
    public:
        
        /**
         *  friends! http://www.cplusplus.com/doc/tutorial/inheritance/
         **/
        friend flStage;
        friend flDisplayObject;
        
        /**
         *  Returns a Matrix3D object, which can transform the space of a specified display object in relation to the current display object's space.
         *  Not working due to cycling dependencies I need to work out.
         **/
        //    ofxFlashMatrix getRelativeMatrix3D( ofxFlashDisplayObject relativeTo ) { return ofxFlashMatrix(); }
        
        // A ColorTransform object containing values that universally adjust the colors in the display object.
        flColorTransform colorTransform;
        // [read-only] A ColorTransform object representing the combined color transformations applied to the display object and all of its parent objects, back to the root level.
        flColorTransform concatenatedColorTransform;
        // [read-only] A flMatrix object representing the combined transformation matrixes of the display object and all of its parent objects, back to the root level.
        flMatrix concatenatedMatrix;
        // A flMatrix object containing values that alter the scaling, rotation, and translation of the display object.
        flMatrix matrix;
        // Provides access to the Matrix3D object of a three-dimensional display object.
        flMatrix matrix3D;
        // [read-only] A Rectangle object that defines the bounding rectangle of the display object on the stage.
        flRectangle* pixelBounds;
        
    protected:
        
    private:    
        bool bDirtyColorTransform;
        bool bDirtyMatrix;
        bool bDirtyMatrix3D;
        
        flColorTransform  _colorTransform;
        flColorTransform  _concatenatedColorTransform;
        flMatrix          _concatenatedMatrix;
        flMatrix          _concatenatedMatrixInv;
        flMatrix          _matrix;
        flMatrix          _matrix3D;
        flRectangle*      _pixelBounds;
        flRectangle*      _rect;
        ofPoint         _rectTransformed[4];
        
    public:
		flTransform();
        virtual ~flTransform();
        
    protected:
        void update();
        
    private:
    };
    
}

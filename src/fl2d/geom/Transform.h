/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlashLite/blob/master/src/geom/ofxFlashTransform.h
 
 ActionScript3.0 Reference
 flash.geom.Transform
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/Transform.html
 
 */

#include "ofMain.h"
#include "ColorTransform.h"
#include "Matrix.h"
#include "Rectangle.h"

namespace fl2d {
    class Stage;
    class DisplayObject;
    
    class Transform : public Object {
    public:
        
        /**
         *  friends! http://www.cplusplus.com/doc/tutorial/inheritance/
         **/
        friend Stage;
        friend DisplayObject;
        
        /**
         *  Returns a Matrix3D object, which can transform the space of a specified display object in relation to the current display object's space.
         *  Not working due to cycling dependencies I need to work out.
         **/
        //    ofxFlashMatrix getRelativeMatrix3D( ofxFlashDisplayObject relativeTo ) { return ofxFlashMatrix(); }
        
        // A ColorTransform object containing values that universally adjust the colors in the display object.
        ColorTransform colorTransform;
        // [read-only] A ColorTransform object representing the combined color transformations applied to the display object and all of its parent objects, back to the root level.
        ColorTransform concatenatedColorTransform;
        // [read-only] A Matrix object representing the combined transformation matrixes of the display object and all of its parent objects, back to the root level.
        Matrix concatenatedMatrix;
        // A Matrix object containing values that alter the scaling, rotation, and translation of the display object.
        Matrix matrix;
        // Provides access to the Matrix3D object of a three-dimensional display object.
        Matrix matrix3D;
        // [read-only] A Rectangle object that defines the bounding rectangle of the display object on the stage.
        Rectangle* pixelBounds;
        
    protected:
        
    private:    
        bool bDirtyColorTransform;
        bool bDirtyMatrix;
        bool bDirtyMatrix3D;
        
        ColorTransform  _colorTransform;
        ColorTransform  _concatenatedColorTransform;
        Matrix          _concatenatedMatrix;
        Matrix          _concatenatedMatrixInv;
        Matrix          _matrix;
        Matrix          _matrix3D;
        Rectangle*      _pixelBounds;
        Rectangle*      _rect;
        ofPoint         _rectTransformed[4];
        
    public:
        Transform();
        virtual ~Transform();
        
    protected:
        void update();
        
    private:
    };
    
}

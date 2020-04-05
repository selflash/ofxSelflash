#include "flTransform.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
	flTransform::flTransform() {
        
    }
    
    //--------------------------------------------------------------
    flTransform::~flTransform() {
        
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
//    void flTransform::update() {
////        bDirtyColorTransform = !_colorTransform.isEqual(colorTransform);
////        bDirtyMatrix         = !__matrix.isEqual(matrix);
////        bDirtyMatrix3D       = !_matrix3D.isEqual(matrix3D);
////
////        if(bDirtyColorTransform) _colorTransform.set(colorTransform);
////
////        if(bDirtyMatrix) _matrix.set(matrix);
////
////        if(bDirtyMatrix3D) _matrix3D.set(matrix3D);
//    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flTransform::__updatePixelBounds(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4) {
        _transformedPoints[0] = p1;
        _transformedPoints[1] = p2;
        _transformedPoints[2] = p3;
        _transformedPoints[3] = p4;
        
        //-- work out global bounding box.
        
        __pixelBounds.__setNull();                        // reset before enclosing new points.
        __pixelBounds.__encloseRect(_transformedPoints);
    }
    
}

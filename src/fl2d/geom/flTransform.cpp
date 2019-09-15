#include "flTransform.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
	flTransform::flTransform() {
        pixelBounds = new flRectangle();
        
        _pixelBounds = new flRectangle();
        _rect = new flRectangle();
    }
    
    //--------------------------------------------------------------
    //
    flTransform::~flTransform() {
        pixelBounds = NULL;
        
        _pixelBounds = NULL;
        _rect = NULL;
    }
    
    //--------------------------------------------------------------
    //
    void flTransform::update() {
        bDirtyColorTransform = !_colorTransform.isEqual(colorTransform);
        bDirtyMatrix         = !_matrix.isEqual(matrix);
        bDirtyMatrix3D       = !_matrix3D.isEqual(matrix3D);
        
        if(bDirtyColorTransform) _colorTransform.set(colorTransform);
        
        if(bDirtyMatrix) _matrix.set(matrix);
        
        if(bDirtyMatrix3D) _matrix3D.set(matrix3D);
    }
    
}

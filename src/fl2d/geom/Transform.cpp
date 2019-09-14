#include "Transform.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
    Transform::Transform() {
        pixelBounds = new Rectangle();
        
        _pixelBounds = new Rectangle();
        _rect = new Rectangle();
    }
    
    //--------------------------------------------------------------
    //
    Transform::~Transform() {
        pixelBounds = NULL;
        
        _pixelBounds = NULL;
        _rect = NULL;
    }
    
    //--------------------------------------------------------------
    //
    void Transform::update() {
        bDirtyColorTransform = !_colorTransform.isEqual(colorTransform);
        bDirtyMatrix         = !_matrix.isEqual(matrix);
        bDirtyMatrix3D       = !_matrix3D.isEqual(matrix3D);
        
        if(bDirtyColorTransform) _colorTransform.set(colorTransform);
        
        if(bDirtyMatrix) _matrix.set(matrix);
        
        if(bDirtyMatrix3D) _matrix3D.set(matrix3D);
    }
    
}

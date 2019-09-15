#include "flObject.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
    flObject::flObject() {
        _typeID = FL_TYPE_OBJECT;
        _no = 0;
        
        _debug = false;
    }

    //--------------------------------------------------------------
    //
    flObject::~flObject() {
        _typeID = 0;
        _no = 0;
        
        _debug = false;
        
        _properties.clear();
        
        _boolProperties.clear();
        _stringProperties.clear();
        _intProperties.clear();
        _floatProperties.clear();
        _doubleProperties.clear();
    }
    
}

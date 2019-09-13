#include "Object.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
    Object::Object() {
        _typeID = FL_TYPE_OBJECT;
        _no = 0;
        
        _debug = false;
    }

    //--------------------------------------------------------------
    //
    Object::~Object() {
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

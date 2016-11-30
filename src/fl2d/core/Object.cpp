#include "Object.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
    Object::Object(){
        _typeID = FL_TYPE_OBJECT;
        _no = 0;
        
        _debug = false;
    }

    //--------------------------------------------------------------
    //
    Object::~Object(){
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

    //--------------------------------------------------------------
    //
    bool Object::debug() { return _debug; }
    void Object::debug(bool value) { _debug = value; }

    //--------------------------------------------------------------
    //
    int Object::typeID() { return _typeID; }

    //--------------------------------------------------------------
    //
    int Object::no() { return _no; }
    void Object::no(int value) { _no = value; }
    
}

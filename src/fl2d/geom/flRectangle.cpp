#include "flRectangle.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    flRectangle::flRectangle() {
        
    }
    
    //--------------------------------------------------------------
    //������� x �p�����[�^�[�� y �p�����[�^�[�Ŏw�肳��A���ƍ����� width �p�����[�^�[ height �p�����[�^�[�Ŏw�肳�ꂽ�V���� Rectangle �I�u�W�F�N�g���쐬���܂��B
    flRectangle::flRectangle(float x, float y, float width, float height) {
        _xMin = x;
        _yMin = y;
        
        _xMax = _xMin + width;
        _yMax = _yMin + height;
    }
    
    //--------------------------------------------------------------
    flRectangle::~flRectangle() {
        _xMin = 0.0;
        _yMin = 0.0;
        
        _xMax = 0.0;
        _yMax = 0.0;
        
        _isChanged = false;
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //��`�̍������ x ���W�ł��B
    float flRectangle::x() const { return _xMin; }
    void flRectangle::x(float value) {
        if(_xMin != value) _isChanged = true;
        _xMin = value;
    }
    
    //--------------------------------------------------------------
    //��`�̍������ y ���W�ł��B
    float flRectangle::y() const{ return _yMin; }
    void flRectangle::y(float value) {
        if(_yMin != value) _isChanged = true;
        _yMin = value;
    }
    
    //--------------------------------------------------------------
    //��`�̍������ x ���W�ł��B
    float flRectangle::left() const{ return _xMin; }
    void flRectangle::left(float value) {
        if(_xMin != value) _isChanged = true;
        _xMin = value;
    }
    
    //--------------------------------------------------------------
    //x �v���p�e�B�� width �v���p�e�B�̍��v�ł��B
    float flRectangle::right() const{ return _xMax; }
    void flRectangle::right(float value) {
        if(_xMax != value) _isChanged = true;
        _xMax = value;
    }
    
    //--------------------------------------------------------------
    //��`�̍������ y ���W�ł��B
    float flRectangle::top() const{ return _yMin; }
    void flRectangle::top(float value) {
        if(_yMin != value) _isChanged = true;
        _yMin = value;
    }
    
    //--------------------------------------------------------------
    //y �v���p�e�B�� height �v���p�e�B�̍��v�ł��B
    float flRectangle::bottom() const{ return _yMax; }
    void flRectangle::bottom(float value) {
        if(_yMax != value) _isChanged = true;
        _yMax = value;
    }
    
    //--------------------------------------------------------------
    //Rectangle �I�u�W�F�N�g�̍�����̈ʒu�ŁA���̃|�C���g�� x ���W�� y ���W�Ō��܂�܂��B
    //    ofPoint& flRectangle::topLeft() const{ return _yMin; }
    //    void flRectangle::topLeft(ofPoint& value) { _yMin = value; }
    
    //--------------------------------------------------------------
    //Rectangle �I�u�W�F�N�g�̉E�����̈ʒu�ŁAright �v���p�e�B�� bottom �v���p�e�B�̒l�Ō��܂�܂��B
    //    ofPoint& flRectangle::bottomRight() const{ return _yMin; }
    //    void flRectangle::bottomRight(ofPoint& value) { _yMin = value; }
    
    //--------------------------------------------------------------
    //��`�̕��i�s�N�Z���P�ʁj�ł��B
    float flRectangle::width() { return _xMax - _xMin; }
    void flRectangle::width(float value) {
        if(_xMax != _xMin + value) _isChanged = true;
        _xMax = _xMin + value;
    }
    //--------------------------------------------------------------
    float flRectangle::height() { return _yMax - _yMin; }
    void flRectangle::height(float value) {
        if(_yMax != _yMin + value) _isChanged = true;
        _yMax = _yMin + value;
    }
    
    //--------------------------------------------------------------
    bool flRectangle::isNull() const {
        return (isnan(_xMin) && isnan(_xMax) && isnan(_yMin) && isnan(_yMax));
    }
    //--------------------------------------------------------------
    bool flRectangle::isZero() const {
        return (_xMin == 0.0 && _xMax == 0.0 && _yMin == 0.0 && _yMax == 0.0);
    }
    
    //--------------------------------------------------------------
    bool flRectangle::pointTest(float x, float y) {
        if(isNull()) return false;
        
//        if(_xMin < x && x < _xMax && _yMin < y && y < _yMax) return true;
        if(_xMin <= x && x <= _xMax && _yMin <= y && y <= _yMax) return true;
        return false;
        
        //        if(x < _xMin || x > _xMax || y < _yMin || y > _yMax) return false;
        //        return true;
    }
    
    //--------------------------------------------------------------
    bool flRectangle::isChanged() {
        bool b = _isChanged;
        _isChanged = false;
        return b;
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //    void flRectangle::__setNull() { _xMin = _yMin = _xMax = _yMax = 0 / 0.f; }
    void flRectangle::__setNull() { _xMin = _yMin = _xMax = _yMax = numeric_limits<float>::quiet_NaN(); }
    void flRectangle::__setZero() { _xMin = _yMin = _xMax = _yMax = 0.0; }

    //--------------------------------------------------------------
    void flRectangle::__expandTo(ofVec2f p) {
        __expandTo(p.x, p.y);
    }
    //--------------------------------------------------------------
//    void flRectangle::__expandTo(vec2 p) {
//        __expandTo(p.x, p.y);
//    }
    //--------------------------------------------------------------
    void flRectangle::__expandTo(float x, float y) {
        //        if(isNull()) {
        //            _xMin = x;
        //            _yMin = y;
        //            _xMax = x;
        //            _yMax = y;
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _xMin != MIN(_xMin, x) ||
           _yMin != MIN(_yMin, y) ||
           _xMax != MAX(_xMax, x) ||
           _yMax != MAX(_yMax, y)
           ) _isChanged = true;
        
        _xMin = MIN(_xMin, x);
        _yMin = MIN(_yMin, y);
        _xMax = MAX(_xMax, x);
        _yMax = MAX(_yMax, y);
    }
    
    //--------------------------------------------------------------
    void flRectangle::__expandToX(float x) {
        //        if(isNull()) {
        //            _xMin = x;
        //            _xMax = x;
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _xMin != MIN(_xMin, x) ||
           _xMax != MAX(_xMax, x)
           ) _isChanged = true;
        
        _xMin = MIN(_xMin, x);
        _xMax = MAX(_xMax, x);
    }
    
    //--------------------------------------------------------------
    void flRectangle::__expandToY(float y) {
        //        if(isNull()) {
        //            _yMin = y;
        //            _yMax = y;
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _yMin != MIN(_yMin, y) ||
           _yMax != MAX(_yMax, y)
           ) _isChanged = true;
        
        _yMin = MIN(_yMin, y);
        _yMax = MAX(_yMax, y);
    }
    
    //--------------------------------------------------------------
    void flRectangle::__encloseRect(const vector<ofPoint>& points) {
        for(int i = 0; i < points.size(); i++){
            if(i == 0){
                __setToPoint(points[0].x, points[0].y);
                continue;
            }
            __expandTo(points[i].x, points[i].y);
        }
    }
    
    //--------------------------------------------------------------
    void flRectangle::__expandToRect(const flRectangle& rect) {
        if(rect.isNull()) return;
        
        if(isNull()){
            *this = rect;
        } else {
            if(
               _xMin != MIN(_xMin, rect.left())  ||
               _yMin != MIN(_yMin, rect.top())   ||
               _xMax != MAX(_xMax, rect.right()) ||
               _yMax != MAX(_yMax, rect.bottom())
               ) _isChanged = true;
            
            _xMin = MIN(_xMin, rect.left());
            _yMin = MIN(_yMin, rect.top());
            _xMax = MAX(_xMax, rect.right());
            _yMax = MAX(_yMax, rect.bottom());
        }
    }
    
    //--------------------------------------------------------------
    void flRectangle::__setToPoint(float x, float y) {
        //        if(isNull()) {
        //            _xMin = x;
        //            _yMin = y;
        //            _xMax = x;
        //            _yMax = y;
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _xMin != x ||
           _xMax != x ||
           _yMin != y ||
           _yMax != y
           ) _isChanged = true;
        
        _xMin = _xMax = x;
        _yMin = _yMax = y;
    }
    
    //--------------------------------------------------------------
    void flRectangle::__expandToPoint(float x, float y) {
        if(isNull()) {
            __setToPoint(x, y);
        } else {
            __expandTo(x, y);
        }
    }
    
    //--------------------------------------------------------------
    void flRectangle::__expandToCircle(float x, float y, float radius) {
        if(isNull()) {
            _isChanged = true;
            
            _xMin = x - radius;
            _yMin = y - radius;
            _xMax = x + radius;
            _yMax = y + radius;
        } else {
            if(
               _xMin != MIN(_xMin, x - radius) ||
               _yMin != MIN(_yMin, y - radius) ||
               _xMax != MAX(_xMax, x + radius) ||
               _yMax != MAX(_yMax, y + radius)
               ) _isChanged = true;
            
            _xMin = MIN(_xMin, x - radius);
            _yMin = MIN(_yMin, y - radius);
            _xMax = MAX(_xMax, x + radius);
            _yMax = MAX(_yMax, y + radius);
        }
    }
    
    //--------------------------------------------------------------
    void flRectangle::__setToRect(float x1, float y1, float x2, float y2) {
        //        if(isNull()) {
        //            _xMin = x1;
        //            _yMin = y1;
        //            _xMax = x2;
        //            _yMax = y2;
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _xMin != x1 ||
           _yMin != y1 ||
           _xMax != x2 ||
           _yMax != y2
           ) _isChanged = true;
        
        _xMin = x1;
        _yMin = y1;
        _xMax = x2;
        _yMax = y2;
    }
    
    //--------------------------------------------------------------
    void flRectangle::__setToRect(const flRectangle& rect) {
        //        if(isNull()) {
        //            _xMin = rect.left();
        //            _yMin = rect.top();
        //            _xMax = rect.right();
        //            _yMax = rect.bottom();
        //            _isChanged = true;
        //            return;
        //        }
        
        if(
           _xMin != rect.left()  ||
           _yMin != rect.top()   ||
           _xMax != rect.right() ||
           _yMax != rect.bottom()
           ) _isChanged = true;
        
        _xMin = rect.left();
        _yMin = rect.top();
        _xMax = rect.right();
        _yMax = rect.bottom();
    }
    
}

#include "Rectangle.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Rectangle::Rectangle() {
        
    }
    
    //--------------------------------------------------------------
    //左上隅が x パラメーターと y パラメーターで指定され、幅と高さが width パラメーター height パラメーターで指定された新しい Rectangle オブジェクトを作成します。
    Rectangle::Rectangle(float x, float y, float width, float height) {
        _xMin = x;
        _yMin = y;
        
        _xMax = _xMin + width;
        _yMax = _yMin + height;
    }
    
    //--------------------------------------------------------------
    //
    Rectangle::~Rectangle() {
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
    //矩形の左上隅の x 座標です。
    float Rectangle::x() const { return _xMin; }
    void Rectangle::x(float value) {
        if(_xMin != value) _isChanged = true;
        _xMin = value;
    }
    
    //--------------------------------------------------------------
    //矩形の左上隅の y 座標です。
    float Rectangle::y() const{ return _yMin; }
    void Rectangle::y(float value) {
        if(_yMin != value) _isChanged = true;
        _yMin = value;
    }
    
    //--------------------------------------------------------------
    //矩形の左上隅の x 座標です。
    float Rectangle::left() const{ return _xMin; }
    void Rectangle::left(float value) {
        if(_xMin != value) _isChanged = true;
        _xMin = value;
    }
    
    //--------------------------------------------------------------
    //x プロパティと width プロパティの合計です。
    float Rectangle::right() const{ return _xMax; }
    void Rectangle::right(float value) {
        if(_xMax != value) _isChanged = true;
        _xMax = value;
    }
    
    //--------------------------------------------------------------
    //矩形の左上隅の y 座標です。
    float Rectangle::top() const{ return _yMin; }
    void Rectangle::top(float value) {
        if(_yMin != value) _isChanged = true;
        _yMin = value;
    }
    
    //--------------------------------------------------------------
    //y プロパティと height プロパティの合計です。
    float Rectangle::bottom() const{ return _yMax; }
    void Rectangle::bottom(float value) {
        if(_yMax != value) _isChanged = true;
        _yMax = value;
    }
    
    //--------------------------------------------------------------
    //Rectangle オブジェクトの左上隅の位置で、そのポイントの x 座標と y 座標で決まります。
    //    ofPoint& Rectangle::topLeft() const{ return _yMin; }
    //    void Rectangle::topLeft(ofPoint& value) { _yMin = value; }
    
    //--------------------------------------------------------------
    //Rectangle オブジェクトの右下隅の位置で、right プロパティと bottom プロパティの値で決まります。
    //    ofPoint& Rectangle::bottomRight() const{ return _yMin; }
    //    void Rectangle::bottomRight(ofPoint& value) { _yMin = value; }
    
    //--------------------------------------------------------------
    //矩形の幅（ピクセル単位）です。
    float Rectangle::width() { return _xMax - _xMin; }
    void Rectangle::width(float value) {
        if(_xMax != _xMin + value) _isChanged = true;
        _xMax = _xMin + value;
    }
    //--------------------------------------------------------------
    //
    float Rectangle::height() { return _yMax - _yMin; }
    void Rectangle::height(float value) {
        if(_yMax != _yMin + value) _isChanged = true;
        _yMax = _yMin + value;
    }
    
    //--------------------------------------------------------------
    //
    bool Rectangle::isNull() const {
        return (isnan(_xMin) && isnan(_xMax) && isnan(_yMin) && isnan(_yMax));
    }
    //--------------------------------------------------------------
    //
    bool Rectangle::isZero() const {
        return (_xMin == 0.0 && _xMax == 0.0 && _yMin == 0.0 && _yMax == 0.0);
    }
    
    //--------------------------------------------------------------
    //
    bool Rectangle::pointTest(float x, float y) {
        if(isNull()) return false;
        
        if(_xMin < x && x < _xMax && _yMin < y && y < _yMax) return true;
        return false;
        
        //        if(x < _xMin || x > _xMax || y < _yMin || y > _yMax) return false;
        //        return true;
    }
    
    //--------------------------------------------------------------
    //
    bool Rectangle::isChanged() {
        bool b = _isChanged;
        _isChanged = false;
        return b;
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    //    void Rectangle::__setNull() { _xMin = _yMin = _xMax = _yMax = 0 / 0.f; }
    void Rectangle::__setNull() { _xMin = _yMin = _xMax = _yMax = numeric_limits<float>::quiet_NaN(); }
    void Rectangle::__setZero() { _xMin = _yMin = _xMax = _yMax = 0.0; }
    
    //--------------------------------------------------------------
    //
    void Rectangle::__expandTo(float x, float y) {
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
    //
    void Rectangle::__expandToX(float x) {
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
    //
    void Rectangle::__expandToY(float y) {
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
    //
    void Rectangle::__encloseRect(const vector<ofPoint>& points) {
        for(int i = 0; i < points.size(); i++){
            if(i == 0){
                __setToPoint(points[0].x, points[0].y);
                continue;
            }
            __expandTo(points[i].x, points[i].y);
        }
    }
    
    //--------------------------------------------------------------
    //
    void Rectangle::__expandToRect(const Rectangle& rect) {
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
    //
    void Rectangle::__setToPoint(float x, float y) {
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
    //
    void Rectangle::__expandToPoint(float x, float y) {
        if(isNull()) {
            __setToPoint(x, y);
        } else {
            __expandTo(x, y);
        }
    }
    
    //--------------------------------------------------------------
    //
    void Rectangle::__expandToCircle(float x, float y, float radius) {
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
    //
    void Rectangle::__setToRect(float x1, float y1, float x2, float y2) {
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
    //
    void Rectangle::__setToRect(const Rectangle& rect) {
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

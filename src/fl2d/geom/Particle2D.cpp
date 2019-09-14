#include "Particle2D.h"

namespace fl2d {
    
    //--------------------------------------------------------------
    //
    Particle2D::Particle2D() {
        //寿命
        _count = 0;
        _delay = 0;
        _life = 0;
        
        //位置
        _position = new ofVec3f(0.0, 0.0, 0.0);
        _startPosition = new ofVec3f(0.0, 0.0, 0.0);
        _velPosition = new ofVec3f(0.0, 0.0, 0.0);
        
        //回転
        _rotation = 0;
        _startRotation = 0;
        _velRotation = 0;
        
        _rotationXYZ = new ofVec3f(0, 0, 0);
        _startRotationXYZ = new ofVec3f(0, 0, 0);
        _velRotationXYZ = new ofVec3f(0, 0, 0);
        
        //サイズ
        _size = new ofVec3f(0.0, 0.0, 0.0);
        _sizeVel = new ofVec3f(0.0, 0.0, 0.0);
        _startSize = new ofVec3f(0.0, 0.0, 0.0);
        
        //大きさ
        _scale = new ofVec3f(0.0, 0.0, 0.0);
        _startScale = new ofVec3f(0.0, 0.0, 0.0);
        _velScale = new ofVec3f(0.0, 0.0, 0.0);
        
        //色
        _color = new ofFloatColor(1.0, 1.0, 1.0);
        _startColor = new ofFloatColor(1.0, 1.0, 1.0);
        _velColor = new ofFloatColor(0.0, 0.0, 0.0);
    }
    
    //--------------------------------------------------------------
    //
    Particle2D::~Particle2D() {
        //寿命
        _count = 0;
        _delay = 0;
        _life = 0;
        
        //位置
        delete _position;
        _position = NULL;
        delete _startPosition;
        _startPosition = NULL;
        delete _velPosition;
        _velPosition = NULL;
        
        //回転
        _rotation = 0;
        _startRotation = 0;
        _velRotation = 0;
        
        //サイズ
        delete _size;
        _size = NULL;
        delete _startSize;
        _startSize = NULL;
        delete _sizeVel;
        _sizeVel = NULL;
        
        //大きさ
        delete _scale;
        _scale = NULL;
        delete _startScale;
        _startScale = NULL;
        delete _velScale;
        _velScale = NULL;
        
        //色
        delete _color;
        _color = NULL;
        delete _startColor;
        _startColor = NULL;
        delete _velColor;
        _velColor = NULL;
    }
    
    //==============================================================
    // 
    //==============================================================
    
    //--------------------------------------------------------------
    //
    const int& Particle2D::delay() { return _delay; }
    void Particle2D::delay(const int value) { _delay = value; }
    
    //--------------------------------------------------------------
    //
    const int& Particle2D::life() { return _life; }
    void Particle2D::life(const int value) {
        _life = value;
        if(_life <= 0) _life = 0;
    }
    
    //==============================================================
    // POSITION
    //==============================================================
    
    const float& Particle2D::x() { return _position->x; }
    void Particle2D::x(const float value){ _position->x = value; }
    
    const float& Particle2D::y() { return _position->y; }
    void Particle2D::y(const float value){ _position->y = value; }
    
    const float& Particle2D::z() { return _position->z; }
    void Particle2D::z(const float value){ _position->z = value; }
    
    const float& Particle2D::startX() { return _startPosition->x; };
    void Particle2D::startX(const float value) { _startPosition->x = value; };
    
    const float& Particle2D::startY() { return _startPosition->y; };
    void Particle2D::startY(const float value) { _startPosition->y = value; };
    
    const float& Particle2D::startZ() { return _startPosition->z; };
    void Particle2D::startZ(const float value) { _startPosition->z = value; };
    
    const float& Particle2D::velX() { return _velPosition->x; };
    void Particle2D::velX(float value) { _velPosition->x = value; };
    
    const float& Particle2D::velY() { return _velPosition->y; };
    void Particle2D::velY(const float value) { _velPosition->y = value; };
    
    const float& Particle2D::velZ() { return _velPosition->z; };
    void Particle2D::velZ(const float value) { _velPosition->z = value; };
    
    const ofVec3f& Particle2D::position() { return *_position; }
    void Particle2D::position(const float x, const float y, const float z){
        _position->set(x, y, z);
        _startPosition->set(x, y, z);
    }
    const ofVec3f& Particle2D::velPosition() { return *_velPosition; }
    void Particle2D::velPosition(const float x, const float y, const float z){
        _velPosition->set(x, y, z);
    }
    
    //==============================================================
    // ROTATION X Y Z
    //==============================================================
    
    const float& Particle2D::rotationX() { return _rotationXYZ->x; };
    void Particle2D::rotationX(const float value) { _rotationXYZ->x = value; };
    
    const float& Particle2D::rotationY() { return _rotationXYZ->y; };
    void Particle2D::rotationY(const float value) { _rotationXYZ->y = value; };
    
    const float& Particle2D::rotationZ() { return _rotationXYZ->z; };
    void Particle2D::rotationZ(const float value) { _rotationXYZ->z = value; };
    
    const float& Particle2D::startRotationX() { return _startRotationXYZ->x; };
    void Particle2D::startRotationX(const float value) { _startRotationXYZ->x = value; };
    
    const float& Particle2D::startRotationY() { return _startRotationXYZ->y; };
    void Particle2D::startRotationY(const float value) { _startRotationXYZ->y = value; };
    
    const float& Particle2D::startRotationZ() { return _startRotationXYZ->z; };
    void Particle2D::startRotationZ(const float value) { _startRotationXYZ->z = value; };
    
    const float& Particle2D::velRotationX() { return _velRotationXYZ->x; };
    void Particle2D::velRotationX(const float value) { _velRotationXYZ->x = value; };
    
    const float& Particle2D::velRotationY() { return _velRotationXYZ->y; };
    void Particle2D::velRotationY(const float value) { _velRotationXYZ->y = value; };
    
    const float& Particle2D::velRotationZ() { return _velRotationXYZ->z; };
    void Particle2D::velRotationZ(const float value) { _velRotationXYZ->z = value; };
    
    const ofVec3f& Particle2D::rotationXYZ() { return *_rotationXYZ; }
    void Particle2D::rotationXYZ(const float& rotationX, const float& rotationY, const float& rotationZ){
        _rotationXYZ->set(rotationX, rotationY, rotationZ);
        _startRotationXYZ->set(rotationX, rotationY, rotationZ);
    }
    const ofVec3f& Particle2D::velRotationXYZ() { return *_velRotationXYZ; }
    void Particle2D::velRotationXYZ(const float& x, const float& y, const float& z){
        _velRotationXYZ->set(x, y, z);
    }
    
    //==============================================================
    // WIDTH HEIGHT DEPTH
    //==============================================================
    
    const float& Particle2D::width() { return _size->x; };
    void Particle2D::width(const float value) { _size->x = value; };
    
    const float& Particle2D::height() { return _size->y; };
    void Particle2D::height(const float value) { _size->y = value; };
    
    const float& Particle2D::depth() { return _size->z; };
    void Particle2D::depth(const float value) { _size->z = value; };
    
    const float& Particle2D::startWidth() { return _startSize->x; };
    void Particle2D::startWidth(const float value) { _startSize->x = value; };
    
    const float& Particle2D::startHeight() { return _startSize->y; };
    void Particle2D::startHeight(const float value) { _startSize->y = value; };
    
    const float& Particle2D::startDepth() { return _startSize->z; };
    void Particle2D::startDepth(const float value) { _startSize->z = value; };
    
    const float& Particle2D::velWidth() { return _sizeVel->x; };
    void Particle2D::velWidth(const float value) { _sizeVel->x = value; };
    
    const float& Particle2D::velHeight() { return _sizeVel->y; };
    void Particle2D::velHeight(const float value) { _sizeVel->y = value; };
    
    const float& Particle2D::velDepth() { return _sizeVel->z; };
    void Particle2D::velDepth(const float value) { _sizeVel->z = value; };
    
    //--------------------------------------------------------------
    //
    const ofVec3f& Particle2D::size(){ return *_size; }
    void Particle2D::size(const float width, const float height, const float depth){
        _size->set(width, height, depth);
        _startSize->set(width, height, depth);
    }
    //--------------------------------------------------------------
    //
    void Particle2D::velSize(const float x, const float y, const float z){ _sizeVel->set(x, y, z); }
    
    //==============================================================
    // SCALE
    //==============================================================
    
    const float& Particle2D::scaleX() { return _scale->x; };
    void Particle2D::scaleX(const float value) { _scale->x = value; };
    
    const float& Particle2D::scaleY() { return _scale->y; };
    void Particle2D::scaleY(const float value) { _scale->y = value; };
    
    const float& Particle2D::scaleZ() { return _scale->z; };
    void Particle2D::scaleZ(const float value) { _scale->z = value; };
    
    const float& Particle2D::startScaleX() { return _startScale->x; };
    void Particle2D::startScaleX(const float value) { _startScale->x = value; };
    
    const float& Particle2D::startScaleY() { return _startScale->y; };
    void Particle2D::startScaleY(const float value) { _startScale->y = value; };
    
    const float& Particle2D::startScaleZ() { return _startScale->z; };
    void Particle2D::startScaleZ(const float value) { _startScale->z = value; };
    
    const float& Particle2D::velScaleX() { return _velScale->x; };
    void Particle2D::velScaleX(const float value) { _velScale->x = value; };
    
    const float& Particle2D::velScaleY() { return _velScale->y; };
    void Particle2D::velScaleY(const float value) { _velScale->y = value; };
    
    const float& Particle2D::velScaleZ() { return _velScale->z; };
    void Particle2D::velScaleZ(const float value) { _velScale->z = value; };
    
    //--------------------------------------------------------------
    //
    const ofVec3f& Particle2D::scale() { return *_scale; }
    void Particle2D::scale(const float x, const float y, const float z) {
        _scale->set(x, y, z);
        _startScale->set(x, y, z);
    }
    
    //--------------------------------------------------------------
    //
    const ofVec3f& Particle2D::velScale() { return *_velScale; }
    void Particle2D::velScale(const float x, const float y, const float z){
        _velScale->set(x, y, z);
    }
    
    //==============================================================
    // COLOR
    //==============================================================
    
    const float& Particle2D::red() { return _color->r; }
    void Particle2D::red(const float value) { _color->r = value; }
    
    const float& Particle2D::green() { return _color->g; }
    void Particle2D::green(const float value) { _color->g = value; }
    
    const float& Particle2D::blue() { return _color->b; }
    void Particle2D::blue(const float value) { _color->b = value; }
    
    const float& Particle2D::velRed() { return _velColor->r; }
    void Particle2D::velRed(const float value) { _velColor->r = value; }
    
    const float& Particle2D::velGreen() { return _velColor->g; }
    void Particle2D::velGreen(const float value) { _velColor->g = value; }
    
    const float& Particle2D::velBlue() { return _velColor->b; }
    void Particle2D::velBlue(const float value) { _velColor->b = value; }
    
    //--------------------------------------------------------------
    //
    const ofFloatColor& Particle2D::color() { return *_color; }
    void Particle2D::color(const float r, const float g, const float b){
        _color->r = r;
        _color->g = g;
        _color->b = b;
        
        _startColor->r = r;
        _startColor->g = g;
        _startColor->b = b;
    }
    void Particle2D::color(const ofFloatColor& value) {
        _color = new ofFloatColor(value.r, value.g, value.b);
    }
    //--------------------------------------------------------------
    //
    const ofFloatColor& Particle2D::startColor() { return *_startColor; }
    void Particle2D::startColor(const float r, const float g, const float b){
        _startColor->r = r;
        _startColor->g = g;
        _startColor->b = b;
    }
    void Particle2D::startColor(const ofFloatColor& value) {
        _startColor = new ofFloatColor(value.r, value.g, value.b);
    }
    //--------------------------------------------------------------
    //
    const ofFloatColor& Particle2D::velColor() { return *_color; }
    void Particle2D::velColor(const float r, const float g, const float b){
        _velColor->r = r;
        _velColor->g = g;
        _velColor->b = b;
    }
    void Particle2D::velColor(const ofFloatColor& value) {
        _velColor = new ofFloatColor(value.r, value.g, value.b);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Particle2D::update() {
        if(_delay > _count) {
            _count ++;
            return;
        }
        
        //寿命
        life(life() - 1);
        
        //位置
        x(x() + velX());
        y(y() + velY());
        z(z() + velZ());
        
        //回転
        rotationX(rotationX() + velRotationX());
        rotationY(rotationY() + velRotationY());
        rotationZ(rotationZ() + velRotationZ());
        
        //サイズ
        scaleX(scaleX() + velScaleX());
        scaleY(scaleY() + velScaleY());
        scaleZ(scaleZ() + velScaleZ());
        
        //色
        red(red() + velRed());
        green(green() + velGreen());
        blue(blue() + velBlue());
        
        if(life() <= 0) reset();
    }
    
    //--------------------------------------------------------------
    //
    void Particle2D::draw(){
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Particle2D::clear(){
        
    }
    
    //--------------------------------------------------------------
    //
    void Particle2D::reset(){
        //位置
        x(startX());
        y(startY());
        z(startZ());
        //回転
        rotationX(startRotationX());
        rotationY(startRotationY());
        rotationZ(startRotationZ());
        //サイズ
        scaleX(startScaleX());
        scaleY(startScaleY());
        scaleZ(startScaleZ());
        //色
        color(ofFloatColor(_startColor->r, _startColor->g, _startColor->b));
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
}

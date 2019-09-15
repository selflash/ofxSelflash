#include "Graphics.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Graphics::Graphics() {
        _typeID = FL_TYPE_GRAPHICS;
        //_commandList = NULL;
        
        _thickness = 1;
        
        _lineEnabled = false;
        _fillEnabled = false;
        
        //        __alpha = 1.0;
        __rect = new flRectangle();
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _IsMoveTo = false;
        
        _compoundAlpha = 1.0;
    }
    
    //--------------------------------------------------------------
    //
    Graphics::~Graphics() {
        _commandList.clear();
        
        _thickness = 0;
        
        _lineEnabled = false;
        _fillEnabled = false;
        
        //        __alpha = 0.0;
        
        delete __rect;
        __rect = NULL;
        
        _enabledSmoothing = false;
        _enabledAntiAliasing = false;
        
        _IsMoveTo = false;
        
        _compoundAlpha = 0.0;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Graphics::__draw() {
        //cout << _commandList.size() << endl;
        
        GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
        GLboolean preMultiSample = glIsEnabled(GL_MULTISAMPLE);
        if(_enabledSmoothing) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
        if(_enabledAntiAliasing) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        
        ofPushStyle();
        int i; int l;
        l = _commandList.size();
        for(i = 0; i < l; i++) {
            DrawCommand* command = _commandList[i];
            int type = command->type;
            if(type == FL_COMMAND_BEGIN_FILL) _beginFill(command->color, command->alpha);
            //if(type == FL_COMMAND_BEAGIN_GRADIENT_FILL) _drawCircle(command.x, command.y, command.radius);
            if(type == FL_COMMAND_END_FILL) _endFill();
            if(type == FL_COMMAND_DRAW_CIRCLE) _drawCircle(command->x, command->y, command->radius);
            //if(type == FL_COMMAND_DRAW_ELLIPSE) _drawCircle(command.x, command.y, command.radius);
            if(type == FL_COMMAND_DRAW_RECT) _drawRect(command->x, command->y, command->width, command->height);
            if(type == FL_COMMAND_DRAW_ROUNDRECT) _drawRoundRect(command->x, command->y, command->width, command->height, command->radius);
            if(type == FL_COMMAND_LINESTYLE) _lineStyle(command->thickness, command->color, command->alpha);
            if(type == FL_COMMAND_LINE_TO) _lineTo(command->x, command->y);
            if(type == FL_COMMAND_MOVE_TO) _moveTo(command->x, command->y);
            //if(type == FL_COMMAND_CURVE_TO) _curveTo(command.x, command.y, command.radius);
            if(type == FL_COMMAND_CLEAR) {
                //            _clear();
                //_fillEnabled = false;
                //            _commandList.erase(_commandList.begin() + i);
                //            _clear(command->index);
                //_commandList.erase(_commandList.begin() + i);
                //--i;
                //--l;
                //if(i == command->index) break;
                //return;
            }
        }
        ofPopStyle();
        
        if(preMultiSample == GL_TRUE) { ofEnableAntiAliasing(); } else { ofDisableAntiAliasing(); }
        if(preLineSmooth == GL_TRUE) { ofEnableSmoothing(); } else { ofDisableSmoothing(); }
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Graphics::lineStyle(float thickness, int color, float alpha) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_LINESTYLE;
        command->thickness = thickness;
        command->color = color;
        command->alpha = alpha;
        
        _commandList.push_back(command);    
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::beginFill(int color, float alpha) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_BEGIN_FILL;
        command->color = color;
        command->alpha = alpha;
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::endFill() {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_END_FILL;
        
        _commandList.push_back(command);    
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::drawCircle(float x, float y, float radius) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_DRAW_CIRCLE;
        command->x = x;
        command->y = y;
        command->radius = radius;
        command->width = radius * 2;
        command->height = radius * 2;
        
        //このコマンドが影響する描画範囲
        command->left = x - radius;
        command->right = x + radius;
        command->top = y - radius;
        command->bottom = y + radius;
        
        __rect->__expandTo(command->left, command->top);
        __rect->__expandTo(command->right, command->bottom);
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::drawRect(float x, float y, float width, float height) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_DRAW_RECT;
        command->x = x;
        command->y = y;
        command->width = width;
        command->height = height;
        
        //このコマンドが影響する描画範囲
        command->left = x;
        command->right = x + width;
        command->top = y;
        command->bottom = y + height;
        
        __rect->__expandTo(command->left, command->top);
        __rect->__expandTo(command->right, command->bottom);
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::drawRoundRect(float x, float y, float width, float height, float radius) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_DRAW_ROUNDRECT;
        command->x = x;
        command->y = y;
        command->width = width;
        command->height = height;
        command->radius = radius;
        
        //このコマンドが影響する描画範囲
        command->left = x;
        command->right = x + width;
        command->top = y;
        command->bottom = y + height;
        
        __rect->__expandTo(command->left, command->top);
        __rect->__expandTo(command->right, command->bottom);
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::lineTo(float x, float y) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_LINE_TO;
        command->x = x;
        command->y = y;
        
        __rect->__expandTo(command->x, command->y);
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::moveTo(float x, float y) {
        DrawCommand* command = new DrawCommand();
        command->type = FL_COMMAND_MOVE_TO;
        command->x = x;
        command->y = y;
        
        __rect->__expandTo(command->x, command->y);
        
        _commandList.push_back(command);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::clear() {
        //        DrawCommand* command = new DrawCommand();
        //        command->type = FL_COMMAND_CLEAR;
        //        command->index = _commandList.size();
        
        _fillEnabled = false;
        
        int i; int l;
        l = _commandList.size();
        for(i = 0; i < l; i++) {
            delete _commandList[i];
        }
        _commandList.clear();
        
        //        __rect->__setNull();
        __rect->__setZero();
        
        //    _commandList.push_back(command);
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Graphics::_lineStyle(float thickness, int color, float alpha) {
        
        _lineColor.r = (color >> 16) & 0xff;
        _lineColor.g = (color >> 8) & 0xff;
        _lineColor.b = (color >> 0) & 0xff;
        _lineColor.a = (_compoundAlpha * 255) * alpha;
        
        _lineEnabled = true;
        
        _thickness = thickness;
        
        //ofNoFill();
        //ofSetLineWidth(thickness);
        //ofSetColor(_lineColor);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::_beginFill(int color, float alpha) {
        //printf("[Graphics]_beginFill(%i, %f)\n", color, alpha);
        
        _fillColor.r = (color >> 16) & 0xff;
        _fillColor.g = (color >> 8) & 0xff;
        _fillColor.b = (color >> 0) & 0xff;
        _fillColor.a = (_compoundAlpha * 255) * alpha;
        
        _fillEnabled = true;
        
        //        if(_IsMoveTo) {
        //            ofEndShape();
        //            ofPopStyle();
        //        }
        //        _IsMoveTo = false;
        ofSetColor(_fillColor);
        
        //        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
        //        ofBeginShape();
        
        //ofFill();
        //ofSetColor(_fillColor);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::_endFill() {
        //printf("[Graphics]_endFill(%i, %f)\n", color, alpha);
        
        //_fillColor.r = 255;
        //_fillColor.g = 255;
        //_fillColor.b = 255;
        //_fillColor.a = (__alpha * 255);
        
        _thickness = 1;
        ofSetLineWidth(_thickness);
        
        _lineEnabled = false;
        _fillEnabled = false;
        
        
        //        if(_IsMoveTo) {
        //            ofEndShape();
        //            ofPopStyle();
        //        }
        //        _IsMoveTo = false;
        
        //ofFill();
        //ofSetColor(_fillColor);
    }
    
    //--------------------------------------------------------------
    //
    void Graphics::_drawCircle(float x, float y, float radius) {
        ofPushStyle();
        
        if(_fillEnabled) {
            ofFill();
            ofSetColor(_fillColor);
            ofSetCircleResolution(100);
            ofDrawCircle(x, y, radius);
        }
        
        if(_lineEnabled){
            ofNoFill();
            ofSetLineWidth(_thickness);
            ofSetColor(_lineColor);
            ofSetCircleResolution(100);
            ofDrawCircle(x, y, radius);
            ofFill();
        }
        
        ofPopStyle();
    }
    //--------------------------------------------------------------
    //
    void Graphics::_drawRect(float x, float y, float width, float height) {
        ofPushStyle();
        
        if(_fillEnabled) {
            ofFill();
            ofSetColor(_fillColor);
            ofDrawRectangle(x, y, width, height);
        }
        
        if(_lineEnabled) {
            ofNoFill();
            ofSetLineWidth(_thickness);
            ofSetColor(_lineColor);
            ofDrawRectangle(x, y, width, height);
            //ofLine(x - 1, y - 1, x, y);
            ofFill();
        }
        
        ofPopStyle();
    }
    //--------------------------------------------------------------
    //
    void Graphics::_drawRoundRect(float x, float y, float width, float height, float radius) {
        ofPushStyle();
        
        if(_fillEnabled) {
            ofFill();
            ofSetColor(_fillColor);
            ofDrawRectRounded(x, y, width, height, radius);
        }
        
        if(_lineEnabled) {
            ofNoFill();
            ofSetLineWidth(_thickness);
            ofSetColor(_lineColor);
            ofDrawRectRounded(x, y, width, height, radius);
            ofFill();
        }
        
        ofPopStyle();
    }
    //--------------------------------------------------------------
    //
    void Graphics::_lineTo(float x, float y) {
        ofPushStyle();
        
        if(_lineEnabled) {
            ofNoFill();
            ofSetLineWidth(_thickness);
            ofSetColor(_lineColor);
            ofDrawLine(_moveToX, _moveToY, x, y);
            ofFill();
        }
        
        _moveToX = x;
        _moveToY = y;
        
        if(_fillEnabled) {
            ofVertex(x, y);
        }
        
        ofPopStyle();
    }
    //--------------------------------------------------------------
    //
    void Graphics::_moveTo(float x, float y) {
        _moveToX = x;
        _moveToY = y;
        
        if(_fillEnabled) {
            //            if(_IsMoveTo) {
            //                cout << x << ", " << y << endl;
            //                ofEndShape();
            //                ofPopStyle();
            //            }
            //            _IsMoveTo = true;
            
            //            ofPushStyle();
            //            ofFill();
            //            ofSetColor(_fillColor);
            //            
            //            ofSetPolyMode(OF_POLY_WINDING_NONZERO);
            //            ofBeginShape();
            
            ofVertex(x, y);
        }
    }
    //--------------------------------------------------------------
    //
    void Graphics::_clear(int index) {
        //cout << _commandList.size() << endl;
        //    _commandList.clear();
        
        _fillEnabled = false;
        
        //TODO メモリーリークしてない？
        //    for(int i = 0; i < _commandList.size(); i++) {
        //        _commandList.erase(_commandList.begin() + i);
        //        if(i == index) break;
        //    }
        
        int i = 0;
        int l = _commandList.size();
        
        for(i; i < l; i++) {
            if(i == index) break;
            _commandList.erase(_commandList.begin() + i);
            --i;
            --l;
        }
        
        //        __rect->__setNull();
        __rect->__setZero();
    }
    
    //--------------------------------------------------------------
    //
    float Graphics::__compoundAlpha(){ return _compoundAlpha; }
    void Graphics::__compoundAlpha(float value){ _compoundAlpha = value; }
    
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_left() { return __rect->left(); }
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_right() { return __rect->right(); }
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_top() { return __rect->top(); }
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_bottom() { return __rect->bottom(); }
    //
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_width() { return __rect->width(); }
    //    //--------------------------------------------------------------
    //    //
    //    float Graphics::_height() { return __rect->height(); }
    
}

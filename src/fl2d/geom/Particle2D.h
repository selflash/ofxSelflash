#pragma once

#include "ofMain.h"
#include "../events/EventDispatcher.h"

namespace fl2d {
    class Particle2D : public EventDispatcher {
        public:
            float radius;
            float theta1;
            float theta2;
            
        protected:
            int _count;
            int _delay;
            int _life;

            //位置
            ofVec3f* _position;
            ofVec3f* _startPosition;
            ofVec3f* _velPosition;
        
            //回転
            float _rotation;
            float _startRotation;
            float _velRotation;
            
            ofVec3f* _rotationXYZ;
            ofVec3f* _startRotationXYZ;
            ofVec3f* _velRotationXYZ;
        
            //横幅、縦幅、奥行き
            //width, height, depth
            ofVec3f* _size;
            ofVec3f* _startSize;
            ofVec3f* _sizeVel;
        
            //拡大・縮小
            ofVec3f* _scale;
            ofVec3f* _startScale;
            ofVec3f* _velScale;
        
            //色
            ofFloatColor* _color;
            ofFloatColor* _startColor;
            ofFloatColor* _velColor;
        
        private:
        
        public:
            Particle2D();
            ~Particle2D();
        
            virtual const int& delay();
            virtual void delay(const int value);
            virtual const int& life();
            virtual void life(const int value);
        
            //--------------------------------------
            //位置
            virtual const float& x();
            virtual void  x(const float value);
            virtual const float& y();
            virtual void  y(const float value);
            virtual const float& z();
            virtual void  z(const float value);
            //--------------------------------------
        
            virtual const float& startX();
            virtual void startX(const float value);
            virtual const float& startY();
            virtual void startY(const float value);
            virtual const float& startZ();
            virtual void startZ(const float value);
        
            virtual const float& velX();
            virtual void velX(const float value);
            virtual const float& velY();
            virtual void velY(const float value);
            virtual const float& velZ();
            virtual void velZ(const float value);
        
            virtual const ofVec3f& position();
            virtual void position(const float x = 0, const float y = 0, const float z = 0);
            virtual const ofVec3f& velPosition();
            virtual void velPosition(const float x = 0, const float y = 0, const float z = 0);
            //--------------------------------------
            
            //--------------------------------------
            //回転
            virtual const float& rotationX();
            virtual void rotationX(const float value);
            virtual const float& rotationY();
            virtual void rotationY(const float value);
            virtual const float& rotationZ();
            virtual void rotationZ(const float value);
            
            virtual const float& startRotationX();
            virtual void startRotationX(const float value);
            virtual const float& startRotationY();
            virtual void startRotationY(const float value);
            virtual const float& startRotationZ();
            virtual void startRotationZ(const float value);
            
            virtual const float& velRotationX();
            virtual void velRotationX(const float value);
            virtual const float& velRotationY();
            virtual void velRotationY(const float value);
            virtual const float& velRotationZ();
            virtual void velRotationZ(const float value);
            
            virtual const ofVec3f& rotationXYZ();
            virtual void rotationXYZ(const float& rotationX = 0, const float& rotationY = 0, const float& rotationZ = 0);
            virtual const ofVec3f& velRotationXYZ();
            virtual void velRotationXYZ(const float& rotationX = 0, const float& rotationY = 0, const float& rotationZ = 0);
            //--------------------------------------

            //--------------------------------------
            //横幅、縦幅、奥行き
            virtual const float& width();
            virtual void width(const float value);
            virtual const float& height();
            virtual void height(const float value);
            virtual const float& depth();
            virtual void depth(const float value);
            
            virtual const float& startWidth();
            virtual void startWidth(const float value);
            virtual const float& startHeight();
            virtual void startHeight(const float value);
            virtual const float& startDepth();
            virtual void startDepth(const float value);
            
            virtual const float& velWidth();
            virtual void velWidth(const float value);
            virtual const float& velHeight();
            virtual void velHeight(const float value);
            virtual const float& velDepth();
            virtual void velDepth(const float value);
            
            const ofVec3f& size();
            virtual void size(const float width = 0, const float height = 0, const float depth = 0);
        
            const ofVec3f& velSize();
            virtual void velSize(const float width = 0, const float height = 0, const float depth = 0);
            //--------------------------------------
            
            //--------------------------------------
            //拡大・縮小
            virtual const float& scaleX();
            virtual void scaleX(const float value);
            virtual const float& scaleY();
            virtual void scaleY(const float value);
            virtual const float& scaleZ();
            virtual void scaleZ(const float value);
            
            virtual const float& startScaleX();
            virtual void startScaleX(const float value);
            virtual const float& startScaleY();
            virtual void startScaleY(const float value);
            virtual const float& startScaleZ();
            virtual void startScaleZ(const float value);
            
            virtual const float& velScaleX();
            virtual void velScaleX(const float value);
            virtual const float& velScaleY();
            virtual void velScaleY(const float value);
            virtual const float& velScaleZ();
            virtual void velScaleZ(const float value);
        
            virtual const ofVec3f& scale();
            virtual void scale(const float x = 0, const float y = 0, const float z = 0);
            virtual const ofVec3f& velScale();
            virtual void velScale(const float x = 0, const float y = 0, const float z = 0);
            //--------------------------------------
        
            //--------------------------------------
            //色
            virtual const float& red();
            virtual void red(const float value);
            virtual const float& green();
            virtual void green(const float value);
            virtual const float& blue();
            virtual void blue(const float value);
        
            virtual const float& velRed();
            virtual void velRed(const float value);
            virtual const float& velGreen();
            virtual void velGreen(const float value);
            virtual const float& velBlue();
            virtual void velBlue(const float value);
        
            virtual const ofFloatColor& color();
            virtual void color(const float r = 1.0, const float g = 1.0, const float b = 1.0);
            virtual void color(const ofFloatColor& value);
            virtual const ofFloatColor& startColor();
            virtual void startColor(const float r = 1.0, const float g = 1.0, const float b = 1.0);
            virtual void startColor(const ofFloatColor& value);
            virtual const ofFloatColor& velColor();
            virtual void velColor(const float r = 1.0, const float g = 1.0, const float b = 1.0);
            virtual void velColor(const ofFloatColor& value);
            //--------------------------------------
        
            virtual void update();
            virtual void draw();
            
            virtual void clear();
            virtual void reset();
        
        protected:
            
        private:
        
    };
}

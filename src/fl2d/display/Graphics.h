/**
 
 ActionScript3.0 Reference
 flash.display.Graphics
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Graphics.html
 
 */

#pragma once

#include "ofMain.h"

#include "../core/Object.h"
#include "../geom/Rectangle.h"
#include "../geom/Matrix.h"

#define FL_COMMAND_BEGIN_FILL            0
#define FL_COMMAND_BEGIN_GRADIENT_FILL   1
#define FL_COMMAND_END_FILL              2
#define FL_COMMAND_DRAW_CIRCLE           3
#define FL_COMMAND_DRAW_ELLIPSE          4
#define FL_COMMAND_DRAW_RECT             5
#define FL_COMMAND_DRAW_ROUNDRECT        6
#define FL_COMMAND_LINESTYLE             7
#define FL_COMMAND_LINE_TO               8
#define FL_COMMAND_MOVE_TO               9
#define FL_COMMAND_CURVE_TO             10
#define FL_COMMAND_CLEAR                11

namespace fl2d {
    
    class TextField;
    class Shape;
    class Sprite;
    
    class Graphics : public Object {
        friend TextField;
        friend Shape;
        friend Sprite;
        public:
            
        protected:
            
        private:
            typedef struct Property {
                float x; float y;
                float width; float height;
                float radius;
                int color; float alpha;
            } Property;
            
            typedef struct DrawCommand {
                int type;
                float thickness;
                float x; float y;
                float width; float height;
                float radius;
                int color; float alpha;
                float left, right, top, bottom;
                int index;
            } DrawCommand;
            
            vector<DrawCommand*> _commandList;
                
            //線の色
            ofColor _lineColor;
            //塗りの色
            ofColor _fillColor;
            //線の太さ
            float _thickness;
        
            bool _lineEnabled;
            bool _fillEnabled;
            
            float _moveToX;
            float _moveToY;
            bool _IsMoveTo;
        
            bool _smoothing;
            
            //Sprite
            float __alpha;
            Rectangle* __rect;
        
        public:
            Graphics();
            ~Graphics();
            
            void lineStyle(float thickness, int color = 0, float alpha = 1.0);
            
            void beginFill(int color, float alpha = 1.0);
            void endFill();
            
            //void beginGradientFill(string type, vector<int> colors, vector<float> alphas, vector<float> ratios, Matrix matrix = NULL, string spreadMethod = "pad", string interpolationMethod = "rgb", float focalPointRatio = 0);
            //void curveTo(float controlX, float controlY, float anchorX, float anchorY);
            
            void drawCircle(float x, float y, float radius);
            void drawEllipse(float x, float y, float width, float height);
            void drawRect(float x, float y, float width, float height);
            void drawRoundRect(float x, float y, float width, float height, float radius);
            //void lineStyle(foat thickness, int color = 0, float alpha = 1.0, bool pixelHinting = false, string scaleMode = "normal", string caps = NULL, string joints = NULL, float miterLimit = 3);
            
            //void lineStyle(float thickness, int color = 0, float alpha = 1.0, bool pixelHinting = false, string scaleMode = "normal", string caps = NULL, string joints = NULL, float miterLimit = 3);
            
            void lineTo(float x, float y);
            void moveTo(float x, float y);
            
            void clear();
            
            void smoothing(bool value);
            bool smoothing();
            
        protected:
            
        private:
            //Sprite
            void __draw();
            
            void _beginFill(int color, float alpha = 1.0);
            void _endFill();
            
            //void beginGradientFill(string type, vector<int> colors, vector<float> alphas, vector<float> ratios, Matrix matrix = NULL, string spreadMethod = "pad", string interpolationMethod = "rgb", float focalPointRatio = 0);
            //void curveTo(float controlX, float controlY, float anchorX, float anchorY);
            
            void _drawCircle(float x, float y, float radius);
            void _drawEllipse(float x, float y, float width, float height);
            void _drawRect(float x, float y, float width, float height);
            void _drawRoundRect(float x, float y, float width, float height, float radius);
            
            void _lineStyle(float thickness, int color, float alpha);

        //    void lineStyle(foat thickness, int color = 0, float alpha = 1.0, bool pixelHinting = false, string scaleMode = "normal", string caps = NULL, string joints = NULL, float miterLimit = 3);
            
            //void lineStyle(float thickness, int color = 0, float alpha = 1.0, bool pixelHinting = false, string scaleMode = "normal", string caps = NULL, string joints = NULL, float miterLimit = 3);
            
            void _lineTo(float x, float y);
            void _moveTo(float x, float y);
            
            void _clear(int index);

//            float _left();
//            float _right();
//            float _top();
//            float _bottom();
//            float _width();
//            float _height();
    };
    
}

/**
 
 Original code is Gnash :: SWFMatrix
 http://www.gnu.org/software/gnash/
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlashLite/blob/master/src/geom/ofxFlashMatrix.h
 
 ActionScript3.0 Reference
 flash.geom.flMatrix
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/geom/flMatrix.html
 
 */

#pragma once

#include "ofMain.h"
//#include "ofMatrix4x4.h"

namespace fl2d {
    
    class flMatrix : public ofMatrix4x4 {
    public:
        
    protected:
        
    private:
        
    public:
        flMatrix();
        flMatrix(const float& a, const float& b, const float& c, const float& d, const float& tx, const float& ty);
        virtual ~flMatrix();
        
        void set(flMatrix& matrix);
        void set(const float& a, const float& b, const float& c, const float& d, const float& tx, const float& ty);
        
        float a() const;
        void a(const float& value);
        
        float b() const;
        void b(const float& value);
        
        float c() const;
        void c(const float& value);
        
        float d() const;
        void d(const float& value);
        
        float tx() const;
        void tx(const float& value);
        
        float ty() const;
        void ty(const float& value);
        
        bool isEqual(flMatrix& matrix);
        
        //===============================================
        static flMatrix interpolate(flMatrix& mat1, flMatrix& mat2, const float& p) {
            flMatrix mat;
            mat.a((mat2.a() - mat1.a()) * p + mat1.a());
            mat.b((mat2.b() - mat1.b()) * p + mat1.b());
            mat.c((mat2.c() - mat1.c()) * p + mat1.c());
            mat.d((mat2.d() - mat1.d()) * p + mat1.d());
            mat.tx((mat2.tx() - mat1.tx()) * p + mat1.tx());
            mat.ty((mat2.ty() - mat1.ty()) * p + mat1.ty());
            
            return mat;
        }
        
        void identity();
        void transformPoint(ofPoint& p) const;
        void concat(const flMatrix& m);
        flMatrix& invert();
        flMatrix& clone();
        
        //	void
        //	SWFMatrix::concatenate_translation(int xoffset, int yoffset)
        //	// Concatenate a translation onto the front of our
        //	// SWFMatrix.  When transforming points, the translation
        //	// happens first, then our original xform.
        //	{
        //		tx += Fixed16Mul(sx,  xoffset) + Fixed16Mul(shy, yoffset);
        //		ty += Fixed16Mul(shx, xoffset) + Fixed16Mul(sy, yoffset);
        //	}
        //
        //	void
        //	SWFMatrix::concatenate_scale(double xscale, double yscale)
        //	// Concatenate scales to our SWFMatrix. When transforming points, these
        //	// scales happen first, then our matirx.
        //	{
        //		sx  = Fixed16Mul(sx, DoubleToFixed16(xscale));
        //		shy = Fixed16Mul(shy,DoubleToFixed16(yscale));
        //		shx = Fixed16Mul(shx,DoubleToFixed16(xscale));
        //		sy  = Fixed16Mul(sy, DoubleToFixed16(yscale));
        //	}
        
        
        const float determinant();
        
        //=============================================== SETTERS.
        
        void setScaleRotation(float sx, float sy, float angle);
        
        const float scaleX();
        void scaleX(float value);
        
        const float scaleY();
        void scaleY(float value);
        
        void scale(float sx, float sy);
        
        const float rotation();
        void rotate(const float& angle);
        
    protected:
        
    private:
        
    };
}

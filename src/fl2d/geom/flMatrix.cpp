#include "flMatrix.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flMatrix::flMatrix() {
        set(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);		// identity.    
    }
    //--------------------------------------------------------------
    //
    flMatrix::flMatrix(const float& a, const float& b, const float& c, const float& d, const float& tx, const float& ty) {
        set(a, b, c, d, tx, ty);
    }
    
    //--------------------------------------------------------------
    //
    flMatrix::~flMatrix() {
        
    }
    
    //===============================================
    //
    //   http://help.adobe.com/en_US/FlashPlatform/reference/actionscript/3/flash/geom/flMatrix.html
    //
    //	[  a   c   tx  ]		flash matrix
    //	[  b   d   ty  ]
    //	[  0   0   1   ]
    //
    //
    //	[  a   b   0   0  ]		ofxSelflash 4x4 matrix.
    //	[  c   d   0   0  ]
    //	[  0   0   0   0  ]
    //	[  tx  ty  0   0  ]
    //
    //===============================================
    
    //	void flMatrix::set(const ofxMatrix4x4& mat) {
    //		ofxMatrix4x4::set(
    //			mat._mat[0][0], mat._mat[0][1], mat._mat[0][2], mat._mat[0][3],
    //			mat._mat[1][0], mat._mat[1][1], mat._mat[1][2], mat._mat[1][3],
    //			mat._mat[2][0], mat._mat[2][1], mat._mat[2][2], mat._mat[2][3],
    //			mat._mat[3][0], mat._mat[3][1], mat._mat[3][2], mat._mat[3][3]
    //		);
    //	}
    
    
    //--------------------------------------------------------------
    //
    void flMatrix::set(flMatrix& matrix) {
        set(matrix.a(), matrix.b(), matrix.c(), matrix.d(), matrix.tx(), matrix.ty());
    }
    
    //--------------------------------------------------------------
    //
    void flMatrix::set(const float& a, const float& b, const float& c, const float& d, const float& tx, const float& ty) {
        ofMatrix4x4::set(
                         a,  b,  0,  0,
                         c,  d,  0,  0,
                         0,  0,  1,  0,
                         tx, ty, 0,  1
                         );
    }
    
    
    //--------------------------------------------------------------
    //イメージを拡大 / 縮小または回転するときに x 軸方向のピクセルの配置に影響を与える値です。
    float flMatrix::a() const { return _mat[0][0]; }
    void flMatrix::a(const float& value) { _mat[0][0] = value; }
    
    //--------------------------------------------------------------
    //イメージを回転または傾斜させるときに y 軸方向のピクセルの配置に影響を与える値です。
    float flMatrix::b() const { return _mat[0][1]; }
    void flMatrix::b(const float& value) { _mat[0][1] = value; }
    
    //--------------------------------------------------------------
    //イメージを回転または傾斜させるときに x 軸方向のピクセルの配置に影響を与える値です。
    float flMatrix::c() const { return _mat[1][0]; }
    void flMatrix::c(const float& value) { _mat[1][0] = value; }
    
    //--------------------------------------------------------------
    //イメージを拡大 / 縮小または回転するときに y 軸方向のピクセルの配置に影響を与える値です。
    float flMatrix::d() const { return _mat[1][1]; }
    void flMatrix::d(const float& value) { _mat[1][1] = value; }
    
    //--------------------------------------------------------------
    //x 軸方向に各ポイントを平行移動する距離です。
    float flMatrix::tx() const { return _mat[3][0]; }
    void flMatrix::tx(const float& value) { _mat[3][0] = value; }
    
    //--------------------------------------------------------------
    //y 軸方向に各ポイントを平行移動する距離です。
    float flMatrix::ty() const { return _mat[3][1]; }
    void flMatrix::ty(const float& value) { _mat[3][1] = value; }
    
    
    //--------------------------------------------------------------
    //
    bool flMatrix::isEqual(flMatrix& matrix) {
        if(a() != matrix.a()) return false;
        if(b() != matrix.b()) return false;
        if(c() != matrix.c()) return false;
        if(d() != matrix.d()) return false;
        if(tx()!= matrix.tx()) return false;
        if(ty()!= matrix.ty()) return false;
        
        return true;
    }
    
    //--------------------------------------------------------------
    //flMatrix オブジェクトで表現される図形変換を、指定されたポイントに適用した結果を返します。
    void flMatrix::transformPoint(ofPoint& p) const {
        float sx;		// 'a'  in AS flMatrix.
        float shx;		// 'b'  in AS flMatrix.
        float shy;		// 'c'  in AS flMatrix.
        float sy;		// 'd'  in AS flMatrix.
        float tx;		// 'tx' in AS flMatrix.
        float ty;		// 'ty' in AS flMatrix.
        
        sx	= _mat[0][0];
        shx	= _mat[0][1];
        shy	= _mat[1][0];
        sy	= _mat[1][1];
        tx	= _mat[3][0];
        ty	= _mat[3][1];
        
        float t0 = (sx  * p.x) + (shy * p.y) + tx;
        float t1 = (shx * p.x) + (sy  * p.y) + ty;
        
        p.x = t0;
        p.y = t1;
    }
    
    //--------------------------------------------------------------
    //マトリックスを現在のマトリックスと連結して、2 つのマトリックスの図形効果を効果的に組み合わせます。
    void flMatrix::concat(const flMatrix& m) {
        float a;
        float b;
        float c;
        float d;
        float tx;
        float ty;
        
        a	= (this->a() * m.a()) + (this->c() * m.b());
        b	= (this->b() * m.a()) + (this->d() * m.b());
        c	= (this->a() * m.c()) + (this->c() * m.d());
        d	= (this->b() * m.c()) + (this->d() * m.d());
        tx	= (this->a() * m.tx()) + (this->c() * m.ty()) + this->tx();
        ty	= (this->b() * m.tx()) + (this->d() * m.ty()) + this->ty();
        
        set(a, b, c, d, tx, ty);
    }
    
    //--------------------------------------------------------------
    //元のマトリックスの逆の変換を実行します。
    flMatrix& flMatrix::invert() {
        float det = determinant();
        
        if(det == 0) {
            set(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);	// set identity.
            return *this;
        }
        
        const float td = 1.0 / det;
        const float t0 = d() * td;
        
        d( a() * td);
        c(-c() * td);
        b(-b() * td);
        
        float t4 = -((tx() * t0) + (ty() * c()));
        ty(-((tx() * b()) + (ty() * d())));
        
        a(t0);
        tx(t4);
        
        return *this;
    }
    
    //--------------------------------------------------------------
    //
    flMatrix& flMatrix::clone() {
        flMatrix* m = new flMatrix();
        return *m;
    }
    
    //--------------------------------------------------------------
    //
    const float flMatrix::determinant() {
        return a() * d() - b() * c();
    }
    
    //--------------------------------------------------------------
    //各行列プロパティを null 変換になる値に設定します。
    void flMatrix::identity() {
        set(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }
    
    //--------------------------------------------------------------
    //
    void flMatrix::setScaleRotation(float sx, float sy, float angle) {
        if(sx == 0) sx = 0.00001;
        if(sy == 0) sy = 0.00001;
        
        const float cos_angle = cos(angle);
        const float sin_angle = sin(angle);
        
        a(sx *  cos_angle);
        b(sx *  sin_angle);
        c(sy * -sin_angle);
        d(sy *  cos_angle);
    }
    
    //--------------------------------------------------------------
    //
    const float flMatrix::scaleX() {
        float a_ = a();
        float b_ = b();
        float s = sqrt((a_ * a_ + b_ * b_)) / 1.0;
        
        return s;
    }
    //--------------------------------------------------------------
    //
    void flMatrix::scaleX(float value) {
        if(value == 0) value = 0.00001;
        
        const double rot_x = atan2(b(), a());
        a(value * cos(rot_x));
        b(value * sin(rot_x));
    }
    
    
    //--------------------------------------------------------------
    //
    const float flMatrix::scaleY() {
        float c_ = c();
        float d_ = d();
        float s = sqrt((d_ * d_ + c_ * c_)) / 1.0;
        
        return s;
    }
    //--------------------------------------------------------------
    //
    void flMatrix::scaleY(float value) {
        if(value == 0) value = 0.00001;
        
        const float rot_y = atan2(-c(), d());
        c(value * sin(rot_y));
        d(value * cos(rot_y));
    }
    
    //--------------------------------------------------------------
    //
    void flMatrix::scale(float sx, float sy) {
        if(sx == 0) sx = 0.00001;
        if(sy == 0) sy = 0.00001;
        
        setScaleRotation(sx, sy, rotation());
    }
    
    //--------------------------------------------------------------
    //
    const float flMatrix::rotation() {
        float a_ = a();
        float b_ = b();
        float r = atan2(b_, a_);
        
        return r;
    }
    //--------------------------------------------------------------
    // TODO flMatrix オブジェクトに回転変換を適用します。
    void flMatrix::rotate(const float& angle) {
        const float rot_x	= atan2(b(), a());
        const float rot_y	= atan2(-c(), d());
        const float scale_x	= scaleX();
        const float scale_y	= scaleY();
        
        a(scale_x * cos(angle));
        b(scale_x * sin(angle));
        c(scale_y * sin(rot_y - rot_x + angle) * -1);		// reverse sign.
        d(scale_y * cos(rot_y - rot_x + angle));
    }
    
    //=============================================== GETTERS.
    
    
    
    
}

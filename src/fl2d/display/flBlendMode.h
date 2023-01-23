/**
 
 Original code is Akira-Hayasaka :: ofxPSBlend
 https://github.com/Akira-Hayasaka/ofxPSBlend
 
 ActionScript3.0 Reference
 flash.display.BlendMode
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/BlendMode.html
 
 */

#pragma once

#include "ofMain.h"

namespace fl2d {
    
    class flBlendMode {
    public:
        //表示オブジェクトの要素カラーの値を背景色に加算し、その際に上限 0xFF を適用します。
        static string ADD;
        //表示オブジェクトの各ピクセルのアルファ値を背景に適用します。
        static string ALPHA;
        //
        static string ALPHA_TEST;
        //表示オブジェクトの要素カラーと背景色のうち暗い方（値が小さい方）の色を選択します。
        static string DARKEN;
        //表示オブジェクトの要素カラーと背景色を比較し、2 つの要素カラーのうち明るい方の値から暗い方の値を差し引きます。
        static string DIFFERENCE_;
        //表示オブジェクトのアルファ値に基づいて背景を消去します。
        static string ERASE;
        //表示オブジェクトの暗さに基づいて、各ピクセルの色を調整します。
        static string HARDLIGHT;
        //背景を反転します。
        static string INVERT;
        //表示オブジェクトに関する透明度グループを強制的に作成します。
        static string LAYER;
        //表示オブジェクトの要素カラーと背景色のうち明るい方（値が大きい方）の色を選択します。
        static string LIGHTEN;
        //表示オブジェクトの要素カラーの値と背景色の要素カラーの値を乗算した後、0xFF で割って正規化し、色を暗くします。
        static string MULTIPLY;
        //表示オブジェクトは、背景の前に表示されます。
        static string NORMAL;
        //背景の暗さに基づいて、各ピクセルの色を調整します。
        static string OVERLAY;
        //表示オブジェクトの色の補数（逆）と背景色の補数を乗算して、ブリーチ効果を得ます。
        static string SCREEN;
        //シェーダーを使用して、オブジェクト間のブレンドを定義します。
        static string SHADER;
        //結果の下限を 0 として、表示オブジェクトの要素カラーの値をその背景色の値から減算します。
        static string SUBTRACT;
        
    protected:
        
    private:
        static ofFbo* _base;
        static ofShader* _blendShader;
        static int _width;
        static int _height;
        
    public:
        static void enable(string value);
        static void disable();
        
        static void setup(int width, int height);
        static void draw(ofTexture& blendTgt, int blendMode = 0, int x = 0, int y = 0);
        static void draw(ofTexture& blendTgt, int blendMode, int x, int y, int width, int height);
        
        static void resize(int width, int height);
        
        static void begin();
        static void end();
        
        static string blendMode(int blendMode);
        
        static void destroy();
        
    protected:
        
    private:
        static void _loadShader();
        
        //            static string _getFragmentProgramGL3();
        //            static string _getFragmentProgramGL2();
        
    };
    
}

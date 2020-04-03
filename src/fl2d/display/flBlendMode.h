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
        //�\���I�u�W�F�N�g�̗v�f�J���[�̒l��w�i�F�ɉ��Z���A���̍ۂɏ�� 0xFF ��K�p���܂��B
        static string ADD;
        //�\���I�u�W�F�N�g�̊e�s�N�Z���̃A���t�@�l��w�i�ɓK�p���܂��B
        static string ALPHA;
        //
        static string ALPHA_TEST;
        //�\���I�u�W�F�N�g�̗v�f�J���[�Ɣw�i�F�̂����Â����i�l�����������j�̐F��I�����܂��B
        static string DARKEN;
        //�\���I�u�W�F�N�g�̗v�f�J���[�Ɣw�i�F���r���A2 �̗v�f�J���[�̂������邢���̒l����Â����̒l�����������܂��B
        static string DIFFERENCE_;
        //�\���I�u�W�F�N�g�̃A���t�@�l�Ɋ�Â��Ĕw�i���������܂��B
        static string ERASE;
        //�\���I�u�W�F�N�g�̈Â��Ɋ�Â��āA�e�s�N�Z���̐F�𒲐����܂��B
        static string HARDLIGHT;
        //�w�i�𔽓]���܂��B
        static string INVERT;
        //�\���I�u�W�F�N�g�Ɋւ��铧���x�O���[�v�������I�ɍ쐬���܂��B
        static string LAYER;
        //�\���I�u�W�F�N�g�̗v�f�J���[�Ɣw�i�F�̂������邢���i�l���傫�����j�̐F��I�����܂��B
        static string LIGHTEN;
        //�\���I�u�W�F�N�g�̗v�f�J���[�̒l�Ɣw�i�F�̗v�f�J���[�̒l����Z������A0xFF �Ŋ����Đ��K�����A�F���Â����܂��B
        static string MULTIPLY;
        //�\���I�u�W�F�N�g�́A�w�i�̑O�ɕ\������܂��B
        static string NORMAL;
        //�w�i�̈Â��Ɋ�Â��āA�e�s�N�Z���̐F�𒲐����܂��B
        static string OVERLAY;
        //�\���I�u�W�F�N�g�̐F�̕␔�i�t�j�Ɣw�i�F�̕␔����Z���āA�u���[�`���ʂ𓾂܂��B
        static string SCREEN;
        //�V�F�[�_�[���g�p���āA�I�u�W�F�N�g�Ԃ̃u�����h���`���܂��B
        static string SHADER;
        //���ʂ̉����� 0 �Ƃ��āA�\���I�u�W�F�N�g�̗v�f�J���[�̒l�����̔w�i�F�̒l���猸�Z���܂��B
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

#pragma once

#include "ofMain.h"
#include "Flash2D.h"
#include "Flash3D.h"

using namespace fl2d;
using namespace fl3d;

#include "GLSLAssister.h"
//#include "BokehDOF.h"

class World3D : public Sprite {
    public:
        
    protected:
        
    private:
        //--------------------------------------
        //[3D]
        //シーン3D
        Scene3D* _scene;
        //レンダラー
        RenderEngine* _renderer;
        //カメラ
        CameraObject3D* _camera;
        //ルートノード
        DisplayObjectContainer3D* _rootNode;
    
        //ライト
        GLLight* _glLight;
        //--------------------------------------
    
        //--------------------------------------
        Plane3D* _plane_fill;
        Plane3D* _plane_nonLighting;
        Plane3D* _plane_vertexColor;
        Plane3D* _plane_vertexColor2;
        Plane3D* _plane_wireFrame;
        Plane3D* _plane_normalTexture;
        Plane3D* _plane_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Cube3D* _cube_fill;
        Cube3D* _cube_nonLighting;
        Cube3D* _cube_vertexColor;
        Cube3D* _cube_vertexColor2;
        Cube3D* _cube_wireFrame;
        Cube3D* _cube_normalTexture;
        Cube3D* _cube_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Sphere3D* _low_sphere_fill;
        Sphere3D* _low_sphere_nonLighting;
        Sphere3D* _low_sphere_vertexColor;
        Sphere3D* _low_sphere_vertexColor2;
        Sphere3D* _low_sphere_wireFrame;
        Sphere3D* _low_sphere_normalTexture;
        Sphere3D* _low_sphere_transparentTexture;
        //--------------------------------------

        //--------------------------------------
        IcoSphere3D* _low_icoSphere_fill;
        IcoSphere3D* _low_icoSphere_nonLighting;
        IcoSphere3D* _low_icoSphere_vertexColor;
        IcoSphere3D* _low_icoSphere_vertexColor2;
        IcoSphere3D* _low_icoSphere_wireFrame;
        IcoSphere3D* _low_icoSphere_normalTexture;
        IcoSphere3D* _low_icoSphere_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Sphere3D* _high_sphere_fill;
        Sphere3D* _high_sphere_nonLighting;
        Sphere3D* _high_sphere_vertexColor;
        Sphere3D* _high_sphere_vertexColor2;
        Sphere3D* _high_sphere_wireFrame;
        Sphere3D* _high_sphere_normalTexture;
        Sphere3D* _high_sphere_transparentTexture;
        //--------------------------------------
        
        //--------------------------------------
        IcoSphere3D* _high_icoSphere_fill;
        IcoSphere3D* _high_icoSphere_nonLighting;
        IcoSphere3D* _high_icoSphere_vertexColor;
        IcoSphere3D* _high_icoSphere_vertexColor2;
        IcoSphere3D* _high_icoSphere_wireFrame;
        IcoSphere3D* _high_icoSphere_normalTexture;
        IcoSphere3D* _high_icoSphere_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Cylinder3D* _cylinder_fill;
        Cylinder3D* _cylinder_nonLighting;
        Cylinder3D* _cylinder_vertexColor;
        Cylinder3D* _cylinder_vertexColor2;
        Cylinder3D* _cylinder_wireFrame;
        Cylinder3D* _cylinder_normalTexture;
        Cylinder3D* _cylinder_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Cone3D* _cone_fill;
        Cone3D* _cone_nonLighting;
        Cone3D* _cone_vertexColor;
        Cone3D* _cone_vertexColor2;
        Cone3D* _cone_wireFrame;
        Cone3D* _cone_normalTexture;
        Cone3D* _cone_transparentTexture;
        //--------------------------------------
    
        //--------------------------------------
        Particles3D* _particles;
        Particles3D* _particles_nonLighting;
        //--------------------------------------
    
        GLSLAssister* _glslAssister;
        //BokehDOF* _bokehDof;
//
//        //--------------------------------------
//        float _bufferWidth;
//        float _bufferHeight;
//        
//        ofFbo* _renderedBuffer;
//        ofFbo* _depthMapBuffer;
//        
//        ofShader* _depthShader;
//        ofFbo* _depthBuffer;
//        //--------------------------------------
    
    public:
        World3D();
        ~World3D();
        
        virtual void setup();
        //virtual void update();
        //virtual void draw();
    
        CameraObject3D* camera();
        //BokehDOF* bokehDOF();
    
    protected:
        //virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _setupPlanes();
        void _setupCubes();
        void _setupLowSpheres();
        void _setupLowIcoSpheres();
        void _setupHighSpheres();
        void _setupHighIcoSpheres();
        void _setupCylinders();
        void _setupCones();
        void _setupParticles();
    
};

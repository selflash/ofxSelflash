#pragma once

#include "ofMain.h"
#include "Flash2D.h"
#include "Flash3D.h"
using namespace fl3d;

#include "BasicController.h"

class Camera3DController : public BasicController {
    public:
        
    protected:
        std::string _status;
    
        CameraObject3D* _camera;
    
    private:
        float _fov;
        float _nearClip;
        float _farClip;
        float _focalNear;
        float _focalFar;
    
    public:
        Camera3DController();
        ~Camera3DController();
    
        //virtual void setup();
        //virtual void update();
        //virtual void draw();    
    
        CameraObject3D* camera();
        void camera(CameraObject3D* value);
    
        //--------------------------------------
        const float fov();
        void fov(const float& value);
        
        const float nearClip();
        void nearClip(const float& value);
        
        const float farClip();
        void farClip(const float& value);
        
        const float focalNear();
        void focalNear(const float& value);
        
        const float focalFar();
        void focalFar(const float& value);    
        //--------------------------------------
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
        virtual void _uiEventHandler(Event& event);
    
    private:
};

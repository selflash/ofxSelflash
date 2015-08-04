#include "World3D.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
World3D::World3D() {
    cout << "[World3D]World3D()" << endl;
    
    _target = this;
    name("World3D");
    
    mouseEnabled(false);
    mouseChildren(false);
    
    //------------------------------------------
    _scene = NULL;
    _renderer = NULL;
    _camera = NULL;
    _rootNode = NULL;
    //------------------------------------------
}

//--------------------------------------------------------------
//
World3D::~World3D() {
    cout << "[World3D]~World3D()" << endl;
    
    _target = NULL;
    
    //------------------------------------------
    _scene = NULL;
    _renderer = NULL;
    _camera = NULL;
    _rootNode = NULL;
    //------------------------------------------
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void World3D::setup() {
    cout << "[World3D]setup()" << endl;
    
    //----------------------------------
    //シーン3D
    _scene = new Scene3D();
    _scene->name("SCENE 3D");
    _scene->stage((Stage*)stage());
//    _scene->backgroundColor(backgroundColor);
//    _scene->backgroundColor(ofFloatColor(0, 0, 0));
    
    //レンダラー
    _renderer = new RenderEngine();
    _renderer->name("FORWARD RENDER ENGINE");
    _renderer->setup(_scene, RENDER_MODE_FORWARD);
    //----------------------------------
    
    //----------------------------------
    //ライト
//    //ダイナミックライト
//    DynamicLight* dynamicLight;
//    //ライト1
//    dynamicLight = new DynamicLight();
//    dynamicLight->name("LIGHT 1 (D)");
//    dynamicLight->lightType(LIGHT_TYPE_DIRECTIONAL);
//    dynamicLight->x(0);
//    dynamicLight->y(1500);
//    dynamicLight->z(0);
//    dynamicLight->rotationX(-90);
////    dynamicLight->ambientColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
//    dynamicLight->diffuseColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
////    dynamicLight->attenuation(170);
////    dynamicLight->intensity(0.15);
////    dynamicLight->enabled(true);
//    _scene->addLight(dynamicLight);
    cout << float(100.0 / 255.0) << endl;
    //ダイナミックライト
    //ライト1
    _glLight = new GLLight();
    _glLight->name("GLLIGHT 1 (D)");
    _glLight->lightType(LIGHT_TYPE_POINT);
    _glLight->x(0);
    _glLight->y(0);
    _glLight->z(-500);
    _glLight->visible(true);
    _glLight->enabled(true);
//    glLight->rotationX(-90);
    _glLight->ambientColor(ofFloatColor(0.0, 0.0, 0.0, 1.0));
    _glLight->diffuseColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    _glLight->specularColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
//    _glLight->ambientColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
//    _glLight->diffuseColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
//    _glLight->emissiveColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
//    _glLight->specularColor(ofFloatColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0));
    _scene->addChild(_glLight);
    _scene->addLight(_glLight);
    //----------------------------------
    
    //----------------------------------
    DisplayObject3D* _eye;
    _eye = new DisplayObject3D();
    _eye->x(0);
    _eye->y(0);
    _eye->z(0);
    //カメラ
    //メインカメラ
    _camera = new CameraObject3D();
    _camera->name("MAIN CAMERA");
    _camera->keyboardMode(true);
    _camera->useMouse(true);
//    _camera->nearClip(1.0);
//    _camera->farClip(20000.0);
    
    _camera->nearClip(20);
    _camera->farClip(10000000);
//    _camera->farClip(100000);
//    _camera->focalNear(38.5615);
//    _camera->focalFar(100.0);
    _camera->focalNear(0.1);
    _camera->focalFar(1.0);
    _camera->x(3000);
    _camera->y(-3600);
    _camera->z(7000);
//    _camera->z(450);
//    camera->rotationX(0);
//    camera->rotationY(0);
//    camera->rotationZ(0);
//    _camera->lookAtTarget(*_eye);
//    camera->fov(20);
    _scene->addChild(_camera);
    _scene->camera(_camera);
//    camera->perspective(false, 60.0, 0.1, 100.0);
//    _cameraList.push_back(camera);
    //----------------------------------
    
    //----------------------------------
    //ルートノード
    _rootNode = new DisplayObjectContainer3D();
    _rootNode->name("ROOT NODE");
    _scene->addChild(_rootNode);
    //----------------------------------
    
    _setupPlanes();
    _setupCubes();
    _setupLowSpheres();
    _setupLowIcoSpheres();
    _setupHighSpheres();
    _setupHighIcoSpheres();
    _setupCylinders();
    _setupCones();
    _setupParticles();
}

//--------------------------------------------------------------
//
void World3D::_update() {
//    cout << "[World3D]update()" << endl;
    
//    cout << _camera->x() << ", " << _camera->y() << ", " << _camera->z() << endl;
    
    float elapsedTime = ofGetElapsedTimef();
    
    _glLight->position(ofGetMouseX()*10- ofGetWidth()*10 * 0.5, -ofGetMouseY()*10+ ofGetHeight()*10 * 0.5, 500);
    
    if(true) {
        //--------------------------------------
        _plane_fill->rotationX((sin(elapsedTime) * 230));
        _plane_fill->rotationY((sin(elapsedTime * 0.6) * 360));
        _plane_nonLighting->rotationX((sin(elapsedTime) * 230));
        _plane_nonLighting->rotationY((sin(elapsedTime * 0.6) * 360));
        _plane_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _plane_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _plane_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _plane_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _plane_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _plane_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _plane_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _plane_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _plane_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _plane_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _cube_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cube_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cube_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _low_sphere_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_sphere_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_sphere_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _low_icoSphere_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _low_icoSphere_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _low_icoSphere_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _high_sphere_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_sphere_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_sphere_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _high_icoSphere_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _high_icoSphere_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _high_icoSphere_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _cylinder_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cylinder_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cylinder_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
        
        //--------------------------------------
        _cone_fill->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_fill->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_nonLighting->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_nonLighting->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_vertexColor->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_vertexColor->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_vertexColor2->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_vertexColor2->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_wireFrame->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_wireFrame->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_normalTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_normalTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        _cone_transparentTexture->rotationX((sin(ofGetElapsedTimef()) * 230));
        _cone_transparentTexture->rotationY((sin(ofGetElapsedTimef() * 0.6) * 360));
        //--------------------------------------
    }
    
    //--------------------------------------
    _renderer->update();
    //--------------------------------------
    
    
    
    
    
    
//    //--------------------------------------
//    _renderedBuffer->begin();
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    _renderer->renderScene();
//    
//    _renderedBuffer->end();
//    //--------------------------------------
//    
//    //--------------------------------------
//    _depthMapBuffer->begin();
//	ofClear(0,0,0,0);
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    _renderer->renderScene();
//    
//    _depthMapBuffer->end();
//    //--------------------------------------
//
//    //--------------------------------------
//    _depthBuffer->begin();
//    
//    glClearColor(0.0, 0.0, 0.0, 0.0);
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    _depthShader->begin();
////    _depthShader->setUniformTexture("u_depth", _renderedBuffer->getDepthTexture(), 0);
////    _depthShader->setUniformTexture("u_depthMap", _depthMapBuffer->getTextureReference(), 1);
////    _depthShader->setUniform1f("u_cameraNearClip", _camera->nearClip());
////    _depthShader->setUniform1f("u_cameraFarClip", _camera->farClip());
////    _depthShader->setUniform1f("u_focalNear", _camera->focalNear());
////    _depthShader->setUniform1f("u_focalLength", _camera->focalLength());
//    _depthShader->setUniformTexture("u_depthTexture", _renderedBuffer->getDepthTexture(), 0);
//    _depthShader->setUniform1f("u_focalDistance", _camera->focalDistance());
//    _depthShader->setUniform1f("u_focalRange", _camera->focalLength());
//    
//    Flash3D::drawQuad();
//    
//    _depthShader->end();
//    
//    _depthBuffer->end();
//    //--------------------------------------
}

//--------------------------------------------------------------
//
void World3D::_draw() {
//    cout << "[World3D]setup()" << endl;
    
    //--------------------------------------
//    _glslAssister->begin();
//    _renderer->renderScene();
//    _glslAssister->end();
    //--------------------------------------
    
    //--------------------------------------
//    _bokehDof->begin();

    _renderer->renderScene();
    
//    _bokehDof->end();
//    _bokehDof->draw(0, 0);
    //--------------------------------------
    
//    glslAssister.end();
//    _renderedBuffer->draw(0, 0);
//    _depthMapBuffer->draw(0, 0);
//    _depthBuffer->draw(0, 0);
    
//    _depthMapBuffer->getDepthTexture().draw(0, 0);
}

//==============================================================
// PUBLI METHOD
//==============================================================

//--------------------------------------------------------------
//
CameraObject3D* World3D::camera() { return _camera; }

//--------------------------------------------------------------
//
//BokehDOF* World3D::bokehDOF() { return _bokehDof; }

//==============================================================
// PROTECTED / PRIVATE METHOD
//==============================================================

//--------------------------------------------------------------
//
void World3D::_setupPlanes() {
    //----------------------------------
    //プレーン(塗り)
    _plane_fill = new Plane3D();
    _plane_fill->name("PLANE [FILL]");
    _plane_fill->frontFaceEnabled(true);
    _plane_fill->backFaceEnabled(true);
    //法線と軸を表示
    _plane_fill->debugEnabled(true);
    _rootNode->addChild(_plane_fill);
    //----------------------------------
    
    //----------------------------------
    //プレーン(ライティングなし)
    _plane_nonLighting = new Plane3D();
    _plane_nonLighting->name("PLANE [NON LIGHTING]");
    _plane_nonLighting->x(1000);
    _plane_nonLighting->frontFaceEnabled(true);
    _plane_nonLighting->backFaceEnabled(true);
    _plane_nonLighting->lightEnabled(false);
    _rootNode->addChild(_plane_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //プレーン(頂点色)
    _plane_vertexColor = new Plane3D();
    _plane_vertexColor->name("PLANE [VERTEX COLOR]");
    _plane_vertexColor->x(2000);
    _plane_vertexColor->frontFaceEnabled(true);
    _plane_vertexColor->backFaceEnabled(true);
    _plane_vertexColor->vertexColor(ofRandomf(), ofRandomf(), ofRandomf());
    _rootNode->addChild(_plane_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //プレーン(頂点色)
    _plane_vertexColor2 = new Plane3D();
    _plane_vertexColor2->name("PLANE [VERTEX COLOR]");
    _plane_vertexColor2->x(3000);
    _plane_vertexColor2->frontFaceEnabled(true);
    _plane_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _plane_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _plane_vertexColor2->vertexColor(ofRandomf(), ofRandomf(), ofRandomf(), 1.0, i);
    }
    _rootNode->addChild(_plane_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //プレーン(ワイヤーフレーム)
    _plane_wireFrame = new Plane3D();
    _plane_wireFrame->name("PLANE [WIREFRAME]");
    _plane_wireFrame->x(4000);
    _plane_wireFrame->wireframeEnabled(true);
    _plane_wireFrame->frontFaceEnabled(true);
    _plane_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_plane_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //プレーン(テクスチャ)
    _plane_normalTexture = new Plane3D();
    _plane_normalTexture->name("PLANE [TEXTUER]");
    _plane_normalTexture->x(5000);
    _plane_normalTexture->frontFaceEnabled(true);
    _plane_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_plane_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _plane_normalTexture->diffuseTexture(diffuseTexture);
    _plane_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    //----------------------------------
    //プレーン(アルファ付きテクスチャ)
    _plane_transparentTexture = new Plane3D();
    _plane_transparentTexture->name("PLANE [TRANSPARENT TEXTUER]");
    _plane_transparentTexture->x(6000);
    _plane_transparentTexture->frontFaceEnabled(true);
    _plane_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_plane_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _plane_transparentTexture->diffuseTexture(diffuseTexture);
    _plane_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupCubes() {
    //----------------------------------
    //キューブ(塗り)
    _cube_fill = new Cube3D();
    _cube_fill->name("CUBE [FILL]");
    _cube_fill->y(-1000);
    //法線と軸を表示
    _cube_fill->debugEnabled(true);
    _cube_fill->frontFaceEnabled(true);
    _cube_fill->backFaceEnabled(true);
    _cube_fill->diffuseColor(1.0, 0.0, 0.0, 0.0);
//    _cube_fill->emissiveColor(ofRandom(0.0, 1.0), ofRandom(0.0, 1.0), ofRandom(0.0, 1.0), 1.0);
    _rootNode->addChild(_cube_fill);
    //----------------------------------
    
    //----------------------------------
    //キューブ(ライティングなし)
    _cube_nonLighting = new Cube3D();
    _cube_nonLighting->name("CUBE [NON LIGHTING]");
    _cube_nonLighting->x(1000);
    _cube_nonLighting->y(-1000);
    _cube_nonLighting->frontFaceEnabled(true);
    _cube_nonLighting->backFaceEnabled(true);
    _cube_nonLighting->lightEnabled(false);
    _cube_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cube_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //キューブ(頂点色)
    _cube_vertexColor = new Cube3D();
    _cube_vertexColor->name("CUBE [VERTEX COLOR]");
    _cube_vertexColor->x(2000);
    _cube_vertexColor->y(-1000);
    _cube_vertexColor->frontFaceEnabled(true);
    _cube_vertexColor->backFaceEnabled(true);
    _cube_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cube_vertexColor);
    //----------------------------------

    //----------------------------------
    //キューブ(頂点色)
    _cube_vertexColor2 = new Cube3D();
    _cube_vertexColor2->name("CUBE [VERTEX COLOR]");
    _cube_vertexColor2->x(3000);
    _cube_vertexColor2->y(-1000);
    _cube_vertexColor2->frontFaceEnabled(true);
    _cube_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _cube_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _cube_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_cube_vertexColor2);
    //----------------------------------

    //----------------------------------
    //キューブ(ワイヤーフレーム)
    _cube_wireFrame = new Cube3D();
    _cube_wireFrame->name("CUBE [WIREFRAME]");
    _cube_wireFrame->x(4000);
    _cube_wireFrame->y(-1000);
    _cube_wireFrame->frontFaceEnabled(true);
    _cube_wireFrame->backFaceEnabled(true);
    _cube_wireFrame->wireframeEnabled(true);
//    _cube_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_cube_wireFrame);
    //----------------------------------
    

    ofTexture* diffuseTexture;
    //----------------------------------
    //キューブ(テクスチャ)
    _cube_normalTexture = new Cube3D();
    _cube_normalTexture->name("CUBE [TEXTUER]");
    _cube_normalTexture->x(5000);
    _cube_normalTexture->y(-1000);
    _cube_normalTexture->frontFaceEnabled(true);
    _cube_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_cube_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _cube_normalTexture->diffuseTexture(diffuseTexture);
    _cube_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    
    //----------------------------------
    //キューブ(アルファ付きテクスチャ)
    _cube_transparentTexture = new Cube3D();
    _cube_transparentTexture->name("CUBE [TRANSPARENT TEXTUER]");
    _cube_transparentTexture->x(6000);
    _cube_transparentTexture->y(-1000);
    _cube_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _cube_transparentTexture->frontFaceEnabled(true);
    _cube_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_cube_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _cube_transparentTexture->diffuseTexture(diffuseTexture);
    _cube_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupLowSpheres() {
    //----------------------------------
    //スフィア(塗り)
    _low_sphere_fill = new Sphere3D(200, 6);
    _low_sphere_fill->name("SPHERE [FILL]");
    _low_sphere_fill->y(-2000);
    //法線と軸を表示
    _low_sphere_fill->debugEnabled(true);
    _low_sphere_fill->frontFaceEnabled(true);
    _low_sphere_fill->backFaceEnabled(true);
    _rootNode->addChild(_low_sphere_fill);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ライティングなし)
    _low_sphere_nonLighting = new Sphere3D(200, 6);
    _low_sphere_nonLighting->name("SPHERE [NON LIGHTING]");
    _low_sphere_nonLighting->x(1000);
    _low_sphere_nonLighting->y(-2000);
    _low_sphere_nonLighting->frontFaceEnabled(true);
    _low_sphere_nonLighting->backFaceEnabled(true);
    _low_sphere_nonLighting->lightEnabled(false);
    _low_sphere_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_low_sphere_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _low_sphere_vertexColor = new Sphere3D(200, 6);
    _low_sphere_vertexColor->name("SPHERE [VERTEX COLOR]");
    _low_sphere_vertexColor->x(2000);
    _low_sphere_vertexColor->y(-2000);
    _low_sphere_vertexColor->frontFaceEnabled(true);
    _low_sphere_vertexColor->backFaceEnabled(true);
    _low_sphere_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_low_sphere_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _low_sphere_vertexColor2 = new Sphere3D(200, 6);
    _low_sphere_vertexColor2->name("SPHERE [VERTEX COLOR]");
    _low_sphere_vertexColor2->x(3000);
    _low_sphere_vertexColor2->y(-2000);
    _low_sphere_vertexColor2->frontFaceEnabled(true);
    _low_sphere_vertexColor2->backFaceEnabled(true);
    //頂点色
    int i; int l;
    l = _low_sphere_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _low_sphere_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_low_sphere_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ワイヤーフレーム)
    _low_sphere_wireFrame = new Sphere3D(200, 6);
    _low_sphere_wireFrame->name("SPHERE [WIREFRAME]");
    _low_sphere_wireFrame->x(4000);
    _low_sphere_wireFrame->y(-2000);
    _low_sphere_wireFrame->wireframeEnabled(true);
    _low_sphere_wireFrame->frontFaceEnabled(true);
    _low_sphere_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_low_sphere_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //スフィア(テクスチャ)
    _low_sphere_normalTexture = new Sphere3D(200, 6);
    _low_sphere_normalTexture->name("SPHERE [TEXTUER]");
    _low_sphere_normalTexture->x(5000);
    _low_sphere_normalTexture->y(-2000);
    _low_sphere_normalTexture->frontFaceEnabled(true);
    _low_sphere_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_low_sphere_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _low_sphere_normalTexture->diffuseTexture(diffuseTexture);
    _low_sphere_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    //----------------------------------
    //スフィア(アルファ付きテクスチャ)
    _low_sphere_transparentTexture = new Sphere3D(200, 6);
    _low_sphere_transparentTexture->name("SPHERE [TRANSPARENT TEXTUER]");
    _low_sphere_transparentTexture->x(6000);
    _low_sphere_transparentTexture->y(-2000);
    _low_sphere_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _low_sphere_transparentTexture->frontFaceEnabled(true);
    _low_sphere_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_low_sphere_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _low_sphere_transparentTexture->diffuseTexture(diffuseTexture);
    _low_sphere_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupLowIcoSpheres() {
    //----------------------------------
    //スフィア(塗り)
    _low_icoSphere_fill = new IcoSphere3D(200, 1);
    _low_icoSphere_fill->name("ICOSPHERE [FILL]");
    _low_icoSphere_fill->y(-3000);
    //法線と軸を表示
    _low_icoSphere_fill->debugEnabled(true);
    _low_icoSphere_fill->frontFaceEnabled(true);
    _low_icoSphere_fill->backFaceEnabled(true);
    _rootNode->addChild(_low_icoSphere_fill);
    //----------------------------------

    //----------------------------------
    //スフィア(ライティングなし)
    _low_icoSphere_nonLighting = new IcoSphere3D(200, 1);
    _low_icoSphere_nonLighting->name("ICOSPHERE [NON LIGHTING]");
    _low_icoSphere_nonLighting->x(1000);
    _low_icoSphere_nonLighting->y(-3000);
    _low_icoSphere_nonLighting->frontFaceEnabled(true);
    _low_icoSphere_nonLighting->backFaceEnabled(true);
    _low_icoSphere_nonLighting->lightEnabled(false);
    _low_icoSphere_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_low_icoSphere_nonLighting);
    //----------------------------------

    //----------------------------------
    //スフィア(頂点色)
    _low_icoSphere_vertexColor = new IcoSphere3D(200, 1);
    _low_icoSphere_vertexColor->name("ICOSPHERE [VERTEX COLOR]");
    _low_icoSphere_vertexColor->x(2000);
    _low_icoSphere_vertexColor->y(-3000);
    _low_icoSphere_vertexColor->frontFaceEnabled(true);
    _low_icoSphere_vertexColor->backFaceEnabled(true);
    _low_icoSphere_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_low_icoSphere_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _low_icoSphere_vertexColor2 = new IcoSphere3D(200, 1);
    _low_icoSphere_vertexColor2->name("ICOSPHERE [VERTEX COLOR]");
    _low_icoSphere_vertexColor2->x(3000);
    _low_icoSphere_vertexColor2->y(-3000);
    _low_icoSphere_vertexColor2->frontFaceEnabled(true);
    _low_icoSphere_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _low_icoSphere_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _low_icoSphere_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_low_icoSphere_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ワイヤーフレーム)
    _low_icoSphere_wireFrame = new IcoSphere3D(200, 1);
    _low_icoSphere_wireFrame->name("ICOSPHERE [WIREFRAME]");
    _low_icoSphere_wireFrame->x(4000);
    _low_icoSphere_wireFrame->y(-3000);
    _low_icoSphere_wireFrame->wireframeEnabled(true);
    _low_icoSphere_wireFrame->frontFaceEnabled(true);
    _low_icoSphere_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_low_icoSphere_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //スフィア(テクスチャ)
    _low_icoSphere_normalTexture = new IcoSphere3D(200, 1);
    _low_icoSphere_normalTexture->name("ICOSPHERE [TEXTUER]");
    _low_icoSphere_normalTexture->x(5000);
    _low_icoSphere_normalTexture->y(-3000);
    _low_icoSphere_normalTexture->frontFaceEnabled(true);
    _low_icoSphere_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_low_icoSphere_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _low_icoSphere_normalTexture->diffuseTexture(diffuseTexture);
    _low_icoSphere_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    
    //----------------------------------
    //スフィア(アルファ付きテクスチャ)
    _low_icoSphere_transparentTexture = new IcoSphere3D(200, 1);
    _low_icoSphere_transparentTexture->name("ICOSPHERE [TRANSPARENT TEXTUER]");
    _low_icoSphere_transparentTexture->x(6000);
    _low_icoSphere_transparentTexture->y(-3000);
    _low_icoSphere_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _low_icoSphere_transparentTexture->frontFaceEnabled(true);
    _low_icoSphere_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_low_icoSphere_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _low_icoSphere_transparentTexture->diffuseTexture(diffuseTexture);
    _low_icoSphere_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupHighSpheres() {
    //----------------------------------
    //スフィア(塗り)
    _high_sphere_fill = new Sphere3D();
    _high_sphere_fill->name("SPHERE [FILL]");
    _high_sphere_fill->y(-4000);
    //法線と軸を表示
    _high_sphere_fill->debugEnabled(true);
    _high_sphere_fill->frontFaceEnabled(true);
    _high_sphere_fill->backFaceEnabled(true);
    _rootNode->addChild(_high_sphere_fill);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ライティングなし)
    _high_sphere_nonLighting = new Sphere3D();
    _high_sphere_nonLighting->name("SPHERE [NON LIGHITNG]");
    _high_sphere_nonLighting->x(1000);
    _high_sphere_nonLighting->y(-4000);
    _high_sphere_nonLighting->frontFaceEnabled(true);
    _high_sphere_nonLighting->backFaceEnabled(true);
    _high_sphere_nonLighting->lightEnabled(false);
    _high_sphere_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_high_sphere_nonLighting);
    //----------------------------------

    //----------------------------------
    //スフィア(頂点色)
    _high_sphere_vertexColor = new Sphere3D();
    _high_sphere_vertexColor->name("SPHERE [VERTEX COLOR]");
    _high_sphere_vertexColor->x(2000);
    _high_sphere_vertexColor->y(-4000);
    _high_sphere_vertexColor->frontFaceEnabled(true);
    _high_sphere_vertexColor->backFaceEnabled(true);
    _high_sphere_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_high_sphere_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _high_sphere_vertexColor2 = new Sphere3D();
    _high_sphere_vertexColor2->name("SPHERE [VERTEX COLOR]");
    _high_sphere_vertexColor2->x(3000);
    _high_sphere_vertexColor2->y(-4000);
    _high_sphere_vertexColor2->frontFaceEnabled(true);
    _high_sphere_vertexColor2->backFaceEnabled(true);
    //頂点色
    int i; int l;
    l = _high_sphere_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _high_sphere_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_high_sphere_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ワイヤーフレーム)
    _high_sphere_wireFrame = new Sphere3D();
    _high_sphere_wireFrame->name("SPHERE [WIREFRAME]");
    _high_sphere_wireFrame->x(4000);
    _high_sphere_wireFrame->y(-4000);
    _high_sphere_wireFrame->wireframeEnabled(true);
    _high_sphere_wireFrame->frontFaceEnabled(true);
    _high_sphere_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_high_sphere_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //スフィア(テクスチャ)
    _high_sphere_normalTexture = new Sphere3D();
    _high_sphere_normalTexture->name("SPHERE [TEXTUER]");
    _high_sphere_normalTexture->x(5000);
    _high_sphere_normalTexture->y(-4000);
    _high_sphere_normalTexture->frontFaceEnabled(true);
    _high_sphere_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_high_sphere_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _high_sphere_normalTexture->diffuseTexture(diffuseTexture);
    _high_sphere_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    //----------------------------------
    //スフィア(アルファ付きテクスチャ)
    _high_sphere_transparentTexture = new Sphere3D();
    _high_sphere_transparentTexture->name("SPHERE [TRANSPARENT TEXTUER]");
    _high_sphere_transparentTexture->x(6000);
    _high_sphere_transparentTexture->y(-4000);
    _high_sphere_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _high_sphere_transparentTexture->frontFaceEnabled(true);
    _high_sphere_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_high_sphere_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _high_sphere_transparentTexture->diffuseTexture(diffuseTexture);
    _high_sphere_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupHighIcoSpheres() {
    //----------------------------------
    //スフィア(塗り)
    _high_icoSphere_fill = new IcoSphere3D(200, 4);
    _high_icoSphere_fill->name("ICOSPHERE [FILL]");
    _high_icoSphere_fill->y(-5000);
    //法線と軸を表示
    _high_icoSphere_fill->debugEnabled(true);
    _high_icoSphere_fill->frontFaceEnabled(true);
    _high_icoSphere_fill->backFaceEnabled(true);
    _rootNode->addChild(_high_icoSphere_fill);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ライティングなし)
    _high_icoSphere_nonLighting = new IcoSphere3D(200, 4);
    _high_icoSphere_nonLighting->name("ICOSPHERE [NON LIGHTING]");
    _high_icoSphere_nonLighting->x(1000);
    _high_icoSphere_nonLighting->y(-5000);
    _high_icoSphere_nonLighting->frontFaceEnabled(true);
    _high_icoSphere_nonLighting->backFaceEnabled(true);
    _high_icoSphere_nonLighting->lightEnabled(false);
    _high_icoSphere_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_high_icoSphere_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _high_icoSphere_vertexColor = new IcoSphere3D(200, 4);
    _high_icoSphere_vertexColor->name("ICOSPHERE [VERTEX COLOR]");
    _high_icoSphere_vertexColor->x(2000);
    _high_icoSphere_vertexColor->y(-5000);
    _high_icoSphere_vertexColor->frontFaceEnabled(true);
    _high_icoSphere_vertexColor->backFaceEnabled(true);
    _high_icoSphere_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_high_icoSphere_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //スフィア(頂点色)
    _high_icoSphere_vertexColor2 = new IcoSphere3D(200, 4);
    _high_icoSphere_vertexColor2->name("ICOSPHERE [VERTEX COLOR]");
    _high_icoSphere_vertexColor2->x(3000);
    _high_icoSphere_vertexColor2->y(-5000);
    _high_icoSphere_vertexColor2->frontFaceEnabled(true);
    _high_icoSphere_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _high_icoSphere_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _high_icoSphere_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_high_icoSphere_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //スフィア(ワイヤーフレーム)
    _high_icoSphere_wireFrame = new IcoSphere3D(200, 4);
    _high_icoSphere_wireFrame->name("ICOSPHERE [WIREFRAME]");
    _high_icoSphere_wireFrame->x(4000);
    _high_icoSphere_wireFrame->y(-5000);
    _high_icoSphere_wireFrame->wireframeEnabled(true);
    _high_icoSphere_wireFrame->frontFaceEnabled(true);
    _high_icoSphere_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_high_icoSphere_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //スフィア(テクスチャ)
    _high_icoSphere_normalTexture = new IcoSphere3D(200, 4);
    _high_icoSphere_normalTexture->name("ICOSPHERE [TEXTUER]");
    _high_icoSphere_normalTexture->x(5000);
    _high_icoSphere_normalTexture->y(-5000);
    _high_icoSphere_normalTexture->frontFaceEnabled(true);
    _high_icoSphere_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_high_icoSphere_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _high_icoSphere_normalTexture->diffuseTexture(diffuseTexture);
    _high_icoSphere_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    
    //----------------------------------
    //スフィア(アルファ付きテクスチャ)
    _high_icoSphere_transparentTexture = new IcoSphere3D(200, 4);
    _high_icoSphere_transparentTexture->name("ICOSPHERE [TRANSPARENT TEXTUER]");
    _high_icoSphere_transparentTexture->x(6000);
    _high_icoSphere_transparentTexture->y(-5000);
    _high_icoSphere_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _high_icoSphere_transparentTexture->frontFaceEnabled(true);
    _high_icoSphere_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_high_icoSphere_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _high_icoSphere_transparentTexture->diffuseTexture(diffuseTexture);
    _high_icoSphere_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupCylinders() {
    //----------------------------------
    //シリンダー(塗り)
    _cylinder_fill = new Cylinder3D();
    _cylinder_fill->name("CYLINDER [FILL]");
    _cylinder_fill->y(-6000);
    _cylinder_fill->frontFaceEnabled(true);
    _cylinder_fill->backFaceEnabled(true);
    //法線と軸を表示
    _cylinder_fill->debugEnabled(true);
    _rootNode->addChild(_cylinder_fill);
    //----------------------------------
    
    //----------------------------------
    //シリンダー(ライティングなし)
    _cylinder_nonLighting = new Cylinder3D();
    _cylinder_nonLighting->name("CYLINDER [NON LIGHTING]");
    _cylinder_nonLighting->x(1000);
    _cylinder_nonLighting->y(-6000);
    _cylinder_nonLighting->frontFaceEnabled(true);
    _cylinder_nonLighting->backFaceEnabled(true);
    _cylinder_nonLighting->lightEnabled(false);
    _cylinder_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cylinder_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //シリンダー(頂点色)
    _cylinder_vertexColor = new Cylinder3D();
    _cylinder_vertexColor->name("CYLINDER [VERTEX COLOR]");
    _cylinder_vertexColor->x(2000);
    _cylinder_vertexColor->y(-6000);
    _cylinder_vertexColor->frontFaceEnabled(true);
    _cylinder_vertexColor->backFaceEnabled(true);
    _cylinder_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cylinder_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //シリンダー(頂点色)
    _cylinder_vertexColor2 = new Cylinder3D();
    _cylinder_vertexColor2->name("CYLINDER [VERTEX COLOR]");
    _cylinder_vertexColor2->x(3000);
    _cylinder_vertexColor2->y(-6000);
    _cylinder_vertexColor2->frontFaceEnabled(true);
    _cylinder_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _cylinder_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _cylinder_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_cylinder_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //シリンダー(ワイヤーフレーム)
    _cylinder_wireFrame = new Cylinder3D();
    _cylinder_wireFrame->name("CYLINDER [WIREFRAME]");
    _cylinder_wireFrame->x(4000);
    _cylinder_wireFrame->y(-6000);
    _cylinder_wireFrame->wireframeEnabled(true);
    _cylinder_wireFrame->frontFaceEnabled(true);
    _cylinder_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_cylinder_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //シリンダー(テクスチャ)
    _cylinder_normalTexture = new Cylinder3D();
    _cylinder_normalTexture->name("CYLINDER [TEXTUER]");
    _cylinder_normalTexture->x(5000);
    _cylinder_normalTexture->y(-6000);
    _cylinder_normalTexture->frontFaceEnabled(true);
    _cylinder_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_cylinder_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _cylinder_normalTexture->diffuseTexture(diffuseTexture);
    _cylinder_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    //----------------------------------
    //シリンダー(アルファ付きテクスチャ)
    _cylinder_transparentTexture = new Cylinder3D();
    _cylinder_transparentTexture->name("CYLINDER [TRANSPARENT TEXTUER]");
    _cylinder_transparentTexture->x(6000);
    _cylinder_transparentTexture->y(-6000);
    _cylinder_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _cylinder_transparentTexture->frontFaceEnabled(true);
    _cylinder_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_cylinder_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _cylinder_transparentTexture->diffuseTexture(diffuseTexture);
    _cylinder_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupCones() {
    //----------------------------------
    //コーン(塗り)
    _cone_fill = new Cone3D();
    _cone_fill->name("CONE [FILL]");
    _cone_fill->y(-7000);
    _cone_fill->frontFaceEnabled(true);
    _cone_fill->backFaceEnabled(true);
    //法線と軸を表示
    _cone_fill->debugEnabled(true);
    _rootNode->addChild(_cone_fill);
    //----------------------------------
    
    //----------------------------------
    //コーン(ライティングなし)
    _cone_nonLighting = new Cone3D();
    _cone_nonLighting->name("CONE [NON LIGHTING]");
    _cone_nonLighting->x(1000);
    _cone_nonLighting->y(-7000);
    _cone_nonLighting->frontFaceEnabled(true);
    _cone_nonLighting->backFaceEnabled(true);
    _cone_nonLighting->lightEnabled(false);
    _cone_nonLighting->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cone_nonLighting);
    //----------------------------------
    
    //----------------------------------
    //コーン(頂点色)
    _cone_vertexColor = new Cone3D();
    _cone_vertexColor->name("CONE [VERTEX COLOR]");
    _cone_vertexColor->x(2000);
    _cone_vertexColor->y(-7000);
    _cone_vertexColor->frontFaceEnabled(true);
    _cone_vertexColor->backFaceEnabled(true);
    _cone_vertexColor->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _rootNode->addChild(_cone_vertexColor);
    //----------------------------------
    
    //----------------------------------
    //コーン(頂点色)
    _cone_vertexColor2 = new Cone3D();
    _cone_vertexColor2->name("CONE [VERTEX COLOR]");
    _cone_vertexColor2->x(3000);
    _cone_vertexColor2->y(-7000);
    _cone_vertexColor2->frontFaceEnabled(true);
    _cone_vertexColor2->backFaceEnabled(true);
    int i; int l;
    l = _cone_vertexColor2->numVertexColors();
    for(i = 0; i < l; i++)  {
        _cone_vertexColor2->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), 1.0, i);
    }
    _rootNode->addChild(_cone_vertexColor2);
    //----------------------------------
    
    //----------------------------------
    //コーン(ワイヤーフレーム)
    _cone_wireFrame = new Cone3D();
    _cone_wireFrame->name("CONE [WIREFRAME]");
    _cone_wireFrame->x(4000);
    _cone_wireFrame->y(-7000);
    _cone_wireFrame->wireframeEnabled(true);
    _cone_wireFrame->frontFaceEnabled(true);
    _cone_wireFrame->backFaceEnabled(true);
    _rootNode->addChild(_cone_wireFrame);
    //----------------------------------
    
    
    ofTexture* diffuseTexture;
    //----------------------------------
    //コーン(テクスチャ)
    _cone_normalTexture = new Cone3D();
    _cone_normalTexture->name("CONE [TEXTUER]");
    _cone_normalTexture->x(5000);
    _cone_normalTexture->y(-7000);
    _cone_normalTexture->frontFaceEnabled(true);
    _cone_normalTexture->backFaceEnabled(true);
    _rootNode->addChild(_cone_normalTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/diffuse_02.jpg");
    ofEnableArbTex();
    _cone_normalTexture->diffuseTexture(diffuseTexture);
    _cone_normalTexture->diffuseTextureEnabled(true);
    //----------------------------------
    //----------------------------------
    //コーン(アルファ付きテクスチャ)
    _cone_transparentTexture = new Cone3D();
    _cone_transparentTexture->name("CONE [TRANSPARENT TEXTUER]");
    _cone_transparentTexture->x(6000);
    _cone_transparentTexture->y(-7000);
    _cone_transparentTexture->blendMode(BlendMode::ALPHA_TEST);
    _cone_transparentTexture->frontFaceEnabled(true);
    _cone_transparentTexture->backFaceEnabled(true);
    _rootNode->addChild(_cone_transparentTexture);
    
    //テクスチャの張り付け
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _cone_transparentTexture->diffuseTexture(diffuseTexture);
    _cone_transparentTexture->diffuseTextureEnabled(true);
    //----------------------------------
}

//--------------------------------------------------------------
//
void World3D::_setupParticles() {
    ofTexture* diffuseTexture;
    
    //----------------------------------
    //パーティクル
    _particles = new Particles3D();
    _particles->name("PARTICLES");
    _particles->setup();
    _particles->x(0);
    _particles->y(-8000);
//    _particles->frontFaceEnabled(true);
//    _particles->backFaceEnabled(true);
//    _particles->debugEnabled(true);
//    _particles->lightEnabled(false);
    _particles->blendMode(BlendMode::ALPHA_TEST);
    
    ofDisableArbTex();
    diffuseTexture = new ofTexture();
    ofLoadImage(*diffuseTexture, "textures/1-10design.png");
    ofEnableArbTex();
    _particles->diffuseTexture(diffuseTexture);
    _particles->diffuseTextureEnabled(true);
    _rootNode->addChild(_particles);
    //----------------------------------
    
    //----------------------------------
    //パーティクル(ライティングなし)
    _particles_nonLighting = new Particles3D();
    _particles_nonLighting->name("PARTICLES [NON LIGHTING]");
    _particles_nonLighting->setup();
    _particles_nonLighting->x(1000);
    _particles_nonLighting->y(-8000);
//    _particles->frontFaceEnabled(true);
//    _particles->backFaceEnabled(true);
//    _particles->debugEnabled(true);
//    _particles_nonLighting->lightEnabled(false);
    _particles_nonLighting->blendMode(BlendMode::ALPHA_TEST);
    _particles_nonLighting->diffuseTexture(diffuseTexture);
    _particles_nonLighting->diffuseTextureEnabled(true);
    _rootNode->addChild(_particles_nonLighting);
    //----------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//==============================================================
// RESIZE
//==============================================================
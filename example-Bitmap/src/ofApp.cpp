#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Btimap");
    ofSetVerticalSync(true);
    //ofDisableAntiAliasing();
    
    ofxSelflash::setup();
    flStage* stage = ofxSelflash::stage();
    
    //--------------------------------------
    if(image1.load("selflash.jpeg")) cout << "loaded 1" << endl;

    //クラスで宣言されたofImageなので参照渡し可能
    bitmap1 = new flBitmap(&image1);
    bitmap1->x(20);
    bitmap1->y(20);
//    bitmap1->scaleY(1.5);
    stage->addChild(bitmap1);
    //--------------------------------------
    
    //--------------------------------------
    ofImage image2;
    if(image2.load("selflash.jpeg")) ofLog() << "loaded 2";
    
    //関数内で宣言されたofImageは関数を抜けるとメモリ解放されるので参照渡しはエラー
    //bitmap2 = new flBitmap(&image2); //Error
    //複製渡しなのでこれ以降にimage2を編集したとしても表示に影響されない
    bitmap2 = new flBitmap(image2);
    bitmap2->x(20 + 256 + 20);
    bitmap2->y(20);
//    bitmap2->scaleY(1.5);
    stage->addChild(bitmap2);
    //--------------------------------------
    
    //--------------------------------------
    if(ofLoadImage(texture3, "selflash.jpeg")) ofLog() << "loaded 3";

    //クラスで宣言されたofTextureなので参照渡し可能
    bitmap3 = new flBitmap(&texture3);
    bitmap3->x(20);
    bitmap3->y(20 + 256 + 20);
    stage->addChild(bitmap3);
    //--------------------------------------

    //--------------------------------------
    ofTexture texture4;
    if(ofLoadImage(texture4, "selflash.jpeg")) ofLog() << "loaded 4";
    
    //関数内で宣言されたofImageは関数を抜けるとメモリ解放されるので参照渡しはエラー
    //bitmap4 = new flBitmap(&texture4); //Error
    //複製渡しなのでこれ以降にimage2を編集したとしても表示に影響されない
    bitmap4 = new flBitmap(texture4);
    bitmap4->x(20 + 256 + 20);
    bitmap4->y(20 + 256 + 20);
    stage->addChild(bitmap4);
    //--------------------------------------
    
    //--------------------------------------
    flSprite* sprite = new flSprite();
    flGraphics* g = sprite->graphics();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 512 + 20, 256 + 10);
    g->endFill();
    sprite->x(20);
    sprite->y(20 + 256 + 20 + 256 + 20);
//    sprite->scaleY(1.5);
//    sprite->height(512);
    stage->addChild(sprite);

    ofLog() << "sprite->width = " << sprite->width();
    ofLog() << "sprite->height = " << sprite->height();
    ofLog() << "sprite->scaleX = " << sprite->scaleX();
    ofLog() << "sprite->scaleY = " << sprite->scaleY();

    ofTexture texture5;
    if(ofLoadImage(texture5, "selflash.jpeg")) ofLog() << "loaded 4";

    //関数内で宣言されたオブジェクトは関数を抜けるとメモリ解放されるので参照渡しはエラー
    //bitmap5 = new flBitmap(&texture4); //Error
    //複製渡しなのでこれ以降にtexture2を編集したとしても表示に影響されない
    bitmap5 = new flBitmap(texture5);
//    bitmap5->x(bitmap3->x());
//    bitmap5->y(bitmap3->height());
//    bitmap5->height(512);
//    bitmap5->width(512);
//    bitmap5->scaleY(2.0);
//    bitmap5->alpha(0.5);
    sprite->addChild(bitmap5);

    ofLog() << "sprite->width = " << sprite->width();
    ofLog() << "sprite->height = " << sprite->height();
    ofLog() << "bitmap5->width = " << bitmap5->width();
    ofLog() << "bitmap5->height = " << bitmap5->height();
    ofLog() << "bitmap5->scaleX = " << bitmap5->scaleX();
    ofLog() << "bitmap5->scaleY = " << bitmap5->scaleY();
    //--------------------------------------
    
    //--------------------------------------
    int camWidth = 320;
    int camHeight = 240;
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);
    videoTexture.allocate(camWidth, camHeight, GL_RGBA);
    
    bitmap6 = new flBitmap(videoTexture);
    bitmap6->x(20 + 256 + 20 + 256 + 20);
    bitmap6->y(20);
    bitmap6->alpha(0.5);
    bitmap6->scaleY(1.5);
//    bitmap6->height(512);
    stage->addChild(bitmap6);
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        ofPixels& pixels = vidGrabber.getPixels();
        videoTexture.loadData(pixels);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofxSelflash::draw();
    
//    image1.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == '1') {
        bitmap2->alpha(0.5);
        bitmap3->alpha(0.5);
        bitmap4->alpha(0.5);
    }
    if(key == '2') {
        bitmap2->alpha(1.0);
        bitmap3->alpha(1.0);
        bitmap4->alpha(1.0);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}

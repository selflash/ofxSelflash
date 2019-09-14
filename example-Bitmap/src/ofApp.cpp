#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Sprite");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::setup();
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    //--------------------------------------
    if(image1.load("selflash.jpeg")) cout << "loaded 1" << endl;
    
    //クラスで宣言されたオブジェクトなので参照渡し可能
    bitmap2 = new flBitmap(&image1);
    bitmap2->x(bitmap2->width() * 1);
    //    bitmap2->scaleY(1.5);
    stage->addChild(bitmap2);
    //--------------------------------------
    
    //--------------------------------------
    ofImage image2;
    if(image2.load("selflash.jpeg")) cout << "loaded 2" << endl;
    
    //関数内で宣言されたオブジェクトは関数を抜けるとメモリ解放されるので参照渡しはエラー
    //複製渡しなのでこれ以降にimage2を編集したとしても表示に影響されない
    bitmap3 = new flBitmap(image2);
    bitmap3->x(bitmap3->width() * 2);
    //    bitmap3->scaleY(1.5);
    stage->addChild(bitmap3);
    //--------------------------------------
    
    //--------------------------------------
    if(ofLoadImage(texture1, "selflash.jpeg")) cout << "loaded 3" << endl;
    
    //クラスで宣言されたオブジェクトなので参照渡し可能
    bitmap4 = new flBitmap(&texture1);
    bitmap4->x(bitmap2->x());
    bitmap4->y(bitmap2->height());
    stage->addChild(bitmap4);
    //--------------------------------------
    
    //--------------------------------------
    flSprite* sprite = new flSprite();
    flGraphics* g = sprite->graphics();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 512, 256);
    g->endFill();
    sprite->x(bitmap3->x());
    sprite->y(bitmap3->height());
    //    sprite->scaleY(1.5);
    //    sprite->height(512);
    stage->addChild(sprite);
    
    cout << sprite->width() << ", " << sprite->height() << endl;
    cout << sprite->scaleX() << ", " << sprite->scaleY() << endl;
    
    ofTexture texture2;
    if(ofLoadImage(texture2, "selflash.jpeg")) cout << "loaded 4" << endl;
    
    //関数内で宣言されたオブジェクトは関数を抜けるとメモリ解放されるので参照渡しはエラー
    //複製渡しなのでこれ以降にtexture2を編集したとしても表示に影響されない
    bitmap5 = new flBitmap(texture2);
    //    bitmap5->x(bitmap3->x());
    //    bitmap5->y(bitmap3->height());
    //    bitmap5->height(512);
    //    bitmap5->width(512);
    //    bitmap5->scaleY(2.0);
    //    bitmap5->alpha(0.5);
    sprite->addChild(bitmap5);
    //--------------------------------------
    
    cout << sprite->width() << ", " << sprite->height() << endl;
    cout << sprite->scaleX() << ", " << sprite->scaleY() << endl;
    
    cout << bitmap5->width() << ", " << bitmap5->height() << endl;
    cout << bitmap5->scaleX() << ", " << bitmap5->scaleY() << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    image1.draw(0, 0);
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

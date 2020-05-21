#include "AppModel.h"

//--------------------------------------------------------------
AppModel::AppModel() {
    _target = this;
    name("AppModel");
    
    status = APPSTATUS_NOT_LOADED;

//    isLoaded = false;
//    isProcessing = false;
//    isFinding = false;

//    viewMode = 0;
//    currentCameraPosition.set("front");
    
    int camWidth = 320 * 1;
    int camHeight = 240 * 2;

    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x000000, 0.5);
    g->drawRect(0, 0, camWidth, camHeight);
    g->lineStyle(1, 0xffffff);
    g->moveTo(-1, -1);
    g->lineTo(camWidth + 1, -1);
    g->lineTo(camWidth + 1, camHeight + 1);
    g->lineTo(-1, camHeight + 1);
    g->lineTo(-1, -1);
    g->endFill();
    
    toolTipEnabled(true);
    toolTipText(u8"各変数の値を表示するウィンドウです。");
}

//--------------------------------------------------------------
void AppModel::_setup() {
//    ofLog() << "[AppModel]setup()";

}

//--------------------------------------------------------------
void AppModel::_update() {
    
}

//--------------------------------------------------------------
void AppModel::_draw() {
    {
        //--------------------------------------
        string text = "";
        text += name() + "\n";
        text += "X = " + ofToString(x()) + "\n";
        text += "Y = " + ofToString(y()) + "\n";
        //    text += "width = " + ofToString(width()) + "\n";
        //    text += "height = " + ofToString(height()) + "\n";
        //    text += "scaleX = " + ofToString(scaleX()) + "\n";
        //    text += "scaleY = " + ofToString(scaleY()) + "\n";
        
        ofPushStyle();
        ofSetColor(255, 255, 255);
        flFont::drawString(text, 9, 10, 20);
        ofPopStyle();
        //--------------------------------------
    }
    
    {
        //--------------------------------------
        string text = "";
        text += "LineWidth = " + ofToString(lineWidth) + "\n";
        text += "Speed = " + ofToString(speed) + "\n";
        text += "Left = " + ofToString(left) + "\n";
        text += "Right = " + ofToString(right) + "\n";
        text += "TestVec2.x = " + ofToString(testVec2->x) + "\n";
        text += "TestVec2.y = " + ofToString(testVec2->y) + "\n";
        text += "TestVec3.x = " + ofToString(testVec3->x) + "\n";
        text += "TestVec3.y = " + ofToString(testVec3->y) + "\n";
        text += "TestVec3.z = " + ofToString(testVec3->z) + "\n";
        text += "TestFloat = " + ofToString(testFloat) + "\n";
        text += "TestVec2ForPad2d.x = " + ofToString(testVec2ForPad2d->x) + "\n";
        text += "TestVec2ForPad2d.y = " + ofToString(testVec2ForPad2d->y) + "\n";
        text += "TestInt = " + ofToString(testInt) + "\n";

        //    text += "width = " + ofToString(width()) + "\n";
        //    text += "height = " + ofToString(height()) + "\n";
        //    text += "scaleX = " + ofToString(scaleX()) + "\n";
        //    text += "scaleY = " + ofToString(scaleY()) + "\n";
        
        ofPushStyle();
        ofSetColor(255, 255, 255);
        flFont::drawString(text, 9, 10, 120);
        ofPopStyle();
        //--------------------------------------
    }
}

//--------------------------------------------------------------
//string AppModel::getStatusToString() {
//    if(status == APPSTATUS_NOT_LOADED) return "Finding Next a Scanned Model.";
//    if(status == APPSTATUS_LOADED) return "Scanned Model is Loaded.";
//    if(status == APPSTATUS_PROCESSING) return "Now Processing..";
//    if(status == APPSTATUS_FINDING) return "Now Processing...";
//}

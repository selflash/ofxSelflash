#include "FrameBorder3.h"

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void FrameBorder3::_setup() {
    _image.load("selflash.jpeg");

    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x888888, 0.8);
    g->drawRect(-10, -10, _image.getWidth() + 20, _image.getHeight() + 20);
    g->endFill();
}

//--------------------------------------------------------------
//
void FrameBorder3::_draw() {
    _image.draw(0, 0);
}

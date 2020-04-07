#include "FrameBorder2.h"

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
void FrameBorder2::_setup() {
    ofImage image;
    image.load("selflash.jpeg");
    
    flBitmap* bitmap = new flBitmap(image);
    addChild(bitmap);

    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x888888, 0.8);
    g->drawRect(-10, -10, width() + 20, height() + 20);
    g->endFill();
}

#include "ImageFrame1.h"

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void ImageFrame1::_update() {
    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x888888, 0.8);
    g->drawRect(-10, -10, width() + 20, height() + 20);
    g->endFill();
}

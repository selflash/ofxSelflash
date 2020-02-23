#include "flRangeSlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flRangeSlider::flRangeSlider(float trackWidth, float min, float max, float minValue, float maxValue) {
        //ofLog() << "[flRangeSlider]flRangeSlider()";
        
        //------------------------------------------
        _target = this;
        name("flRangeSlider");
        
        //------------------------------------------
        _min = min;
        _max = max;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }

        _minValue = minValue;
        _maxValue = maxValue;
        if(_roundEnabled) {
            _minValue = flmath::roundd(_minValue);
            _maxValue = flmath::roundd(_maxValue);
        }    
        //------------------------------------------
        
        //------------------------------------------
        _trackWidth = trackWidth;
//        if(_max > _min) {
//            _barWidth = (_value -_min) / (_range / _trackWidth);
//        } else {
//            _barWidth = (_min - _value) / (_range / _trackWidth);
//        }
//        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------

        _percent = (_max - _min) / _trackWidth;    
        
        flGraphics* g;
        
        //------------------------------------------
        track = new flSprite();
        track->name("flRangeSlider.track");
        track->x(0);
        track->y(0);
        track->mouseEnabled(false);
//        track->addEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
//        track->addEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
//        track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        addChild(track);
        //------------------------------------------

        //------------------------------------------
        bar = new flSprite();
        bar->name("flRangeSlider.bar");
        bar->useHandCursor(true);
        bar->addEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        bar->addEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        bar->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(bar);
        //------------------------------------------

        //------------------------------------------
        minThumb = new flSprite();
        minThumb->name("flRangeSlider.minThumb");
        g = minThumb->graphics();
        g->clear();
        g->beginFill(0xff0000);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        minThumb->y(0);
        minThumb->alpha(0);
        minThumb->useHandCursor(true);
        minThumb->addEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        minThumb->addEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        minThumb->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(minThumb);
        //------------------------------------------

        //------------------------------------------
        maxThumb = new flSprite();
        maxThumb->name("flRangeSlider.maxThumb");
        g = maxThumb->graphics();
        g->clear();
        g->beginFill(0x00ff00);
        g->drawRect(0, 0, _thumbWidth, _trackHeight - 1);
        g->endFill();
        maxThumb->x((_maxValue - _min) / _percent);
        maxThumb->y(0);
        maxThumb->alpha(0);
        maxThumb->useHandCursor(true);
        maxThumb->addEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->addEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        track->addChild(maxThumb);
        //------------------------------------------

        bar->x(minThumb->x() + _thumbWidth);

        //------------------------------------------
        _minValueText = new flTextField();
        _minValueText->name("flRangeSlider.minValueText");
        _minValueText->x(0);
        _minValueText->width(_trackWidth);
        _minValueText->autoSize(flTextFieldAutoSize::LEFT);
        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _minValueText->text(ofToString(_minValue));
        _minValueText->mouseEnabled(false);
        _minValueText->y(0);
        addChild(_minValueText);
        
        _maxValueText = new flTextField();
        _maxValueText->name("flRangeSlider.maxValueText");
        _maxValueText->x(0);
        _maxValueText->width(_trackWidth);
        _maxValueText->autoSize(flTextFieldAutoSize::RIGHT);
        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _maxValueText->text(ofToString(_maxValue));
        _maxValueText->mouseEnabled(false);
        _maxValueText->y(0);
        addChild(_maxValueText);
        //------------------------------------------
        
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);

        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flRangeSlider::~flRangeSlider() {
        //ofLog() << "[flRangeSlider]~flRangeSlider()";
        
        delete track;
        track = NULL;
        
        bar->removeEventListener(flMouseEvent::ROLL_OVER, this, &flRangeSlider::_mouseEventHandler);
        bar->removeEventListener(flMouseEvent::ROLL_OUT, this, &flRangeSlider::_mouseEventHandler);
        bar->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete bar;
        bar = NULL;
        
        minThumb->removeEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        minThumb->removeEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        minThumb->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete minThumb;
        minThumb = NULL;
        
        maxThumb->removeEventListener(flMouseEvent::MOUSE_OVER, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->removeEventListener(flMouseEvent::MOUSE_OUT, this, &flRangeSlider::_mouseEventHandler);
        maxThumb->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRangeSlider::_mouseEventHandler);
        delete maxThumb;
        maxThumb = NULL;
        
        delete _minValueText;
        _minValueText = NULL;
        
        delete _maxValueText;
        _maxValueText = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_setup() {
        //ofLog() << "[flRangeSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_update() {
        if(bar->isMouseDown()) {
            _barPress();
        }
        if(minThumb->isMouseDown()) {
            _minThumbPress();
        }
        if(maxThumb->isMouseDown()) {
            _maxThumbPress();
        }

        //        ofLog() << "[flRangeSlider]bar->width = " << bar->width();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if (_enabled) {
            _setNormalColor();
        } else {
            _setDisableNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    float flRangeSlider::min() { return _min; }
    void flRangeSlider::min(float value, bool dispatch) {
        _min = value;
        if(_roundEnabled) _min = flmath::roundd(_min);
        if(_max < _min) _max = _min;
        if(_maxValue < _min) _maxValue = _min;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    //--------------------------------------------------------------
    float flRangeSlider::max() { return _max; }
    void flRangeSlider::max(float value, bool dispatch) {
        _max = value;
        if(_roundEnabled) _max = flmath::roundd(_max);
        if(_min > _max) _min = _max;
        if(_minValue > _max) _minValue = _max;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        //サムの位置の更新
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    float flRangeSlider::minValue() { return _minValue; }
    void flRangeSlider::minValue(float value, bool dispatch) {
        _minValue = value;
        if(_minValue < _min) _min = _minValue;
        if(_roundEnabled) _minValue = flmath::roundd(_minValue);
        if(_minValue > _max) _max = _minValue;
        if(_minValue > _maxValue) _maxValue = _minValue;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        
        //------------------------------------------
        //サムの位置の更新
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        if(bar->isMouseDown() || minThumb->isMouseDown() || maxThumb->isMouseDown()) {
            _setActiveColor();
        } else if(bar->isMouseOver() || minThumb->isMouseOver() || maxThumb->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    float flRangeSlider::maxValue() { return _maxValue; }
    void flRangeSlider::maxValue(float value, bool dispatch) {
        _maxValue = value;
        if(_maxValue > _max) _max = _maxValue;
        if(_roundEnabled) _maxValue = flmath::roundd(_maxValue);
        if(_maxValue < _min) _min = _maxValue;
        if(_maxValue < _minValue) _minValue = _maxValue;
        
        //------------------------------------------
        //値の更新
        _percent = (_max - _min) / _trackWidth;
        //------------------------------------------
        
        //------------------------------------------
        //サムの位置の更新
        minThumb->x(((_minValue - _min) / _percent) - _thumbWidth);
        maxThumb->x((_maxValue - _min) / _percent);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _range = _maxValue - _minValue;
        _minValueText->text(ofToString(_minValue));
        _maxValueText->text(ofToString(_maxValue));
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        if(bar->isMouseDown() || minThumb->isMouseDown() || maxThumb->isMouseDown()) {
            _setActiveColor();
        } else if(bar->isMouseOver() || minThumb->isMouseOver() || maxThumb->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    float flRangeSlider::range() { return _range; }

    //--------------------------------------------------------------
    bool flRangeSlider::roundEnabled() { return _roundEnabled; }
    void flRangeSlider::roundEnabled(bool value) { _roundEnabled = value; }

    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_changeValue(bool dispatch) {
        _minValueText->text(ofToString(_minValue, _digit));
        _maxValueText->text(ofToString(_maxValue, _digit));

        //------------------------------------------
        //イベント
        if(dispatch) {
            flRangeSliderEvent* event = new flRangeSliderEvent(flRangeSliderEvent::CHANGE);
            event->__minValue = _minValue;
            event->__maxValue = _maxValue;
            event->__range = _range;
            dispatchEvent(event);

        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_over() {
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_barOut() {
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_thumbOut() {
        if(bar->isMouseOver()) return;
        if(bar->isMouseDown()) return;
        if(minThumb->isMouseDown()) return;
        if(maxThumb->isMouseDown()) return;

        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_barPress() {
        //------------------------------------------
        float temp1 = mouseX() - _draggablePoint.x;
        if(temp1 < 0) {
            temp1 = 0;
        } else if(temp1 > _trackWidth - _barWidth) {
            temp1 = _trackWidth - _barWidth;
        }
        float temp2 = temp1 + _barWidth;
        minThumb->x(temp1 - _thumbWidth);
        maxThumb->x(temp2);
        //------------------------------------------
        
        //------------------------------------------
        //値の更新
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
        if(_roundEnabled) {
            _minValue = flmath::roundd(_minValue);
            _maxValue = flmath::roundd(_maxValue);
        }
        _range = _maxValue - _minValue;
        //------------------------------------------

        //------------------------------------------
        //表示の更新
        bar->x(minThumb->x() + _thumbWidth);
        //------------------------------------------

        //------------------------------------------
        _setActiveColor();
        //------------------------------------------

        //------------------------------------------
        _changeValue(true);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_minThumbPress() {
//        ofLog() << "[flRangeSlider]_thumbPress()";

        float preValue = _minValue;

        //------------------------------------------
        //サムの位置の更新
        float temp = mouseX() - _draggablePoint.x;
        if(temp < 0) {
            temp = 0;
        } else if(temp > maxThumb->x() - 1) {
            temp = maxThumb->x() - 1;
        }
        //------------------------------------------

        //------------------------------------------
        minThumb->x(temp - _thumbWidth);
        //------------------------------------------
        
        //------------------------------------------
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
        if(_roundEnabled) {
            _minValue = flmath::roundd(_minValue);
            _maxValue = flmath::roundd(_maxValue);
        }
        _range = _maxValue - _minValue;
        //------------------------------------------

        //------------------------------------------
        bar->x(minThumb->x() + _thumbWidth);
        //------------------------------------------

        //------------------------------------------
        _setActiveColor();
        //------------------------------------------

        //------------------------------------------
        if(preValue != _minValue) _changeValue(true);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_maxThumbPress() {
//        ofLog() << "[flRangeSlider]_maxThumbPress()";

        float preValue = _maxValue;

        //------------------------------------------
        //サムの位置の更新
        float temp = mouseX() - _draggablePoint.x;
        if(temp < minThumb->x() + _thumbWidth + 1) {
            temp = minThumb->x() + _thumbWidth + 1;
        } else if(temp > _trackWidth) {
            temp = _trackWidth;
        }
        //------------------------------------------
        
        //------------------------------------------
        maxThumb->x(temp);
        //------------------------------------------
        
        //------------------------------------------
        _barWidth = maxThumb->x() - (minThumb->x() + _thumbWidth);
        _minValue = _min + ((minThumb->x() + _thumbWidth) * _percent);
        _maxValue = _min + (maxThumb->x() * _percent);
        if(_roundEnabled) {
            _minValue = flmath::roundd(_minValue);
            _maxValue = flmath::roundd(_maxValue);
        }
        _range = _maxValue - _minValue;
        //------------------------------------------
        
        //------------------------------------------
        _setActiveColor();
        //------------------------------------------
        
        //------------------------------------------
        if(preValue != _maxValue) _changeValue(true);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_release() {
//        ofLog() << "[flRangeSlider]_release()";
        if(
           bar->isMouseOver() ||
           minThumb->isMouseOver() ||
           maxThumb->isMouseOver()
           ) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setSelectedBarOverColor() {
        //        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setSelectedThumbOverColor() {
        //        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _minValueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _maxValueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_drawTrackGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), _trackAlpha);
        g->drawRect(0, 0, _trackWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRangeSlider::_drawBarGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        //            g->beginFill(0xff0000, _barAlpha);
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
//        g->drawRect(minThumb->x() + _thumbWidth, 0, _barWidth, _trackHeight);
        g->drawRect(0, 0, _barWidth, _trackHeight);
        g->endFill();
    }
    
//    //--------------------------------------------------------------
//    void flRangeSlider::_over() {
//        if(track->isMouseDown()) return;
//        if(bar->isMouseDown()) return;
//        if(minThumb->isMouseDown()) return;
//        if(maxThumb->isMouseDown()) return;
//
//        //------------------------------------------
//        _drawTrackGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//        _drawBarGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//        //------------------------------------------
//
//        //------------------------------------------
//        _minValueText->visible(true);
//        _maxValueText->visible(true);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_out() {
//        if(track->isMouseDown()) return;
//        if(bar->isMouseDown()) return;
//        if(minThumb->isMouseDown()) return;
//        if(maxThumb->isMouseDown()) return;
//
//        //------------------------------------------
//        _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//        //------------------------------------------
//
//        //------------------------------------------
//        _minValueText->visible(false);
//        _maxValueText->visible(false);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_press() {
//        //------------------------------------------
//        _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//        _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//        //------------------------------------------
//    }
//    //--------------------------------------------------------------
//    void flRangeSlider::_release() {
//        if(minThumb->isMouseOver() || track->isMouseOver()) {
//            //------------------------------------------
//            _drawTrackGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//            _drawBarGraphics(flDefinition::UI_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//            //------------------------------------------
//
//            //------------------------------------------
//            _minValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//            _maxValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//            //------------------------------------------
//        } else {
//            //------------------------------------------
//            _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_NORMAL_COLOR.getHex(), 1);
//            _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR.getHex(), 1);
//            //------------------------------------------
//
//            //------------------------------------------
//            _minValueText->visible(false);
//            _maxValueText->visible(false);
//            //------------------------------------------
//        }
//    }
    
    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flRangeSlider::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flRangeSlider]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flRangeSlider]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flRangeSlider]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flRangeSlider]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == bar) _over();
//            else if(event.target() == minThumb) _thumbOver();
//            else if(event.target() == maxThumb) _thumbOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == bar) _barOut();
//            else if(event.target() == minThumb) _thumbOut();
//            else if(event.target() == maxThumb) _thumbOut();
        }
        
        //Mouse Over
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == minThumb || event.target() == maxThumb) _over();
        }
        
        //Mouse Out
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == minThumb || event.target() == maxThumb) _thumbOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == bar) {
                _draggablePoint.x = mouseX() - (minThumb->x() + _thumbWidth);
                _barPress();
            }
            if(event.target() == minThumb) {
                _draggablePoint.x = mouseX() - (minThumb->x() + _thumbWidth);
//                _draggablePoint.x = mouseX() - thumb->x() - _thumbWidth * 0.5;
                _minThumbPress();
            }
            else if(event.target() == maxThumb) {
                _draggablePoint.x = mouseX() - maxThumb->x();
                _maxThumbPress();
            }

            if(stage()) {
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            }

            
//            if(event.target() == maxThumb) {
//                _draggablePoint.x = mouseX() - maxThumb->x();
//                _press();
//            }
//            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            
//            if(minThumb->isMouseOver() || maxThumb->isMouseOver()) {
//                if(event.target() == minThumb || event.target() == maxThumb) {
//                    _thumbDown();
//                    addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//                    if(stage()) {
//                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//                    }
//                }
//            } else {
////                if(event.target() == track) {
////                    _barDown();
////                    addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
////                    if(stage()) {
////                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
////                    }
////                }
//            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
            }
            _release();

//            if(event.currentTarget() == stage()) {
//                _draggablePoint.x = 0;
//                _draggablePoint.y = 0;
//
//                _release();
//                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRangeSlider::_mouseEventHandler);
//            }
        }
    }
    
}

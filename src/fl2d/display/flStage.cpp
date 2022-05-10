#include "flStage.h"

namespace fl2d {
    
    flStage* flStage::_instance = nullptr;
    
    //--------------------------------------------------------------
    flStage* flStage::instance() {
        if(!_instance) {
            _instance = new flStage();
//            _instance->setup();
        }
        return _instance;
    };
    void flStage::clear() {
        if(_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flStage::flStage() {
        if(debug()) ofLog() << "[flStage]flStage()";
        
        _typeID = FL_TYPE_STAGE;
        _target = this;
        name("flStage");
        
        this->_stage = this;
        
        //MainTimeline
        _root = new flMovieClip();
        _root->name("root1");
        //        this->addChild(_root);
        
        _stageWidth = ofGetWidth();
        _stageHeight = ofGetHeight();
        
        _isTouchMode = false;
        
        _mouseX = 0;
        _mouseY = 0;
        
        _mouseID = 0;
        
        _isMouseChanged = false;
        
        //        _isKeyDown = false;
        
        _focus = this;
        __isFocus = true;
        
        _topMostHitDisplayObject = nullptr;
        _topMostHitDisplayObjectPrev = nullptr;
        
        _topMostHitInteractiveObject = nullptr;
        _topMostHitInteractiveObjectPrev = nullptr;
        
        _currentMouseDownInteractiveObject = nullptr;
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    flStage::~flStage() {
        if(debug()) ofLog() << "[flStage]~flStage()";
        
        _target = nullptr;
        name("");
        
        this->_stage = this;
        
        //MainTimeline
        delete _root;
        _root = nullptr;
        
        _stageWidth = 0;
        _stageHeight = 0;
        
        _isTouchMode = false;
        
        _mouseX = 0;
        _mouseY = 0;
        
        _mouseID = 0;
        
        _isMouseChanged = false;
        
        //        _isKeyDown = false;
        
        _focus = nullptr;
        __isFocus = false;
        
        if(_topMostHitDisplayObject) _topMostHitDisplayObject->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _topMostHitDisplayObject = nullptr;

        if (_topMostHitDisplayObjectPrev) _topMostHitDisplayObjectPrev->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _topMostHitDisplayObjectPrev = nullptr;
        
        if (_topMostHitInteractiveObject) _topMostHitInteractiveObject->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _topMostHitInteractiveObject = nullptr;

        if (_topMostHitInteractiveObjectPrev) _topMostHitInteractiveObjectPrev->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _topMostHitInteractiveObjectPrev = nullptr;
        
        if (_currentMouseDownInteractiveObject) _currentMouseDownInteractiveObject->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _currentMouseDownInteractiveObject = nullptr;
        
        //_lineTopDown.clear();
        //_lineTopDownPrev.clear();
        _lineBottomUp.clear();
        _lineBottomUpPrev.clear();
        //------------------------------------
        
        //------------------------------------
        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
        ofRemoveListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mouseScrolled, this, &flStage::_mouseScrolledEventHandler, _settings.mousePriority);
        
        ofRemoveListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _settings.keyboardPriority);
        ofRemoveListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _settings.keyboardPriority);
        
        ofRemoveListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _settings.windowPriority);
        
        if(!_settings.manualUpdate) {
            ofRemoveListener(ofEvents().update, this, &flStage::_updateEventHandler, _settings.updatePriority);
        }
        if(!_settings.manualDraw) {
            ofRemoveListener(ofEvents().draw, this, &flStage::_drawEventHandler, _settings.drawPriority);
        }
        
//        _priority = OF_EVENT_ORDER_BEFORE_APP;
        //------------------------------------

        flBlendMode::destroy();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flStage::setup(flSettings settings) {
        if(debug()) ofLog() << "[flStage]setup()";
        
        if(_isSetuped) return;
        _isSetuped = true;
        
        _settings = settings;
        
        //------------------------------------
        //        _priority = OF_EVENT_ORDER_BEFORE_APP;
        //        _priority = OF_EVENT_ORDER_APP;
        //        _priority = OF_EVENT_ORDER_AFTER_APP;
        
        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
        ofAddListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mouseScrolled, this, &flStage::_mouseScrolledEventHandler, _settings.mousePriority);
        
        ofAddListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _settings.keyboardPriority);
        ofAddListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _settings.keyboardPriority);
        
        ofAddListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _settings.windowPriority);
        
        if(!_settings.manualUpdate) {
            ofAddListener(ofEvents().update, this, &flStage::_updateEventHandler, _settings.updatePriority);
        }
        if(!_settings.manualDraw) {
            ofAddListener(ofEvents().draw, this, &flStage::_drawEventHandler, _settings.drawPriority);
        }
        //------------------------------------
        
        flBlendMode::setup(_stageWidth, _stageHeight);
    }
    
    //--------------------------------------------------------------
    void flStage::update() {
        if(_isPaused) return;
        
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
        
        //------------------------------------
        if(_topMostHitInteractiveObject != nullptr) {
            if(flUtil::isSprite(_topMostHitInteractiveObject)) {
                flSprite* sprite = (flSprite*) _topMostHitInteractiveObject;
                //------------------------------------
                if(sprite->useHandCursor() == true) {
                    if(sprite->isMouseDown()) {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_CLOSE_HAND);
                    } else {
                        if(sprite->buttonMode() == true) {
                            flMouse::changeCursor(FLASH_MOUSE_TYPE_POINTING_HAND);
                        } else {
                            flMouse::changeCursor(FLASH_MOUSE_TYPE_OPEN_HAND);
                        }
                    }
                } else {
                    if(sprite->buttonMode() == true) {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_POINTING_HAND);
                    } else {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
                    }
                }
                //------------------------------------
            } else {
                flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
            }
        } else {
            flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
        }
        //------------------------------------
        
        //------------------------------------
        // Åá
        if(false) {
            if(_topMostHitDisplayObjectPrev != _topMostHitDisplayObject) {
                ofLog() << "\n==========================================================";
                ofLog() << "[Address]";
                ofLog() << "topMostHitDisplayObject         = " << _topMostHitDisplayObject;
                ofLog() << "topMostHitDisplayObjectPrev     = " << _topMostHitDisplayObjectPrev;
                ofLog() << "----------------------------------------------------------";
                ofLog() << "----------------------------------------------------------";
                ofLog() << "[Name]";
                if(_topMostHitDisplayObject) ofLog() << "topMostHitDisplayObject         = " << _topMostHitDisplayObject->name().c_str();
                if(_topMostHitDisplayObjectPrev) ofLog() << "topMostHitDisplayObjectPrev     = " << _topMostHitDisplayObjectPrev->name().c_str();
                ofLog() << "==========================================================\n";
            }
            ofLog() << "==========================================================\n";
            ofLog() << "focus                           = " << _focus;
            if(_focus) ofLog() << "focus                           = " << _focus->name().c_str();
            ofLog() << "==========================================================\n";
        }
        //------------------------------------
        
        __isMouseOver = bool(_topMostHitDisplayObject == nullptr);
        
        if(_topMostHitDisplayObjectPrev) _topMostHitDisplayObjectPrev->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
        _topMostHitDisplayObjectPrev = _topMostHitDisplayObject;
        _topMostHitDisplayObject = nullptr;
        
        _updateChildrenOne(this, _children);
        _updateMouse();
        _updateChildrenTwo(this, _children);
        
        __isMousePressed	= false;
        __isMouseReleased	= false;
        _isMouseChanged	= false;
        
        //------------------------------------
        //Å˜ÉŒÅÁÅèÅá
        float mouseXPrev = _mouseX;
        float mouseYPrev = _mouseY;
        _mouseX = ofGetMouseX();
        _mouseY = ofGetMouseY();
        //------------------------------------
        //------------------------------------
        //Å˜ÉŒÅıÅò
        if(_mouseX != mouseXPrev || _mouseY != mouseYPrev) _mouseMove();
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::draw() {
        if(!visible()) return;

        //ofLog() << "[flStage]draw();
        
        //    glEnable(GL_BLEND);
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        
        GLboolean preBlendmodeAlpha = glIsEnabled(OF_BLENDMODE_ALPHA);
        GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
        
        ofEnableAlphaBlending();
        glDisable(GL_DEPTH_TEST);
        
        flDisplayObjectContainer::draw();
        //_drawChildren(this, _children);
        
        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
        if(preBlendmodeAlpha == GL_TRUE) { ofEnableAlphaBlending(); } else { ofDisableAlphaBlending(); }
        
        //oFÅÁÅëÅLÅãÅNÅíÅáÉŒ
        //ofDisableAlphaBlending();
        //    glBlendFunc(GL_ONE, GL_ZERO);
        //    glDisable(GL_BLEND);
        
//        if(true) _debugDraw(this, _children);
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    int flStage::stageWidth() { return _stageWidth; }
    int flStage::stageHeight() { return _stageHeight; }
    
    //--------------------------------------------------------------
    int flStage::mouseX() { return _mouseX; }
    int flStage::mouseY() { return _mouseY; }
    
    //--------------------------------------------------------------
    //    bool flStage::isMouseDown() { return _bMouseDown; };
    
    //--------------------------------------------------------------
    flInteractiveObject* flStage::focus() { return _focus; }
    
    //--------------------------------------------------------------
    flDisplayObject* flStage::topMostHitDisplayObject() { return _topMostHitDisplayObject; }
    flDisplayObject* flStage::topMostHitDisplayObjectPrev() { return _topMostHitDisplayObjectPrev; }
    
    //--------------------------------------------------------------
    flInteractiveObject* flStage::topMostHitInteractiveObject() { return _topMostHitInteractiveObject; }
    flInteractiveObject* flStage::topMostHitInteractiveObjectPrev() { return _topMostHitInteractiveObjectPrev; }
    
    //--------------------------------------------------------------
    flDisplayObject* flStage::getMostHitDisplayObject(int x, int y) {
        ofLog() << "[flStage]getMostHitDisplayObject(" << x << ", " << y << ")";
        return _getMostHitDisplayObject(this, _children, x, y);
    }
    
//    //--------------------------------------------------------------
//    // TODO
//    void flStage::priority(ofEventOrder value) {
//        if(_priority == value) return;
//        _priority = value;
//
//        //        //------------------------------------
//        //        //ofRemoveListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler);
//        //        ofRemoveListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler);
//        //        ofRemoveListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler);
//        //        ofRemoveListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler);
//        //
//        //        ofRemoveListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler);
//        //        ofRemoveListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler);
//        //
//        //        ofRemoveListener(ofEvents().update, this, &flStage::_updateEventHandler);
//        //        ofRemoveListener(ofEvents().draw, this, &flStage::_drawEventHandler);
//        //        ofRemoveListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler);
//        //        //------------------------------------
//        //
//        //        //------------------------------------
//        //        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
//        //        ofAddListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _priority);
//        //        ofAddListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _priority);
//        //        ofAddListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _priority);
//        //
//        //        ofAddListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _priority);
//        //        ofAddListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _priority);
//        //
//        //        ofAddListener(ofEvents().update, this, &flStage::_updateEventHandler, _priority);
//        //        ofAddListener(ofEvents().draw, this, &flStage::_drawEventHandler, _priority);
//        //        ofAddListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _priority);
//        //        //------------------------------------
//    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flStage::_updateChildrenOne(flDisplayObject* parent, vector<flDisplayObject*>& _children) {
        //ofLog() << "[flStage]_updateChildrenOne()";
        
        // clear pixel bounds on every loop and recalculate.
        //parent->resetPixelBounds();
        
        for(int i = 0; i < _children.size(); i++) {
            flDisplayObject* child;
            child = _children[i];
            
            //------------------------------------
            //Dispatch enterframe event.
//            if(_isDisplayObject(child)) {
//                flEvent* event = new flEvent(flEvent::ENTER_FRAME);
//                child->dispatchEvent(event);
//            }
            //------------------------------------
            
            if(child->__maskOwner != nullptr) continue;
            if(!child->visible()) continue;
            
            //=========================================== Matrix.
            //transform child matrix by world matrix.
            flMatrix worldMatrix;
            worldMatrix = parent->transform().concatenatedMatrix();
            worldMatrix.concat(child->transform().matrix());
            child->__updateTransform(worldMatrix);
            
            // compound alpha adds up down the parent-child chain.
//            child->__compoundAlpha(parent->__compoundAlpha() * child->_alpha);
//            child->updateOnFrame();
            
            //------------------------------------ topMostHitDisplayObject

			bool isInEffectiveArea = true;

			if (isInEffectiveArea && child->mask() != nullptr) {
				isInEffectiveArea = child->mask()->hitTestPoint(_mouseX, _mouseY, true);
			}

			if (isInEffectiveArea) {
				//------------------------------------ mouseEnabled
				if (flUtil::isInteractiveObject(child)) {
					flInteractiveObject* intObj = (flInteractiveObject*)child;
					if (intObj->mouseEnabled()) {
						//------------------------------------ hitArea
						if (flUtil::isSprite(child)) {
							flSprite* sprite = (flSprite*)child;
							if (sprite->hitArea() == nullptr) {
								if (child->hitTestPoint(_mouseX, _mouseY, true)) {
									_topMostHitDisplayObject = child;
                                    _topMostHitDisplayObject->addEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
								}
							}
							else {

							}
						}
						else {
							if (child->hitTestPoint(_mouseX, _mouseY, true)) {
								_topMostHitDisplayObject = child;
                                _topMostHitDisplayObject->addEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
                            }
						}
						//------------------------------------ hitArea
					}
					else {
						//------------------------------------ hitArea
						if (flUtil::isSprite(child)) {
							flSprite* sprite = (flSprite*)child;
							if (sprite->__hitAreaObject) {
								if (child->hitTestPoint(_mouseX, _mouseY, true)) {
									_topMostHitDisplayObject = child;
                                    _topMostHitDisplayObject->addEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
                                }
							}
							else {

							}
						}
						else {

						}
						//------------------------------------ hitArea
					}
				}
				else {
					if (child->hitTestPoint(_mouseX, _mouseY, true)) {
						_topMostHitDisplayObject = child;
                        _topMostHitDisplayObject->addEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
                    }
				}
				//------------------------------------ mouseEnabled

				//------------------------------------ topMostHitDisplayObject

				//ÅáÅÁ
				if (_hasChildren(child)) {
					flDisplayObjectContainer* container = (flDisplayObjectContainer*)child;

					//------------------------------------ mouseChildren
					if (container->mouseChildren()) {
						if (container->numChildren() > 0) {
							_updateChildrenOne(child, container->children());
						}
					}
					//------------------------------------ mouseChildren
				}

				// compound pixel bounds from _children.
				//parent->addToPixelBounds(child->pixelBounds());
			}
        }
    }
    
    //--------------------------------------------------------------
    void flStage::_updateMouse() {
        //ofLog() << "[flStage]_updateMouse()";
        
        if(__isMouseDown) return;
        //ofLog() << "_isMouseChanged = " << _isMouseChanged;
        
        //ÅëÅ˜ÉŒÅ˜ÅòÅí
        bool bHitDisplayObjectChanged = false;
        bHitDisplayObjectChanged = (_topMostHitDisplayObject != _topMostHitDisplayObjectPrev);
        //ÅëÅ˜ÉŒÅ˜ÅòÅè,ÅÒÅãÅÒÅ›ÅÒÅèÅ˜ÅÒÉ∂
        //if(!bHitDisplayObjectChanged && !_bMousePressed && !_bMouseReleased && !_isMouseChanged) return;
        if(!bHitDisplayObjectChanged && !__isMousePressed && !__isMouseReleased) return;
        
        //------------------------------------
        if(false) {
            char frame[10];
            //sprintf(frame, "%05d", ofGetFrameNum());
            sprintf(frame, "%05llu", ofGetFrameNum());
            ofLog() << frame << " :: bHitDisplayObjectChanged = " << (bHitDisplayObjectChanged ? "true" : "false");
            ofLog() << frame << " :: bMousePressed = "	<< (__isMousePressed ? "true" : "false");
            ofLog() << frame << " :: bMouseReleased = " << (__isMouseReleased ? "true" : "false");
            ofLog() << frame << " :: bMouseChanged = " << (_isMouseChanged ? "true" : "false");
        }
        //------------------------------------
        
        //=========================================== CREATE CHILD / PARENT LINES.
        
        _topMostHitInteractiveObjectPrev = _topMostHitInteractiveObject;
        _topMostHitInteractiveObject = nullptr;
        
        flDisplayObject* dispObj = nullptr;
        flInteractiveObject* intObj = nullptr;
        
        flDisplayObject* hitDisplayObject = _topMostHitDisplayObject;
        
        //if(bHitDisplayObjectChanged) {
        //ÉŒÅ˜ÅÒÅ˜Åë
        //_lineTopDownPrev = _lineTopDown;
        _lineBottomUpPrev = _lineBottomUp;
        //_lineTopDown.clear();
        _lineBottomUp.clear();
        
        //Å˜ÉŒÅLÅëÅ˜Å˜ÉŒÅíÅ˜InteractiveObjectÉŒÅLÅı
        if(hitDisplayObject) {
            dispObj = hitDisplayObject;
            //ÉŒÅÒÅòÅL
            while(dispObj != this) {
                //------------------------------------ InteractiveObject
                //ÅòÅíÅ˜
                if(flUtil::isInteractiveObject(dispObj)) {
                    intObj = (flInteractiveObject*)dispObj;
                    
                    //------------------------------------ mouseEnabled
                    //[mouseEnabledÅLÅ˜]
                    if(intObj->mouseEnabled()) {
                        //Å˜ÉŒUPÅ›Åá
                        //                        intObj->__isMouseDown = _bMouseDown;
                        //                            intObj->__isMouseDown = false; // TODO ÅíÅ˜ÅÒ
                        intObj->__isMousePressed = false;
                        intObj->__isMouseReleased = false;
                        //ÉŒÅáÅLÅı
                        //_lineTopDown.push_back(intObj);
                        //ÉŒÅıÅÇÅLÅı
                        _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                        
                        //ÅLÅãÉ∂ÅíÅòÅí
                        if(!_topMostHitInteractiveObject) _topMostHitInteractiveObject = intObj;
                        
                        //------------------------------------ mouseChildren
                        //mouseChildrenfalseÅıÅí
                        if(flUtil::isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) {
                                _lineBottomUp.clear();
                                _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                                _topMostHitInteractiveObject = intObj;
                            }
                        }
                        //------------------------------------ mouseChildren
                    } else {
                        
                        //------------------------------------ hitArea
                        //[hitAreaÅLÅ˜]
                        /*
                         memo [AS3ÅLhitArea]
                         hitAreaÅÇSprietÅ˜ÉŒÅãÉŒÅL
                         addChildÅ˜
                         hitAreaÅLÅÇSpritemouseEnabledfalse
                         hitAreaÅLÅÇSpriteÅÒhitAreaÅLÅÒÅÁ
                         ÅíÅÒÅLaddChildSprite
                         hitAreaÅÇÅ˜SpriteÅÁÅLÅ˜ÉŒÅòÅÁÅL
                         */
                        if(flUtil::isSprite(intObj)) {
                            flSprite* sprite = (flSprite*) intObj;
                            if(sprite->__hitAreaObject) {
                                dispObj = sprite->__hitAreaObject;
                                //sprite->__hitAreaObject->dispatchEvent(mouseEvent);
                                //goto pushListEnd;
                                
                                intObj = (flInteractiveObject*)dispObj;
                                //Å˜ÉŒUPÅ›Åá
//                                intObj->__isMouseDown = _bMouseDown;
//                                intObj->__isMouseDown = false; // TODO ÅíÅ˜ÅÒ
//                                intObj->__isMouseDown = false;
                                intObj->__isMousePressed = false;
                                intObj->__isMouseReleased = false;
                                //ÉŒÅáÅLÅı
                                //_lineTopDown.push_back(intObj);
                                //ÉŒÅıÅÇÅLÅı
                                _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                                
                                //ÅLÅãÉ∂ÅíÅòÅí
                                if(!_topMostHitInteractiveObject) _topMostHitInteractiveObject = intObj;
                            } else {
                                
                            }
                        }
                        //------------------------------------ hitArea
                        
                        //------------------------------------ mouseChildren
                        //mouseChildrenfalseÅıÅí
                        if(flUtil::isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) {
                                _lineBottomUp.clear();
                            }
                        }
                        //------------------------------------ mouseChildren
                    }
                    //------------------------------------ mouseEnabled
                }
                //------------------------------------ InteractiveObject
                dispObj	= dispObj->parent();
            }
        }
        //}
        //pushListEnd:
        
        //------------------------------------
        if(false) {
            if(_topMostHitInteractiveObject || _topMostHitInteractiveObjectPrev)ofLog() << "\n==========================================================";
            if(_topMostHitInteractiveObject) ofLog() << "TopMostHitInteractiveObject     = " << _topMostHitInteractiveObject->name().c_str();
            if(_topMostHitInteractiveObjectPrev) ofLog() << "TopMostHitInteractiveObjectPrev = " << _topMostHitInteractiveObjectPrev->name().c_str();
            if(_topMostHitInteractiveObject || _topMostHitInteractiveObjectPrev)ofLog() <<         "==========================================================\n";
        }
        //------------------------------------
        
        //---------------------------------------------------------- MOUSE EVENTS
        
        //------------------------------------
        //ÅÇÅLÅëÅ˜Åò
        if(_topMostHitInteractiveObjectPrev) {
            if(_topMostHitInteractiveObjectPrev != _topMostHitInteractiveObject) {
                for(int i = 0; i < _lineBottomUpPrev.size(); i++) {
                    intObj = _lineBottomUpPrev[i];
                    bool check = false;
                    
                    //
                    for(int ii = 0; ii < _lineBottomUp.size(); ii++) {
                        check = bool(intObj == _lineBottomUp[ii]);
                        if(check) break;
                    }
                    
                    if(!check) {
                        //------------------------------------
                        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::ROLL_OUT);
                        mouseEvent->__target = intObj;
                        intObj->__isRollOver = false;
                        intObj->__isMouseOver = false;
                        intObj->dispatchEvent(mouseEvent);
                        //------------------------------------
                        
                        //mouseChildrenfalseÅıÅí
                        if(flUtil::isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) goto rollOutCheckEnd;
                        }
                    }
                }
            }
        }
    rollOutCheckEnd:
        
        //ÅÇÅLÅò
        if(_topMostHitInteractiveObject) {
            if(_topMostHitInteractiveObject != _topMostHitInteractiveObjectPrev) {
                for(int i = 0; i < _lineBottomUp.size(); i++) {
                    intObj = _lineBottomUp[i];
                    bool check = false;
                    
                    //
                    for(int ii = 0; ii < _lineBottomUpPrev.size(); ii++ ) {
                        check = bool(intObj == _lineBottomUpPrev[ii]);
                        if(check) break;
                    }
                    
                    if(!check) {
                        //------------------------------------
                        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::ROLL_OVER);
                        mouseEvent->__target = intObj;
                        intObj->__isRollOver = true;
                        intObj->__isMouseOver = true;
                        intObj->dispatchEvent(mouseEvent);
                        //------------------------------------
                        
                        //mouseChildrenfalseÅıÅí
                        if(flUtil::isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) goto rollOverCheckEnd;
                        }
                    }
                }
            }
        }
    rollOverCheckEnd:
        //------------------------------------
        
        //------------------------------------
        //Å˜ÉŒÅëÅ˜Åò
        if(_topMostHitInteractiveObjectPrev) {
            if(_topMostHitInteractiveObjectPrev != _topMostHitInteractiveObject) {
                for(int i = 0; i < _lineBottomUpPrev.size(); i++) {
                    //------------------------------------
                    flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_OUT);
                    mouseEvent->__target = _topMostHitInteractiveObjectPrev;
                    intObj = _lineBottomUpPrev[i];
                    intObj->__isMouseOver = false;
                    intObj->dispatchEvent(mouseEvent);
                    //------------------------------------
                    
                    //mouseChildrenfalseÅıÅí
                    if(flUtil::isDisplayObjectContainer(intObj)) {
                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                        if(!dispObjContainer->mouseChildren()) goto mouseOutCheckEnd;
                    }
                }
            }
        }
    mouseOutCheckEnd:
        
        //Å˜ÉŒÅò
        if(_topMostHitInteractiveObject) {
            if(_topMostHitInteractiveObject != _topMostHitInteractiveObjectPrev) {
                for(int i = 0; i < _lineBottomUp.size(); i++ ) {
                    //------------------------------------
                    flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_OVER);
                    mouseEvent->__target = _topMostHitInteractiveObject;
                    intObj = _lineBottomUp[i];
                    intObj->__isMouseOver = true;
                    intObj->dispatchEvent(mouseEvent);
                    //------------------------------------
                    
                    //mouseChildrenfalseÅıÅí
                    if(flUtil::isDisplayObjectContainer(intObj)) {
                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                        if(!dispObjContainer->mouseChildren()) goto mouseOverCheckEnd;
                    }
                }
            }
        }
    mouseOverCheckEnd:
        //------------------------------------
        
        //        //------------------------------------
        //        //Å˜ÉŒÅ˜Åò
        //        if(__isMousePressed) {
        //            ofLog() << "HOGE";
        //            if(_topMostHitInteractiveObject) {
        //                //------------------------------------
        //                //ÅLÉŒÅòÅí
        //                if(_focus != _topMostHitInteractiveObject) {
        //                    FocusEvent* focusEvent;
        //
        //                    // ÅÒÅòÅÁ
        //                    try {
        //                        //ÅLÉŒÅëÅ˜Åò
        //                        _focus->__isFocus = false;
        //                        focusEvent = new FocusEvent(FocusEvent::FOCUS_OUT);
        //                        focusEvent->__target = _focus;
        //                        _focus->dispatchEvent(focusEvent);
        //
        //                        // ÅÒÅòÉŒÅÇ
        //    //                    throw "ÅÒÅòÅÁ";
        //                    } catch(const char* str ) {
        //                        // ÅÒÅòÅÇÅí
        //                        ofLog() << str;
        //                    }
        //
        //                    //ÅLÉŒ
        //                    _focus = _topMostHitInteractiveObject;
        //
        //                    //ÅLÉŒÅòÅò
        //                    _focus->__isFocus = true;
        //                    focusEvent = new FocusEvent(FocusEvent::FOCUS_IN);
        //                    focusEvent->__target = _focus;
        //                    _focus->dispatchEvent(focusEvent);
        //                }
        //                //------------------------------------
        //
        //                for(int i = 0; i < _lineBottomUp.size(); i++ ) {
        //                    //------------------------------------
        //                    MouseEvent* mouseEvent = new MouseEvent(MouseEvent::MOUSE_DOWN);
        //                    mouseEvent->__target = _topMostHitInteractiveObject;
        //                    mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
        //                    mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
        //                    mouseEvent->__stageX = mouseX();
        //                    mouseEvent->__stageY = mouseY();
        //                    intObj = _lineBottomUp[i];
        ////                    intObj->__isMouseDown = true; // TODO ÅíÅ˜ÅÒ
        //                    intObj->__isMousePressed = true;
        //                    intObj->dispatchEvent(mouseEvent);
        //                    //------------------------------------
        //
        //                    //mouseChildrenfalseÅıÅí
        //                    if(flUtil::isDisplayObjectContainer(intObj)) {
        //                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
        //                        if(!dispObjContainer->mouseChildren()) goto mouseDownCheckEnd;
        //                    }
        //                }
        //            }
        //        }
        //    mouseDownCheckEnd:
        
        //        //Å˜ÉŒÅëÅò
        //        if(__isMouseReleased) {
        //            if(_topMostHitInteractiveObject) {
        //                for(int i = 0; i < _lineBottomUp.size(); i++ ) {
        //                    //------------------------------------
        //                    MouseEvent* mouseEvent = new MouseEvent(MouseEvent::MOUSE_UP);
        //                    mouseEvent->__target = _topMostHitInteractiveObject;
        //                    mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
        //                    mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
        //                    mouseEvent->__stageX = mouseX();
        //                    mouseEvent->__stageY = mouseY();
        //                    intObj = _lineBottomUp[i];
        ////                    intObj->__isMouseDown = true; // TODO ÅíÅ˜ÅÒ
        //                    intObj->__isMousePressed = true;
        //                    intObj->dispatchEvent(mouseEvent);
        //                    //------------------------------------
        //
        //                    //mouseChildrenfalseÅıÅí
        //                    if(flUtil::isDisplayObjectContainer(intObj)) {
        //                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
        //                        if(!dispObjContainer->mouseChildren()) goto mouseUpCheckEnd;
        //                    }
        //                }
        //            }
        //        }
        //    mouseUpCheckEnd:
        
        return;
        //----------------------------------------------------------
    }
    
    //--------------------------------------------------------------
    //ÅÇÅıÅLÅèÅáÅ˜
    void flStage::_updateChildrenTwo(flDisplayObject* parent, vector<flDisplayObject*>& _children) {
        for(int i = 0; i < _children.size(); i++) {
            flDisplayObject* child;
            child = _children[i];
            
//            if(!child->visible()) continue;
            
            child->__compoundAlpha(parent->__compoundAlpha() * child->_alpha);
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container = (flDisplayObjectContainer*)child;
                
                if(container->numChildren() > 0) {
                    _updateChildrenTwo(child, container->children());
                }
            }
            
            // last thing we do is call the update method for each child.
            child->update();
        }
    }
    
    //--------------------------------------------------------------
    // 
    void flStage::_drawChildren(flDisplayObject* parent, vector<flDisplayObject*>& _children) {
        for(int i = 0; i < _children.size(); i++) {
            flDisplayObject* child;
            child = _children[i];

			if (child->__maskOwner != nullptr) continue;
			if (!child->visible()) continue;
            
            //-- matrix transform.
            bool bIdentity = true;
            bIdentity = child->transform().matrix().isIdentity();
            bIdentity = false;
            
            if(!bIdentity) {
                glPushMatrix();
                glMultMatrixf(child->transform().matrix().getPtr());
            }
            
            //child->drawOnFrame();
            child->draw();
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container = (flDisplayObjectContainer*)child;
                if(container->numChildren() > 0) {
                    _drawChildren(child, container->children());
                }
            }
            
            if(!bIdentity) {
                glPopMatrix();
            }
        }
    }
    
    //--------------------------------------------------------------
    flDisplayObject* flStage::_getMostHitDisplayObject(flDisplayObject* parent, vector<flDisplayObject*>& _children, int x, int y) {
//        ofLog() << "[flStage]_getMostHitDisplayObject(" << x << ", " << y << ")";
        flDisplayObject* mostHitDisplayObject;
        
        int i; int l;
        l = _children.size();
        for(i = 0; i < l; i++) {
            flDisplayObject* child;
            child = _children[i];
            
			if (child->__maskOwner != nullptr) continue;
			if (!child->visible()) continue;

            //------------------------------------ topMostHitDisplayObject

			bool isInEffectiveArea = true;

			if (isInEffectiveArea && child->mask() != nullptr) {
				isInEffectiveArea = child->mask()->hitTestPoint(_mouseX, _mouseY, true);
			}

			if (isInEffectiveArea) {
				//------------------------------------ mouseEnabled
				if (flUtil::isInteractiveObject(child)) {
					flInteractiveObject* intObj = (flInteractiveObject*)child;
					if (intObj->mouseEnabled()) {
						//------------------------------------ hitArea
						if (flUtil::isSprite(child)) {
							flSprite* sprite = (flSprite*)child;
							if (sprite->hitArea() == nullptr) {
								if (child->hitTestPoint(x, y, true)) {
									mostHitDisplayObject = child;
								}
							}
							else {

							}

						}
						else {
							if (child->hitTestPoint(x, y, true)) {
								mostHitDisplayObject = child;
							}
						}
						//------------------------------------ hitArea
					}
					else {
						//------------------------------------ hitArea
						if (flUtil::isSprite(child)) {
							flSprite* sprite = (flSprite*)child;
							if (sprite->__hitAreaObject) {
								if (child->hitTestPoint(x, y, true)) {
									mostHitDisplayObject = child;
								}
							}
							else {

							}
						}
						else {

						}
						//------------------------------------ hitArea

					}
				}
				else {
					if (child->hitTestPoint(x, y, true)) {
						mostHitDisplayObject = child;
					}
				}
				//------------------------------------ mouseEnabled

				//------------------------------------ topMostHitDisplayObject

				//------------------------------------
				if (_hasChildren(child)) {
					flDisplayObjectContainer* container = (flDisplayObjectContainer*)child;

					//------------------------------------ mouseChildren
					if (container->mouseChildren()) {
						if (container->numChildren() > 0) {
							flDisplayObject* hitDisplayObject = _getMostHitDisplayObject(child, container->children(), x, y);
							if (hitDisplayObject != nullptr) mostHitDisplayObject = hitDisplayObject;
							//                        mostHitDisplayObject = _getMostHitDisplayObject(child, container->children(), x, y);
						}
					}
					//------------------------------------ mouseChildren
				}
				//------------------------------------
			}
        }
        
//        if(mostHitDisplayObject) ofLog() << "[flStage]" << mostHitDisplayObject->name();
        return mostHitDisplayObject;
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseMove() {
        //        if(debug()) ofLog() << "[flStage]_mouseMove()";
        
        if(_mouseID != 0) return;
        
        flMouseEvent* mouseEvent;
        //----------------------------------------------------------
        mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //----------------------------------------------------------
        
        //----------------------------------------------------------
        if(_topMostHitInteractiveObject) {
            mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
            mouseEvent->__target = _topMostHitInteractiveObject;
            mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
            mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
            mouseEvent->__stageX = mouseX();
            mouseEvent->__stageY = mouseY();
            _topMostHitInteractiveObject->dispatchEvent(mouseEvent);
        }
        //----------------------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::_debugDraw(flDisplayObject* parent, vector<flDisplayObject*>& _children) {
        for(int i = 0; i < _children.size(); i++) {
            flDisplayObject* child;
            child = _children[i];

			if (child->__maskOwner != nullptr) continue;
            if (!child->visible()) continue;
            
            //-- matrix transform.
            bool bIdentity = true;
            bIdentity = child->transform().matrix().isIdentity();
            bIdentity = false;
            
            if(!bIdentity) {
                glPushMatrix();
                glMultMatrixf(child->transform().matrix().getPtr());
            }
            
            ofSetHexColor(0xff0000);
            float n = 5 / child->scaleX();
            ofDrawLine(-n, 0, n, 0);
            ofDrawLine(0, -n, 0, n);
            
            ofNoFill();
            ofDrawRectangle(child->_rect->left(), child->_rect->top(), child->_rect->right(), child->_rect->bottom());
            ofFill();
            
            ofSetHexColor(0x000000);
            string t = ofToString(child->name()) + " x:" + ofToString(child->x()) + " y:" + ofToString(child->y());
            ofDrawBitmapString(t, -50, -10);
            ofSetHexColor(0xffffff);
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                if(container->numChildren() > 0) {
                    _debugDraw(child, container->children());
                }
            }
            
            if(!bIdentity) {
                glPopMatrix();
            }
        }
    }
    
    //==============================================================
    // Protected / Private EventHandler
    //==============================================================

	//--------------------------------------------------------------
	void flStage::_childEventHandler(flEvent& event) {
		//ofLog() << "[flStage]_childEventHandler(" << event.type() << ")";
		//ofLog() << "[flStage]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flStage]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flStage]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();

		if (event.type() == flEvent::ADDED) {
			if (event.target() == this) {

			}
		}
		else if (event.type() == flEvent::ADDED_TO_STAGE) {
			if (event.target() == this) {

			}
		}
		else if (event.type() == flEvent::REMOVED) {
            //ofLog() << "[flStage]_childEventHandler(" << event.type() << ")";
            //ofLog() << "[flStage]this          = " << this << "," << ((flDisplayObject*)this)->name();
            //ofLog() << "[flStage]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
            //ofLog() << "[flStage]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();
            //ofLog() << "[flStage]topMostHitDisplayObject        = " << ((_topMostHitDisplayObject) ? _topMostHitDisplayObject->name() : "");
            //ofLog() << "[flStage]topMostHitDisplayObjectPrev        = " << ((_topMostHitDisplayObject) ? _topMostHitDisplayObjectPrev->name() : "");

            ((flDisplayObject*)event.target())->removeEventListener(flEvent::REMOVED, this, &flStage::_childEventHandler);
            //_removeFromList((flDisplayObject*)event.target());

			//if (event.target() == this) {
   //             flDisplayObject* displayObject = (flDisplayObject*)event.target();
   //             _removeFromList(displayObject);
			//}
		}
		else if (event.type() == flEvent::REMOVED_FROM_STAGE) {
			if (event.target() == this) {

			}
		}
	}

    //--------------------------------------------------------------
    void flStage::_updateEventHandler(ofEventArgs& event) {
        update();

		//try {
		//	update();
		//} catch(...) {
		//	ofLog() << "[flStage]update error";
		//	//êiçsèÛãµ
		//	ofLog(OF_LOG_VERBOSE) << "the number is " << 10;
		//	ofLog(OF_LOG_VERBOSE) << "the number is " << 20;
		//	//åxçê
		//	ofLog(OF_LOG_NOTICE) << "the number is " << 10;
		//	//åxçê
		//	ofLog(OF_LOG_WARNING) << "the number is " << 10;
		//	//ÉGÉâÅ[
		//	ofLog(OF_LOG_ERROR) << "the number is " << 10;
		//	//ívñΩìIÇ»ÉGÉâÅ[
		//	ofLog(OF_LOG_FATAL_ERROR) << "the number is " << 10;
		//	//ê√Ç©Ç»ÉçÉO
		//	ofLog(OF_LOG_SILENT) << "the number is " << 10;
		//	ofExit();
		//}
	}
    //--------------------------------------------------------------
    void flStage::_drawEventHandler(ofEventArgs& event) {
        draw();
        //try {
        //    draw();
        //} catch(...) {
        //    ofLog() << "[flStage]draw error";
        //}
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseMoveEventHandler(ofMouseEventArgs& event) {
        if(debug()) ofLog() << "[flStage]_mouseMoveEventHandler()";
        
        if(_mouseID != 0) return;
        
        //_mouseX = event.x;
        //_mouseY = event.y;
        
        //dispatchEvent(new Event(MouseEvent::MOUSE_MOVE));
        
        flMouseEvent* mouseEvent;
        //------------------------------------
        mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //------------------------------------
        //------------------------------------
        if(_topMostHitInteractiveObject) {
            mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
            mouseEvent->__target = _topMostHitInteractiveObject;
            mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
            mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
            mouseEvent->__stageX = mouseX();
            mouseEvent->__stageY = mouseY();
            _topMostHitInteractiveObject->dispatchEvent(mouseEvent);
        }
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseDragEventHandler(ofMouseEventArgs& event) {
        if(_mouseID != 0) return;
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::DRAGGING);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseDownEventHandler(ofMouseEventArgs& event) {
        if(debug()) ofLog() << "[flStage]_mouseDownEventHandler()";
        
        _mouseID = event.button;
        
        __isMouseDown	= true;
        __isMousePressed = true;
        
        _isMouseChanged = (_mouseID != 0);
        if(_isMouseChanged) _mouseID = 0;

		_startTime = ofGetElapsedTimef();
        
        //------------------------------------
        if(_topMostHitInteractiveObject) {
            //            _topMostHitInteractiveObject->__isMousePressed = true; // TODO ÅíÅ˜ÅÒ
            


            //------------------------------------
             //2016.6.8
             //ÅLÉŒÅòÅí
            if (_focus != _topMostHitInteractiveObject) {
                if (_focus) {
                    // ÅÒÅòÅÁ
                    try {
                        //ÅLÉŒÅëÅ˜Åò
                        _focus->__isFocus = false;

                        flFocusEvent* focusEvent = new flFocusEvent(flFocusEvent::FOCUS_OUT);
                        focusEvent->__target = _focus;
                        _focus->dispatchEvent(focusEvent);
                        if (true) {
                            //ofLog() << "focus out = " << _focus->name().c_str();
                        }
                        // ÅÒÅòÉŒÅÇ
                        //                    throw "ÅÒÅòÅÁ";
                    }
                    catch (const char* str) {
                        // ÅÒÅòÅÇÅí
                        ofLog(OF_LOG_ERROR) << str;
                    }
                }

                //ÅLÉŒ
                _lineBottomUpForFocus.clear();
                _focus = _topMostHitInteractiveObject;
                if (_focus) {
                    _lineBottomUpForFocus.resize(_lineBottomUp.size());
                    copy(_lineBottomUp.begin(), _lineBottomUp.end(), _lineBottomUpForFocus.begin());
                    //memcpy(&_lineBottomUpForFocus[0], &_lineBottomUp, sizeof(_lineBottomUp));
                    //memcpy(&_lineBottomUpForFocus, &_lineBottomUp, sizeof(_lineBottomUp));

                    //ÅLÉŒÅòÅò
                    _focus->__isFocus = true;

                    flFocusEvent* focusEvent = new flFocusEvent(flFocusEvent::FOCUS_IN);
                    focusEvent->__target = _focus;
                    _focus->dispatchEvent(focusEvent);
                    if (true) {
                        //ofLog() << "focus in = " << _focus->name().c_str();
                    }
                }
            }
            //------------------------------------

            //------------------------------------

            if (_topMostHitInteractiveObject) {
                _topMostHitInteractiveObject->__isMouseDown = true;
                _currentMouseDownInteractiveObject = _topMostHitInteractiveObject;
            }



			//ofLog() << "MouseDownCheck";
            for(int i = 0; i < _lineBottomUp.size(); i++ ) {
				if (_topMostHitInteractiveObject == nullptr) continue;

				flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_DOWN);
				mouseEvent->__target = _topMostHitInteractiveObject;
				mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
				mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
				mouseEvent->__stageX = mouseX();
				mouseEvent->__stageY = mouseY();

                //------------------------------------
				flInteractiveObject* intObj = _lineBottomUp[i];
				//ofLog() << "_lineBottomUp[" << i << "].name = " << _lineBottomUp[i]->name();
				intObj->__isMouseDown = true;
				intObj->__isMousePressed = true;

				bool bMouseDownCheckEnd = false;
				if(flUtil::isDisplayObjectContainer(intObj)) {
					flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
					if (!dispObjContainer->mouseChildren()) bMouseDownCheckEnd = true;
				}

				intObj->dispatchEvent(mouseEvent);
                //------------------------------------
                
                //mouseChildrenfalseÅıÅí
                //if(flUtil::isDisplayObjectContainer(intObj)) {
                //    flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                //    if(!dispObjContainer->mouseChildren()) goto mouseDownCheckEnd;
                //}

				if (bMouseDownCheckEnd) goto mouseDownCheckEnd;
            }

        mouseDownCheckEnd:;

        } else {
            //------------------------------------
            //ÅLÉŒ
            if(_focus != this) {
				if (_focus) {
					//ÅLÉŒÅëÅ˜Åò
					_focus->__isFocus = false;
					flFocusEvent* focusEvent = new flFocusEvent(flFocusEvent::FOCUS_OUT);
					focusEvent->__target = _focus;
					_focus->dispatchEvent(focusEvent);
					if (true) {
						//                    ofLog() << "focus out = " << _focus->name().c_str();
					}
				}
                
				_lineBottomUpForFocus.clear();
				_focus = this;
				{
					_lineBottomUpForFocus.resize(_lineBottomUp.size());
					copy(_lineBottomUp.begin(), _lineBottomUp.end(), _lineBottomUpForFocus.begin());
					//memcpy(&_lineBottomUpForFocus[0], &_lineBottomUp, sizeof(_lineBottomUp));
					//memcpy(&_lineBottomUpForFocus, &_lineBottomUp, sizeof(_lineBottomUp));

					//ÅLÉŒÅòÅò
					_focus->__isFocus = true;
					flFocusEvent* focusEvent = new flFocusEvent(flFocusEvent::FOCUS_IN);
					focusEvent->__target = _focus;
					_focus->dispatchEvent(focusEvent);

					if (true) {
						//ofLog() << "focus in = " << _focus->name().c_str();
					}
				}
            }
            //------------------------------------
        }
        //------------------------------------
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_DOWN);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        this->__isMouseDown = true;
        dispatchEvent(mouseEvent);
        //------------------------------------
        
        //ofLog() << "isFocus = " << isFocus();
        //ofLog() << "flStage->focus = " << focus()->name();
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseUpEventHandler(ofMouseEventArgs& event) {
        if(_mouseID != 0) return;
        
        __isMouseDown = false; 
        __isMouseReleased = true;

		float elapsedTime = ofGetElapsedTimef() - _startTime;
		//ofLog(OF_LOG_NOTICE) << "elapsedTime = " << elapsedTime;
        
        //------------------------------------
        //    if(_topMostHitInteractiveObjectPrev) _topMostHitInteractiveObjectPrev->__isMouseDown = false;
        // Å˜É∂??
        //    if(_topMostHitInteractiveObject) _topMostHitInteractiveObject->__isMouseDown = false;
        
        //------------------------------------
        //2016.6.8
        //Å˜ÉŒÅëÅò
        if(_topMostHitInteractiveObject) {

            for(int i = 0; i < _lineBottomUp.size(); i++ ) {
				if (_topMostHitInteractiveObject == nullptr) continue;

                //------------------------------------
                flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_UP);
                mouseEvent->__target = _topMostHitInteractiveObject;
                mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
                mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
                mouseEvent->__stageX = mouseX();
                mouseEvent->__stageY = mouseY();

				//------------------------------------
				flInteractiveObject* intObj = _lineBottomUp[i];
				//ofLog() << "_lineBottomUp[" << i << "].name = " << _lineBottomUp[i]->name();
				//intObj->__isMouseDown = true; // TODO ÅíÅ˜ÅÒ
				intObj->__isMouseDown = false;
				//intObj->__isMousePressed = true;
				intObj->__isMouseReleased = true;

				bool bMouseUpCheckEnd = false;
				if (flUtil::isDisplayObjectContainer(intObj)) {
					flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*)intObj;
					if (!dispObjContainer->mouseChildren()) bMouseUpCheckEnd = true;
				}

                intObj->dispatchEvent(mouseEvent);
                //------------------------------------
                
                //mouseChildrenfalseÅıÅí
                //if(flUtil::isDisplayObjectContainer(intObj)) {
                //    flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                //    if(!dispObjContainer->mouseChildren()) goto mouseUpCheckEnd;
                //}

				if (bMouseUpCheckEnd) goto mouseUpCheckEnd;
            }
        }
    mouseUpCheckEnd:
        //------------------------------------
        
        if(_currentMouseDownInteractiveObject) {
//            _currentMouseDownInteractiveObject->__isMousePressed = false; // TODO ÅíÅ˜ÅÒ
            _currentMouseDownInteractiveObject->__isMouseDown = false;

			//------------------------------------
			if ((elapsedTime <= 0.35) && (_currentMouseDownInteractiveObject == _topMostHitInteractiveObject)) {
				flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::CLICK);
				mouseEvent->__target = _currentMouseDownInteractiveObject;
				mouseEvent->__localX = _currentMouseDownInteractiveObject->mouseX();
				mouseEvent->__localY = _currentMouseDownInteractiveObject->mouseY();
				mouseEvent->__stageX = mouseX();
				mouseEvent->__stageY = mouseY();
				_currentMouseDownInteractiveObject->dispatchEvent(mouseEvent);
			}
			//------------------------------------
	
			_currentMouseDownInteractiveObject = nullptr;
		}
        //------------------------------------
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_UP);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        __isMouseDown = false;
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::_mouseScrolledEventHandler(ofMouseEventArgs& event) {
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_SCROLLED);
        mouseEvent->__target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        mouseEvent->__scrollX = event.scrollX;
        mouseEvent->__scrollY = event.scrollY;
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    void flStage::_keyDownEventHandler(ofKeyEventArgs& event) {
        if(debug()) ofLog() << "[flStage]_keyDownEventHandler()";
        
        int key = event.key;
        //Space
        if(key == 32) flKeyboard::isSpaceKeyDown(true);
        //Shift
        if(key == 2304) flKeyboard::isShiftKeyDown(true);
                
        flKeyboardEvent* keyboardEvent = nullptr;
        
        //------------------------------------
        if(!flKeyboard::__checkKeyIsDown(key)) {
        //if(_isKeyDown == false) {
            keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_PRESS);
            keyboardEvent->__keyCode = key;
            dispatchEvent(keyboardEvent);
            
            if(_focus != this) {
				//ofLog() << "--------------------------------";
				//ofLog() << "_lineBottomUpForFocus.size() = " << _lineBottomUpForFocus.size();
				//ofLog() << "_focus = " << _focus->name();
				for (int i = 0; i < _lineBottomUpForFocus.size(); i++) {
					flDisplayObject* dispObj = _lineBottomUpForFocus[i];
					//ofLog() << "dispObj = " << dispObj->name();

					if (flUtil::isInteractiveObject(dispObj)) {
						flInteractiveObject* intObj = (flInteractiveObject*)dispObj;
						if (intObj->mouseEnabled()) {
							keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_PRESS);
							keyboardEvent->__target = _focus;
							keyboardEvent->__keyCode = key;
							intObj->dispatchEvent(keyboardEvent);
						}
					}
				}
				//ofLog() << "--------------------------------";
            }
		}
        //------------------------------------
        
        //------------------------------------
        keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_DOWN);
        keyboardEvent->__keyCode = key;
        dispatchEvent(keyboardEvent);

		if (_focus != this) {
			//ofLog() << "--------------------------------";
			//ofLog() << "_lineBottomUpForFocus.size() = " << _lineBottomUpForFocus.size();
			//ofLog() << "_focus = " << _focus->name();
			for (int i = 0; i < _lineBottomUpForFocus.size(); i++) {
				flDisplayObject* dispObj = _lineBottomUpForFocus[i];
				//ofLog() << "dispObj = " << dispObj->name();

				if (flUtil::isInteractiveObject(dispObj)) {
					flInteractiveObject* intObj = (flInteractiveObject*)dispObj;
					if (intObj->mouseEnabled()) {
						keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_DOWN);
						keyboardEvent->__target = _focus;
						keyboardEvent->__keyCode = key;
						intObj->dispatchEvent(keyboardEvent);
					}
				}
			}
			//ofLog() << "--------------------------------";
		}
        //------------------------------------
        
        flKeyboard::__addDownKey(key);
        //_isKeyDown = true;
    }
    
    //--------------------------------------------------------------
    void flStage::_keyUpEventHandler(ofKeyEventArgs& event) {
        if(debug()) ofLog() << "[flStage]_keyUpEventHandler()";
        
        int key = event.key;
        //Space
        if(key == 32) flKeyboard::isSpaceKeyDown(false);
        //Shift
        if(key == 2304) flKeyboard::isShiftKeyDown(false);
        
		flKeyboardEvent* keyboardEvent = nullptr;

		//------------------------------------
		if (flKeyboard::__checkKeyIsDown(key)) {
			//if(_isKeyDown) {
			keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_RELEASE);
			keyboardEvent->__keyCode = key;
			dispatchEvent(keyboardEvent);

			if (_focus != this) {
				//ofLog() << "--------------------------------";
				//ofLog() << "_lineBottomUpForFocus.size() = " << _lineBottomUpForFocus.size();
				//ofLog() << "_focus = " << _focus->name();
				for (int i = 0; i < _lineBottomUpForFocus.size(); i++) {
					flDisplayObject* dispObj = _lineBottomUpForFocus[i];
					//ofLog() << "dispObj = " << dispObj->name();

					if (flUtil::isInteractiveObject(dispObj)) {
						flInteractiveObject* intObj = (flInteractiveObject*)dispObj;
						if (intObj->mouseEnabled()) {
							keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_RELEASE);
							keyboardEvent->__target = _focus;
							keyboardEvent->__keyCode = key;
							intObj->dispatchEvent(keyboardEvent);
						}
					}
				}
				//ofLog() << "--------------------------------";
			}
		}
		//------------------------------------

		//------------------------------------
		keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_UP);
		keyboardEvent->__keyCode = key;
		dispatchEvent(keyboardEvent);

		if (_focus != this) {
			//ofLog() << "--------------------------------";
			//ofLog() << "_lineBottomUpForFocus.size() = " << _lineBottomUpForFocus.size();
			//ofLog() << "_focus = " << _focus->name();
			for (int i = 0; i < _lineBottomUpForFocus.size(); i++) {
				flDisplayObject* dispObj = _lineBottomUpForFocus[i];
				//ofLog() << "dispObj = " << dispObj->name();

				if (flUtil::isInteractiveObject(dispObj)) {
					flInteractiveObject* intObj = (flInteractiveObject*)dispObj;
					if (intObj->mouseEnabled()) {
						keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_UP);
						keyboardEvent->__target = _focus;
						keyboardEvent->__keyCode = key;
						intObj->dispatchEvent(keyboardEvent);
					}
				}
			}
			//ofLog() << "--------------------------------";
		}
		//------------------------------------
        
        flKeyboard::__removeDownKey(key);
        //_isKeyDown = false;
    }
    
    //==============================================================
    // Resize
    //==============================================================
    
    //--------------------------------------------------------------
    void flStage::_resizeEventHandler(ofResizeEventArgs& event) {
        _stageWidth = event.width;
        _stageHeight = event.height;
        
        flBlendMode::resize(_stageWidth, _stageHeight);
    }
    
    //==============================================================
    // Utility
    //==============================================================

	//--------------------------------------------------------------
	void flStage::_removeFromList(flDisplayObject* displayObject) {
        if (displayObject == nullptr) return;

        if (_focus == displayObject) {
            _focus->__isFocus = false;
            flFocusEvent* focusEvent = new flFocusEvent(flFocusEvent::FOCUS_OUT);
            focusEvent->__target = _focus;
            _focus->dispatchEvent(focusEvent);

            _lineBottomUpForFocus.clear();
            _focus = nullptr;
        }
		if (_topMostHitDisplayObject == displayObject) _topMostHitDisplayObject = nullptr;
		if (_topMostHitDisplayObjectPrev == displayObject) _topMostHitDisplayObjectPrev = nullptr;
		if (_topMostHitInteractiveObject == displayObject) _topMostHitInteractiveObject = nullptr;
		if (_topMostHitInteractiveObjectPrev == displayObject) _topMostHitInteractiveObjectPrev = nullptr;
		if (_currentMouseDownInteractiveObject == displayObject) {
			_currentMouseDownInteractiveObject = nullptr;
			_startTime = 0.0;
		}

		int l = 0;
		l = _lineBottomUpForFocus.size();
		for (int i = 0; i < l; i++) {
			if (_lineBottomUpForFocus[i] == displayObject) {
				_lineBottomUpForFocus.erase(_lineBottomUpForFocus.begin() + i);
				break;
				//--i;
				//--l;
			}
		}		
		
		l = _lineBottomUp.size();
		for (int i = 0; i < l; i++) {
			if (_lineBottomUp[i] == displayObject) {
				_lineBottomUp.erase(_lineBottomUp.begin() + i);
				break;
				//--i;
				//--l;
			}
		}

		l = _lineBottomUpPrev.size();
		for (int i = 0; i < l; i++) {
			if (_lineBottomUpPrev[i] == displayObject) {
				_lineBottomUpPrev.erase(_lineBottomUpPrev.begin() + i);
				break;
				//--i;
				//--l;
			}
		}

		if (_hasChildren(displayObject)) {
			flDisplayObjectContainer* displayObjectContainer = (flDisplayObjectContainer*)displayObject;
			if (displayObjectContainer->mouseChildren()) {
				for (int i = 0; i < displayObjectContainer->numChildren(); i++) {
					_removeFromList(displayObjectContainer->children()[i]);
				}
			}
		}
	}
}

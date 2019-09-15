/**
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashDisplayObjectContainer.h
 
 ActionScript3.0 Reference
 flash.display.DisplayObjectContainer
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/DisplayObjectContainer.html
 
 */

#pragma once

#include "flInteractiveObject.h"
#include "flEvent.h"

namespace fl2d {
    
    class flDisplayObjectContainer : public flInteractiveObject {
        
    public:
        vector<flDisplayObject*> children;
        
    protected:
        
    private:
        bool _mouseChildren;
        //bool _tabChildren;
        
    public:
        virtual void update();
        virtual void draw(bool applyMatrix = true);
        
        bool mouseChildren();
        void mouseChildren(bool value);
        int numChildren();
        virtual bool contains(flDisplayObject* child);
        
        virtual flDisplayObject* stage();
        virtual void stage(flDisplayObject* value);
        
        virtual flDisplayObject* addChild(flDisplayObject* child);
        virtual flDisplayObject* addChild(flDisplayObject* child, int x, int y);
        virtual flDisplayObject* addChildAt(flDisplayObject* child, int index);
        virtual flDisplayObject* removeChild(flDisplayObject* child);
        virtual flDisplayObject* removeChildAt(int index);
        virtual void removeAllChildren();
        
        virtual flDisplayObject* getChildAt(int index);
        virtual flDisplayObject* getChildByName(string name);
        virtual int getChildIndex(flDisplayObject* child);
        virtual vector<flDisplayObject*> getObjectsUnderPoint(ofPoint point);
        
        virtual void setChildIndex(flDisplayObject* child, int index);
        virtual void swapChildren(flDisplayObject* child1, flDisplayObject* child2);
        virtual void swapChildrenAt(int index1, int index2);
        
    protected:
        flDisplayObjectContainer();
        virtual ~flDisplayObjectContainer();
        
        virtual void _updateRect();
        
        bool _hasChildren(flDisplayObject* displayObject);
        
    private:
    };
    
}

/**
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashDisplayObjectContainer.h
 
 ActionScript3.0 Reference
 flash.display.DisplayObjectContainer
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/DisplayObjectContainer.html
 
 */

#pragma once

#include "InteractiveObject.h"
#include "Event.h"

namespace fl2d {
    
    class DisplayObjectContainer : public InteractiveObject {
        
    public:
        vector<DisplayObject*> children;
        
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
        virtual bool contains(DisplayObject* child);
        
        virtual DisplayObject* stage();
        virtual void stage(DisplayObject* value);
        
        virtual DisplayObject* addChild(DisplayObject* child);
        virtual DisplayObject* addChild(DisplayObject* child, int x, int y);
        virtual DisplayObject* addChildAt(DisplayObject* child, int index);
        virtual DisplayObject* removeChild(DisplayObject* child);
        virtual DisplayObject* removeChildAt(int index);
        virtual void removeAllChildren();
        
        virtual DisplayObject* getChildAt(int index);
        virtual DisplayObject* getChildByName(string name);
        virtual int getChildIndex(DisplayObject* child);
        virtual vector<DisplayObject*> getObjectsUnderPoint(ofPoint point);
        
        virtual void setChildIndex(DisplayObject* child, int index);
        virtual void swapChildren(DisplayObject* child1, DisplayObject* child2);
        virtual void swapChildrenAt(int index1, int index2);
        
    protected:
        DisplayObjectContainer();
        virtual ~DisplayObjectContainer();
        
        virtual void _updateRect();
        
        bool _hasChildren(DisplayObject* displayObject);
        
    private:
    };
    
}

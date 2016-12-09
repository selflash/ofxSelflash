#pragma once

#include "ofMain.h"

#include "../display/Shape.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"

namespace fl2d {
    
    class ScrollKit : public Sprite {
        
        public:
            Shape* base;
            
            ofRectangle viewport;

        protected:
            
        private:
            DisplayObject* _body;
            
            float _disy;
            
        public:
            ScrollKit();
            virtual ~ScrollKit();
            
            DisplayObject* body();
            void body(DisplayObject* value);
            
            void drawViewportOutline(const ofRectangle & viewport);

            
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
        private:        
            void _mouseEventHandler(Event& event);
            void _moveEventHandler(Event& event);
    };
    
}

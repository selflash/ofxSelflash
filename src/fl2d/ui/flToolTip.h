#pragma once

#include "ofMain.h"
#include "flSprite.h"
#include "flFont.h"

namespace fl2d {
    
    class flToolTip : public flSprite {
        
        public:
        
        protected:
        
        private:
            //string _text = u8"ここにテキストが入ります。";
			string _text ="Test";
            int _fontHeight = 0;
        
        public:
            flToolTip();
            virtual ~flToolTip();
        
            string text();
            void text(string value);
        
        protected:
//            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
        private:
            virtual void _updateWindow();

        };
    
}

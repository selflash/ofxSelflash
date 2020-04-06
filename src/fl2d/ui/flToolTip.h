#pragma once

#include "ofMain.h"
#include "flShape.h"
#include "flFont.h"

namespace fl2d {
    class flSprite;
    class flToolTip : public flShape {
        friend flSprite;

        public:
        
        protected:
        
        private:
			string _text = "Some information is displayed here.";
            int _fontHeight = 0;
        
            bool _bReady = false;
        
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

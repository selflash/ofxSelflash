/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flSlider;
    class flRangeSlider;
    class flSimpleSlider;
    class flSliderEvent : public flEvent {
        friend class flSlider;
        friend class flRangeSlider;
        friend class flSimpleSlider;
        
        public:
            static string CHANGE;
            static string THUMB_DRAG;
            static string THUMB_PRESS;
            static string THUMB_RELEASE;
        
        protected:
            //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
            void* _clickTarget;
        
        private:
        
        public:
            flSliderEvent(string type);
            virtual ~flSliderEvent();
        
            template <class T>
            T data() { return getProperty<T>("data"); }
        
        protected:
        
        private:
            template <class T>
            void data(T value) { setProperty<T>("data", value); }
        
    };
    
}

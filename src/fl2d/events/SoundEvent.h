/**
 
 ActionScript3.0 Reference
 flash.video.SoundEvent
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/fl/video/SoundEvent.html
 
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class SoundEvent : public Event {
        
    public:
        static string SOUND_UPDATE;
        static string ON_BEAT;
        static string ON_BACK_BEAT;
        static string ON_4_BEAT;
        static string ON_8_BEAT;
        static string ON_16_BEAT;
        
        static string ON_LEFT_BEAT;
        static string ON_RIGHT_BEAT;
        
    private:
        
    public:
        SoundEvent(string type);
        virtual ~SoundEvent();
        
    private:
        
    };
    
}

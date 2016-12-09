﻿/**
 
 ActionScript3.0 Reference
 flash.events.KeyboardEvent
 http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/flash/events/KeyboardEvent.html
 
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Stage;
    class KeyboardEvent : public Event {
        friend Stage;
            
        public:
            static string KEY_DOWN;
            static string KEY_UP;
            static string KEY_PRESS;
            static string KEY_RELEASE;
        
        protected:
            //int __charCode;
            int __keyCode;

        private:
        
        public:
            KeyboardEvent(string type);
            virtual ~KeyboardEvent();
            
            //押したキーまたは離したキーの文字コード値を含みます。
            //int charCode();
            //押したキーまたは離したキーのキーコード値です。
            virtual inline int keyCode() { return __keyCode; }
            
        private:
            
    };
    
}

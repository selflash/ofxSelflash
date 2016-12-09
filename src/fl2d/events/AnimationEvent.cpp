#include "AnimationEvent.h"

namespace fl2d {
    
    string AnimationEvent::POSITION_COMPLETE = "positionComplete";
    string AnimationEvent::SIZE_COMPLETE = "sizeComplete";
    string AnimationEvent::SCALE_COMPLETE = "scaleComplete";
    string AnimationEvent::ROTATION_COMPLETE = "rotationComplete";
    string AnimationEvent::COLOR_COMPLETE = "colorComplete";
    
    //--------------------------------------------------------------
    //
    AnimationEvent::AnimationEvent(string type):Event(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    AnimationEvent::~AnimationEvent() {
        
    }
    
}

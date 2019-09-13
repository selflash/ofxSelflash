#include "SoundEvent.h"

namespace fl2d {
    
    string SoundEvent::SOUND_UPDATE = "soundUpdate";
    string SoundEvent::ON_BEAT = "onBeat";
    string SoundEvent::ON_BACK_BEAT = "onBackBeat";
    string SoundEvent::ON_4_BEAT = "on4Beat";
    string SoundEvent::ON_8_BEAT = "on8Beat";
    string SoundEvent::ON_16_BEAT = "on16Beat";

    string SoundEvent::ON_LEFT_BEAT = "onLeftBeat";
    string SoundEvent::ON_RIGHT_BEAT = "onRightBeat";

    string SoundEvent::COMPLETED = "completed";

    //--------------------------------------------------------------
    //
    SoundEvent::SoundEvent(string type):Event(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    SoundEvent::~SoundEvent(){
        
    }
    
}

#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"

namespace fl2d {
    
    class flUIBase : public flSprite {
        
    public:
        
    protected:
        flTextField* _label;
        bool _enabled;

        //------------------------------------------
        bool _changedValueByMyself = false;
//        ofParameter<float>* _param;
        ofEventListener _valueListener;
        //------------------------------------------

    private:
        
    public:
        virtual flTextField* label();
        virtual void label(flTextField* value);
        
        virtual bool enabled();
        virtual void enabled(bool value);
        
        //------------------------------------------
        virtual inline void bind(ofParameter<float>& param) {

        }
        virtual inline void unbind() {
            
        }
        //------------------------------------------
        
    protected:
        flUIBase();
        virtual ~flUIBase();

    private:
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}

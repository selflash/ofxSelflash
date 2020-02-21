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
        flTextField* _label = NULL;
        bool _enabled = true;

        //------------------------------------------
        bool _bChangedByMyself = false;
        bool _bChangedByOfParm = false;
        ofEventListeners _listeners;
        //------------------------------------------

    private:
        
    public:
        virtual flTextField* label();
        virtual void label(flTextField* value);
        
        virtual bool enabled();
        virtual void enabled(bool value);
        
        //------------------------------------------
        virtual inline void bind(ofParameter<float>& param);
        virtual inline void bind(ofParameter<int>& param);
        virtual inline void bind(ofParameter<bool>& param);
        template <class T>
        inline void bind(ofParameter<T>& param);
        virtual inline void unbind();
        //------------------------------------------
        
    protected:
        flUIBase();
        virtual ~flUIBase();

    private:
        virtual void _mouseEventHandler(flEvent& event);
    };
    
}

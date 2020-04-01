#pragma once

#include "ofMain.h"

#include "flStage.h"
#include "flDefinition.h"
#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flToolTip.h"

//using namespace glm;

namespace fl2d {
    
    class flUIBase : public flSprite {
        
    public:
        
    protected:
        bool _toolTipEnabled = false;
        flToolTip* _toolTip = NULL;
        bool _showToolTip = false;
        ofPoint _mouseWhenRollOver;
        
        flTextField* _label = NULL;
        bool _enabled = true;

        //------------------------------------------
        map<string, bool> _bChangedByMyself;
        map<string, bool> _bChangedByOfParm;
        //------------------------------------------

    private:
        
    public:
        virtual inline flToolTip* toolTip() { return _toolTip; }
        virtual bool toolTipEnabled();
        virtual void toolTipEnabled(bool value);
        virtual inline string toolTipText() { return _toolTip->text(); }
        virtual inline void toolTipText(string value) { _toolTip->text(value); }

        virtual flTextField* label();
        virtual void label(flTextField* value);

        virtual bool enabled();
        virtual void enabled(bool value);
        
        //------------------------------------------
//        virtual inline void bind(ofParameter<float>& param);
//        virtual inline void bind(ofParameter<int>& param);
//        virtual inline void bind(ofParameter<bool>& param);
//        template <class T>
//        virtual void bind(ofParameter<T>& param);
//        virtual inline void unbind();
        //------------------------------------------
        
    protected:
        flUIBase();
        virtual ~flUIBase();
        
        virtual void _update();

        virtual void _mouseEventHandler(flEvent& event);

    private:
    };
    
}

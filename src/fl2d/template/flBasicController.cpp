#include "flBasicController.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flBasicController::flBasicController() {
		//ofLog() << "[flBasicController]flBasicController()";
        
        _target = this;
        name("flBasicController");

		_title = "[Contoller]";

        useHandCursor(true);
	}
    
    //--------------------------------------------------------------
    flBasicController::~flBasicController() {
		//ofLog() << "[flBasicController]~flBasicController()";
        
        _target = NULL;

		_graphics = NULL;
        
        for(auto* radioButtonGroup : radioButtonGroups) {
            delete radioButtonGroup;
            radioButtonGroup = NULL;
        }
        radioButtonGroups.clear();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //==============================================================
    // Public Method
    //==============================================================

	//==============================================================
	// Protected / Private Method
	//==============================================================

    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

	//--------------------------------------------------------------
	void flBasicController::_mouseEventHandler(flEvent& event) {
		//ofLog() << "[flBasicController]_mouseEventHandler(" << event.type() << ")";
		//ofLog() << "[flBasicController]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flBasicController]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flBasicController]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();

		flBasicUIWindow::_mouseEventHandler(event);

		//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Down
		if (event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Up
		if (event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}
	}

    //--------------------------------------------------------------
    void flBasicController::_uiEventHandler(flEvent& event) {
        //ofLog() << "[flBasicController]_uiEventHandler(" << event.type() << ")";
        //ofLog() << "[flBasicController]this          = " << this << "," << ((flDisplayObject*) this)->name();
        //ofLog() << "[flBasicController]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
        //ofLog() << "[flBasicController]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();

		flBasicUIWindow::_uiEventHandler(event);

        //�{�^��
        if(event.type() == flButtonEvent::ROLL_OVER) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::ROLL_OUT) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_OVER) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_OUT) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_DOWN) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
		}
        if(event.type() == flButtonEvent::MOUSE_UP) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }     
		if(event.type() == flButtonEvent::CLICK) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
		}
        if(event.type() == flButtonEvent::CHANGE) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }

        //�R���{�{�b�N�X
        if(event.type() == flComboBoxEvent::CHANGE) {
            flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
            flComboBox* comboBox = (flComboBox*)(event.currentTarget());
            
//            ofLog() << "-------------";
//            ofLog() << comboBox->name() << " :";
//            ofLog() << "selectedIndex : " << comboBox->selectedIndex();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<string>();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<float>();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<flComboBox*>()->name();
        }
        
        //�`�F�b�N�{�b�N�X
        if(event.type() == flCheckBoxEvent::CHANGE) {
            flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
            flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
        }
        
        //���W�I�{�^��
        if(event.type() == flRadioButtonEvent::CHANGE) {
            flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
            flRadioButton* radio = (flRadioButton*)(event.currentTarget());
        }
        
        //�i���o�[�_�C�A���[
        if(event.type() == flNumericDialerEvent::CHANGE) {
            flNumericDialerEvent& numberDialerEvent = *(flNumericDialerEvent*) &event;
            flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
        }
        
        //2D�p�b�h
        if(event.type() == flPadEvent::CHANGE) {
            flPadEvent& padEvent = *(flPadEvent*) &event;
            flPad2D* pad = (flPad2D*)(event.currentTarget());
        }
        
        //�X���C�_�[
        if(event.type() == flSliderEvent::CHANGE) {
            flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
            flSlider* slider = (flSlider*)(event.currentTarget());
        }
        
        //�����W�X���C�_�[
        if(event.type() == flRangeSliderEvent::CHANGE) {
            flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
            flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
        }
        
        //�J���[�X���C�_�[
        if(event.type() == flColorSliderEvent::CHANGE) {
            flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
            flColorSlider* slider = (flColorSlider*)(event.currentTarget());
        }
        
        //�W���C�X�e�B�b�N1��
        if(event.type() == flJoyStick1Event::CHANGE) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::UP) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::DOWN) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::LEFT) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::RIGHT) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        
        //�W���C�X�e�B�b�N2��
        if(event.type() == flJoyStick2Event::CHANGE) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::UP) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::DOWN) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::LEFT) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::RIGHT) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
    }
     
}

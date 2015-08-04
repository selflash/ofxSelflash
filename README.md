# ofxSelflash
=========

Copyright (c) 2015 selflash

MIT License.

Description:
--------

ofxSelflash is an Open Frameworks addon to be able to write a code like AS3 on an Open Frameworks.  

+ 'fl2d' package is classes like built-in classes of ActionScript3.0.
+ 'fl3d' package is classes that imitated classes of PaperVision3D.
+ 'tween' package is classes that imitated TweenMax API.

I'm going to commit it on this repository soon.


This addon is still in development!!!!!
The following example is unable to build.
+ example-3D-1
+ example-3D-2
+ example-3D-Deferred-1
+ example-BasicController
+ example-BlendMode
+ MovieClip
+ example-Tweener-4


Requirements
--------

Features:
--------

[fl2d.core](https://github.com/selflash/ofxSelflash/wiki/core)
+ core/Object.h

[fl2d.display](https://github.com/selflash/ofxSelflash/wiki/display)
+ display/Stage.h
+ display/MovieClip.h
+ display/Sprite.h
+ display/DisplayObjectContainer.h
+ display/InteractiveObject.h
+ display/BitmapData.h
+ display/Bitmap.h
+ display/Graphics.h
+ display/Shape.h
+ display/DisplayObject.h
+ display/BlendMode.h

[fl2d.events](https://github.com/selflash/ofxSelflash/wiki/events)
+ events/EventDispatcher.h
+ events/Event.h
+ events/SoundEvent.h
+ events/AnimationEvent.h
+ events/FocusEvent.h
+ events/MouseEvent.h
+ events/KeyboardEvent.h
+ events/SliderEvent.h
+ events/ButtonEvent.h
+ events/RadioButtonEvent.h
+ events/NumberDialerEvent.h
+ events/RangeSliderEvent.h
+ events/ColorSliderEvent.h
+ events/ColorPickerEvent.h
+ events/PadEvent.h
+ events/JoystickEvent.h
+ events/ComboBoxEvent.h

[fl2d.geom](https://github.com/selflash/ofxSelflash/wiki/geom)
+ geom/ColorTransform.h
+ geom/Matrix.h
+ geom/Particle2D.h
+ geom/Rectangle.h
+ geom/Transform.h

[fl2d.net](https://github.com/selflash/ofxSelflash/wiki/net)
+ net/Loader.h

[flash.texts](https://github.com/selflash/ofxSelflash/wiki/texts)
+ texts/Font.h
+ texts/TextField.h
+ texts/TextFieldAutoSize.h

[fl2d.ui](https://github.com/selflash/ofxSelflash/wiki/ui)
+ ui/Mouse.h
+ ui/Keyboard.h
+ ui/Button.h
+ ui/RadioButton.h
+ ui/NumberDialer.h
+ ui/Slider.h
+ ui/RangeSlider.h
+ ui/ColorSlider.h
+ ui/CircleColorPicker.h
+ ui/Pad2D.h
+ ui/Pad3D.h
+ ui/Joystick.h
+ ui/ScrollKit.h
+ ui/ComboBox.h"

fl3d.primitive  
fl3d.render  
fl3d.camera  
fl3d.light  



Getting Started
--------

- Simple example: 

```cpp
void ofApp::setup() {
    ofxSelflash::setup(false);
	//ofxSelflash::clear();

	//Stage
	flStage stage = ofxSelflash::stage();

	//DisplayObject
	flDisplayObject displayObject = new flDisplayObject();
	displayObject->name("TestDisplayObject");
    stage->addChild(displayObject);

	//Sprite
	flSprite sprite = new flSprite();
	sprite->name("TestSprite");
    sprite->mouseEnabled(false);
    stage->addChild(sprite);

    stage->removeChild(displayObject);
    stage->removeChild(sprite);
}
```

Updates:
--------
Coming soon.
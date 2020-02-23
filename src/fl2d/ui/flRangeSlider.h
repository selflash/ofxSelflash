#pragma once

#include "ofMain.h"
#include "flUIBase.h"
#include "flRangeSliderEvent.h"
#include "flmath.h"

namespace fl2d {
    
    class flRangeSlider : public flUIBase {
        
        public:
            flSprite* track = NULL;
            flSprite* minThumb = NULL;
            flSprite* maxThumb = NULL;
            flSprite* bar = NULL;
        
        protected:
        
        private:
            bool _roundEnabled = false;
            int _digit = 2;

            //DEBUGG用
            float _trackAlpha = 1.0;

            float _trackWidth = 150;
            float _trackHeight = 18;
            float _thumbWidth = 10;
            float _barWidth = 50;
        
            float _min = 0.0;
            float _max = 100.0;
            float _range = 100.0;
            float _minValue = 50.0;
            float _maxValue = 70.0;
            float _percent = 0.5;

            flTextField* _minValueText = NULL;
            flTextField* _maxValueText = NULL;

            ofPoint _draggablePoint;
        
        public:
            flRangeSlider(float trackWidth = 200, float min = 0, float max = 100, float minValue = 40, float maxValue = 60);
            virtual ~flRangeSlider();
        
            virtual void label(flTextField* value);
            virtual void enabled(bool value);
        
            bool roundEnabled();
            void roundEnabled(bool value);

            float min();
            void min(float value, bool dispatch = true);
        
            float max();
            void max(float value, bool dispatch = true);
        
            float minValue();
            void minValue(float value, bool dispatch = true);
        
            float maxValue();
            void maxValue(float value, bool dispatch = true);
        
            float range();

        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
        
            virtual void _changeValue(bool dispatch = true);

            virtual void _over();
            virtual void _barOut();
            virtual void _thumbOut();
            virtual void _barPress();
            virtual void _minThumbPress();
            virtual void _maxThumbPress();
            virtual void _release();
        
            virtual void _setNormalColor();
            virtual void _setOverColor();
            virtual void _setSelectedBarOverColor();
            virtual void _setSelectedThumbOverColor();
            virtual void _setActiveColor();
            virtual void _setDisableNormalColor();
            virtual void _setDisableActiveColor();
        
            virtual void _drawTrackGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);
            virtual void _drawBarGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness = 1.0);

        private:
            virtual void _mouseEventHandler(flEvent& event);
        
    };
}

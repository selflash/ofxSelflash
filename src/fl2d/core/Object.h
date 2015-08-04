
/**
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashObject.h
 
 */

#pragma once

#include <map>

#include "ofMain.h"

using namespace std;

//Flash2D
#define TYPE_OBJECT                      0
#define TYPE_EVENT_DISPATCHER            1
#define TYPE_DISPLAY_OBJECT              2
#define TYPE_INTERACTIVE_OBJECT          3
#define TYPE_DISPLAY_OBJECT_CONTAINER    4
#define TYPE_SPRITE                      5
#define TYPE_MOVIE_CLIP                  6
#define TYPE_STAGE                       7
#define TYPE_BITMAPDATA                  8
#define TYPE_BITMAP                      9
#define TYPE_SHAPE                      10
#define TYPE_TEXT_FIELD                 11

//Flash3D
#define TYPE_DISPLAY_OBJECT3D           12
#define TYPE_DISPLAY_OBJECT_CONTAINER3D 13
#define TYPE_SCENE3D                    14
#define TYPE_LIGHT_OBJECT3D             15
#define TYPE_CAMERA_OBJECT3D            16
#define TYPE_RENDER_ENGINE              17
#define TYPE_PLANE3D                    18
#define TYPE_CUBE3D                     19
#define TYPE_CONE3D                     20
#define TYPE_CYLINDER3D                 21
#define TYPE_ICOSPHERE3D                22
#define TYPE_SPHERE3D                   23
#define TYPE_BILLBOARD3D                24
#define TYPE_PARTICLE_SPHERE3D          25
#define TYPE_PARTICLES3D                26
#define TYPE_ROOM3D                     27
#define TYPE_LINE3D                     28
#define TYPE_RIBBON3D                   29
#define TYPE_MODEL_LOADER3D             30

namespace fl2d {
    
    class Object {
        public:
            
        protected:
            bool _debug;
            int _typeID;
            int _no;
        
            map<string, shared_ptr<void> > _properties;
        
            map<string, bool> _boolProperties;
            map<string, string> _stringProperties;
            map<string, int> _intProperties;
            map<string, float> _floatProperties;
            map<string, double> _doubleProperties;
        
        private:
            
        public:
            Object();
            ~Object();
            
            virtual bool debug();
            virtual void debug(bool value);
            
            virtual int typeID();
            
            virtual int no();
            virtual void no(int value);

            //--------------------------------------------------------------
            //
            bool getBoolProperty(string propertyName) {
                return _boolProperties[propertyName];
            }
            void setBoolProperty(string propertyName, bool value) {
                _boolProperties[propertyName] = value;
            }
        
            //--------------------------------------------------------------
            //
            string getStringProperty(string propertyName) {
                return _stringProperties[propertyName];
            }
            void setStringProperty(string propertyName, string value) {
                _stringProperties[propertyName] = value;
            }
        
            //--------------------------------------------------------------
            //
            int getIntProperty(string propertyName) {
                return _intProperties[propertyName];
            }
            void setIntProperty(string propertyName, int value) {
                _intProperties[propertyName] = value;
            }
        
            //--------------------------------------------------------------
            //
            float getFloatProperty(string propertyName) {
                return _floatProperties[propertyName];
            }
            void setFloatProperty(string propertyName, float value) {
                _floatProperties[propertyName] = value;
            }
        
            //--------------------------------------------------------------
            //
            double getDoubleProperty(string propertyName) {
                return _doubleProperties[propertyName];
            }
            void setDoubleProperty(string propertyName, double value) {
                _doubleProperties[propertyName] = value;
            }
        
            //--------------------------------------------------------------
            //
            template <class T>
            T& getProperty(string propertyName) {
//                cout << propertyName << ", " << *static_cast<T*>(_properties[propertyName]) << endl;
//                cout << propertyName << ", " << *static_cast<T*>(_properties[propertyName].get()) << endl;
                
                return *static_cast<T*>(_properties[propertyName].get());
            }
            //--------------------------------------------------------------
            //
            template <class T>
            void setProperty(string propertyName, const T* value) {
                _properties[propertyName] = shared_ptr<T>(new T(*value));
//                cout << "[Object]setProperty1(" << propertyName << ", " << *static_cast<T*>(_properties[propertyName].get()) << ")" << endl;
            }
            //--------------------------------------------------------------
            //
            template <class T>
            void setProperty(string propertyName, const T& value) {
                _properties[propertyName] = shared_ptr<T>(new T(value));

//                cout << "[Object]setProperty2(" << propertyName << ", " << *static_cast<T*>(_properties[propertyName].get()) << ")" << endl;
            }
        
        protected:
        
        private:
    };
    
}
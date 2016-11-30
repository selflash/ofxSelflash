#pragma once

#include "ofMain.h"

namespace fltw {

    template <typename Arg>
    class DelayedCallFunction {
        private:
            class Base {
                public:
                    virtual ~Base() { }
                    virtual void operator()() = 0;
            };
            Base* _pointerino;
            
            bool _assigned;
            
        public:
            template <typename Class>
            class T : public Base {
                typedef void (Class::*Func)();
                
            public:
                T(Class* listener, void (Class::*listenerMethod)()) : _listener(listener), _listenerMethod(listenerMethod) { }
                
                virtual void operator()() { return (_listener->*_listenerMethod)(); }
                
            private:
                // Pointer to the object we are delegating to.
                Class* _listener;
                // Address of the function on the delegate object.
                Func _listenerMethod;
            };
            
        public:
            
            //--------------------------------------------------------------
            //
            DelayedCallFunction() {
                _assigned = false;
                _pointerino = NULL;
            }
            //--------------------------------------------------------------
            //
            ~DelayedCallFunction() {
                /*
                 if (_assigned) {
                 //cout << "there is a pointerino" << endl;
                 delete pointerino;
                 pointerino = NULL;
                 }
                 _assigned = false;
                 */
            }
            
            //--------------------------------------------------------------
            //
            void destroy() {
                if (_assigned) {
                    //cout << "there is a pointerino" << endl;
                    delete _pointerino;
                    _pointerino = NULL;
                }
                _assigned = false;
                //cout << "deleting pointerino _assigned = " << _assigned << endl;
            }
            
            //--------------------------------------------------------------
            //
            DelayedCallFunction& operator = (Base* aPtr) {
                _pointerino = aPtr;
                _assigned = true;
                return *this;
            }
            
            //--------------------------------------------------------------
            //
            bool operator == (const bool& b) { return _assigned; }
            
            //--------------------------------------------------------------
            //
            void operator()() {
                if (_pointerino) {
                    //cout << "TweenEvent :: operator args = " << args << "  _assigned = " << _assigned << endl;
                    (*_pointerino)();
                }
            }
    };

}
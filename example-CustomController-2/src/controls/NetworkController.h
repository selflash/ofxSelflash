#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

#include "flBasicController.h"
#include "NetworkManager.h"

using namespace fl2d;

class SocketController : public flSprite {
    public:
    
    protected:
    
    private:
        UDPSocketWrapper* _socket = NULL;
    
        flButton* _button001 = NULL;
        flButton* _button002 = NULL;
        flButton* _button003 = NULL;
        flButton* _button011 = NULL;
        flButton* _button012 = NULL;
    
        flTextField* _textField001 = NULL;
        flTextField* _textField002 = NULL;
    
        flTextField* _textField101 = NULL;
        flTextField* _textField102 = NULL;
        flTextField* _textField103 = NULL;
        flTextField* _textField104 = NULL;
        flTextField* _textField105 = NULL;
        flTextField* _textField106 = NULL;
        flTextField* _textField107 = NULL;
        flTextField* _textField108 = NULL;
        flTextField* _textField109 = NULL;
        flTextField* _textField110 = NULL;
    
    public:
        SocketController();
        virtual ~SocketController();
    
        virtual string name();
        virtual void name(string value);
    
    
        //virtual void setup();
        //virtual void update();
        //virtual void draw();
    
        virtual void socket(UDPSocketWrapper* value);
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
    
    private:
        virtual void _uiEventHandler(flEvent& event);
    
    };


    class NetworkController : public flBasicController {
    public:
        
    protected:
        string _status;
        
    private:
        NetworkManager* _networkManager = NULL;
        vector<SocketController*> _socketControllers;
        SocketController* _currentSocketController = NULL;
        
    public:
        NetworkController();
        ~NetworkController();
        
        //virtual void setup();
        //virtual void update();
        //virtual void draw();
        
        virtual void networkManager(NetworkManager* value);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        virtual void _uiEventHandler(flEvent& event);
        
};


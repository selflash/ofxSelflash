#include "NativeWindow.h"

#ifdef __APPLE__

//--------------------------------------------------------------
//MAC
//--------------------------------------------------------------

#import <Cocoa/Cocoa.h>

//--------------------------------------------------------------
//
void NativeWindow::orderToDefault() {
    NSWindow *window = [NSApp mainWindow];
    
    if (window) {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [window setLevel:NSNormalWindowLevel];
        [pool release];
    }
}

//--------------------------------------------------------------
//
void NativeWindow::orderToBack() {
    NSWindow *window = [NSApp mainWindow];
    
    if (window) {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [window setLevel:NSNormalWindowLevel - 1];
        [pool release];
    }
}

//--------------------------------------------------------------
//
void NativeWindow::orderToFront() {
    NSWindow *window = [NSApp mainWindow];
    
    if (window) {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [window setLevel:NSFloatingWindowLevel];
        [pool release];
    }
}

#elif defined _WIN32

//--------------------------------------------------------------
//WINDOWS
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void NativeWindow::orderToDefault() {
    
}

//--------------------------------------------------------------
//
void NativeWindow::orderToBack() {

}

//--------------------------------------------------------------
//
void NativeWindow::orderToFront() {

}

#endif

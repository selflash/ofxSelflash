#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
//    ofGLWindowSettings settings;
//    settings.width = 1024;
//    settings.height = 768;
//    settings.windowMode = OF_WINDOW;
//    settings.setGLVersion(4, 1);
//    ofCreateWindow(settings);

	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

    cout << "Vendor     : " << glGetString(GL_VENDOR) << '\n';
    cout << "GPU        : " << glGetString(GL_RENDERER) << '\n';
    cout << "OpenGL ver : " << glGetString(GL_VERSION) << '\n';
    cout << "GLSL ver   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

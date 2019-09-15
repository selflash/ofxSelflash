#include "ofApp.h"
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	ofGLFWWindowSettings settings;
	settings.setSize(1920, 1080);
	//settings.setGLVersion(2, 1); // GL2

	//settings.setSize(1280 * 0.5 * 3, 720);
	settings.setGLVersion(3, 2); // GL3
	//settings.setGLVersion(4, 1); // GL4

	ofCreateWindow(settings);

	//-------------------------------
	cout << "Vendor     : " << glGetString(GL_VENDOR) << '\n';
	cout << "GPU        : " << glGetString(GL_RENDERER) << '\n';
	cout << "OpenGL ver : " << glGetString(GL_VERSION) << '\n';
	cout << "GLSL ver   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	int maxVertexTextureImageUnits;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits);
	cout << "MaxVertexTextureImageUnits   : " << maxVertexTextureImageUnits << '\n';

	int maxCombinedTextureImageUnits;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
	cout << "MaxVertexTextureImageUnits   : " << maxCombinedTextureImageUnits << '\n';
	//-------------------------------

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}

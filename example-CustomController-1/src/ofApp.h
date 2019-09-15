#pragma once

#include "Define.h"

#include "ofMain.h"
#include "ofxAzureKinectDK.h"
#include "ofxCv.h"
#include "ofxSelflash.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/aruco/charuco.hpp>
//#include <opencv2/aruco/dictionary.hpp>

#include "DeviceWrapper.h"
#include "MarkerDetector.h"
#include "PoseEstimater.h"

#include "AppEngine.h"
#include "MainController.h"
#include "NetworkManager.h"

#ifdef _DEBUG_MEASURE_PROCESS_TIME
#include "ofxTimeMeasurements.h"
#endif

using namespace glm;
using namespace cv;

#define NUM_PARTICLES 50*4

class ofApp : public ofBaseApp
{
	public:
		bool debug = false;
		int installedCount = 0;
		//ofEasyCam camera;

		int numKinect = 1;

		DeviceWrapper* masterKinect = 0;

		vec3 tempVec3;
		vec2 tempPoints2d[4] = { };
		vec3 tempPoints3d[4] = { };

		vec3 groundMarkerPoints[4];
		vec3 groundCenter;
		vec3 groundAxisX;
		vec3 groundAxisY;
		vec3 groundAxisZ;


		vec3 markerCenter;
		vec3 markerAxisX;
		vec3 markerAxisY;
		vec3 markerAxisZ;

		DeviceWrapper kinect1;
		MarkerDetector markerDetector1;
		vec3 markerPoints1[4] = { };
		bool detectedMarker1 = false;
		ofPolyline polyline1;


		bool isCalibrating = false;
		DeviceWrapper kinect2;
		MarkerDetector markerDetector2;
		vec3 markerPoints2[4] = { };
		bool detectedMarker2 = false;
		ofPolyline polyline2;

		DeviceWrapper kinect3;
		MarkerDetector markerDetector3;
		vec3 markerPoints3[4] = { };
		bool detectedMarker3 = false;
		ofPolyline polyline3;

		ofVbo pointCloudVbo;

		ofTexture depthBufferTexture;
		ofFbo fbo;
		ofTexture depthTex;
		ofShader compositeShader;
		ofShader visualizeColorShader;
		ofShader visualizeDepthShader;

		PoseEstimater poseEstimater;

		enum CalibrationMode {
			None,
			Device2ToDevice1,
			Device3ToDevice1,
			Ground
		};
		CalibrationMode calibrationMode = None;

		enum ViewerMode {
			All,
			Device1AndDevice2,
			Device1AndDevice3,
			Device2AndDevice3
		};
		ViewerMode viewerMode = All;

		bool showKinect1 = true;
		bool showKinect2 = true;
		bool showKinect3 = true;

		bool showColorImage = false;
		bool showPointCloud = true;
		bool showCalibrationPoints = false;

		ofVbo vbo1;
		ofFloatColor calibPointsColor1[NUM_PARTICLES];
		vec3 calibPoints1[NUM_PARTICLES];
		ofVbo vbo2;
		ofFloatColor calibPointsColor2[NUM_PARTICLES];
		vec3 calibPoints2[NUM_PARTICLES];
		ofVbo vbo3;
		ofFloatColor calibPointsColor3[NUM_PARTICLES];
		vec3 calibPoints3[NUM_PARTICLES];

		bool showUI = false;

		MainController* mainController;
		NetworkManager* networkManager;

		//---------------------
		//ƒ}ƒEƒX‚É‚æ‚é‰ñ“]
		ofQuaternion _globalRotation;
		ofVec2f _lastMouse;
		float _dampen = 0.4;
		//---------------------
	private:

	public:
		void setup();
		void exit();
		void update();
		void draw();
		void drawColorImage();
		void drawPointCloud();
		void drawMarkers();
		void drawCalibrationPoints();
		void drawInfo();

		void startCalibration();
		void endCalibration();
		//void applyMatrix();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		void _eventHandler(flEvent& event);
};

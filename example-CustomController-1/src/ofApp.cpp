#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
#ifdef _DEBUG_MEASURE_PROCESS_TIME
	TIME_SAMPLE_SET_FRAMERATE(60.0f);
#endif

	ofSetFrameRate(60);
	ofSetVerticalSync(true);


	//----------------------------------
	Config::loadConfigXml();
	if (Config::mode != "release") {
//        Config::inputFolderPath = "input";
//        Config::outputFolderPath = "output";
	}
	//ofSetWindowTitle("Multiple Azure Kinect");


	AppEngine::setup();
	//--------------------------------------
	//ネットワークマネージャー
	networkManager = AppEngine::networkManager();
	//    _networkManager->addEventListener(NetworkEvent::RECEIVED, this, &ofApp::_networkEventHandler);
	//networkManager->addEventListener("udp0Received", this, &ofApp::_networkEventHandler);
	//ネットワーク
	//バッチ処理用
	//networkManager->bindWithUDP(0, Config::udp_local_port0);
	//--------------------------------------
	ofxSelflash::setup();
	flStage* stage = ofxSelflash::stage();
	stage->addEventListener(flFocusEvent::FOCUS_IN, this, &ofApp::_eventHandler);
	stage->addEventListener(flFocusEvent::FOCUS_OUT, this, &ofApp::_eventHandler);

	//--------------------------------------
	mainController = new MainController();
	mainController->setup();
	mainController->x(1);
	mainController->y(ofGetHeight() - mainController->height() - 1);
	stage->addChild(mainController);
	//ネットワークコントローラーにネットワークマネージャーをセットする
	((NetworkController*)mainController->controller0())->networkManager(AppEngine::networkManager());

	//AppEngine::controller((flBasicController*)mainController);
	//--------------------------------------


	{
		//1辺の長さ
		float n = 215.0f / 2.0f; //21.5cm / 2
		//groundMarkerPoints[0] = vec3(n, 0, n);
		//groundMarkerPoints[1] = vec3(n, 0, -n);
		//groundMarkerPoints[2] = vec3(-n, 0, -n);
		//groundMarkerPoints[3] = vec3(-n, 0, n);
		groundMarkerPoints[0] = vec3(n, 0, -n);
		groundMarkerPoints[1] = vec3(n, 0, n);
		groundMarkerPoints[2] = vec3(-n, 0, n);
		groundMarkerPoints[3] = vec3(-n, 0, -n);


		//groundMarkerPoints[0] = vec3(209.33, 31.0164, 2548);
		//groundMarkerPoints[1] = vec3(129.624, 152.349, 2386);
		//groundMarkerPoints[2] = vec3(- 61.6326, 97.8434, 2450);
		//groundMarkerPoints[3] = vec3(17.1883, -20.0228, 2605);

		const ofVec3f& p1 = groundMarkerPoints[0];
		const ofVec3f& p2 = groundMarkerPoints[1];
		const ofVec3f& p3 = groundMarkerPoints[2];
		const ofVec3f& p4 = groundMarkerPoints[3];
		groundCenter = (p1 + p2 + p3 + p4) / 4.0f;
		groundAxisX = (p1 + p2) / 2.0f;
		groundAxisZ = (p2 + p3) / 2.0f;
		groundAxisY = groundCenter + ofxANATOMe::getNormal(p1, p3, p2) * 100;
	}

	{
		for (int i = 0; i < NUM_PARTICLES; i++) {
			calibPoints1[i] = vec3(0, 0, 0);
			calibPointsColor1[i].set(1, 0, 0, 0);
		}
		vbo1.setVertexData(calibPoints1, NUM_PARTICLES, GL_DYNAMIC_DRAW);
		vbo1.setColorData(calibPointsColor1, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	}
	{
		for (int i = 0; i < NUM_PARTICLES; i++) {
			calibPoints2[i] = vec3(0, 0, 0);
			calibPointsColor2[i].set(0, 1, 0, 0);
		}
		vbo2.setVertexData(calibPoints2, NUM_PARTICLES, GL_DYNAMIC_DRAW);
		vbo2.setColorData(calibPointsColor2, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	}
	{
		for (int i = 0; i < NUM_PARTICLES; i++) {
			calibPoints3[i] = vec3(0, 0, 0);
			calibPointsColor3[i].set(0, 0, 1, 0);
		}
		vbo3.setVertexData(calibPoints3, NUM_PARTICLES, GL_DYNAMIC_DRAW);
		vbo3.setColorData(calibPointsColor3, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	}

	//ofSetLogLevel(OF_LOG_VERBOSE);
	installedCount = ofxAzureKinectDK::Device::getInstalledCount();
	//ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinectDK::Device::getInstalledCount() << " installed devices.";
	cout << "Found " << installedCount << " installed devices." << endl;

	//camera.setDistance(500.f);
	//camera.setPosition(0.f, 0.f, 500.f);
	//camera.lookAt(mesh.getCentroid(), ofVec3f(0.f, 1.f, 0.f));
	//camera.setNearClip(0.0001);
	//camera.setFarClip(100000000);
	//camera.setNearClip(0.0001);
	//camera.setFarClip(100000);
	//cout << "Camera FOV = " << camera.getFov() << endl;

	if (numKinect >= 1) {
		//kinect1.camera.setPosition(0.f, 0.f, 2000.f);
		kinect1.setup();
		if (kinect1.open(0)) {
			if (kinect1.isMasterDevice()) {
				masterKinect = &kinect1;
			}
			else {
				if (kinect1.startCameras(K4A_WIRED_SYNC_MODE_SUBORDINATE)) {
					cout << "this kinect(" + kinect1.device.getSerialNum() + ") has started." << endl;
				}
			}
		}
	}
	if (numKinect >= 2) {
		//kinect2.camera.setPosition(0.f, 0.f, 2000.f);
		kinect2.setup();
		if (kinect2.open(1)) {
			if (kinect2.isMasterDevice()) {
				masterKinect = &kinect2;
			}
			else {
				if (kinect2.startCameras(K4A_WIRED_SYNC_MODE_SUBORDINATE)) {
					cout << "this kinect(" + kinect2.device.getSerialNum() + ") has started." << endl;
				}
			}
		}
	}
	if (numKinect >= 3) {
		//kinect3.camera.setPosition(0.f, 0.f, 2000.f);
		kinect3.setup();
		if (kinect3.open(2)) {
			if (kinect3.isMasterDevice()) {
				masterKinect = &kinect3;
			}
			else {
				if (kinect3.startCameras(K4A_WIRED_SYNC_MODE_SUBORDINATE)) {
					cout << "this kinect(" + kinect3.device.getSerialNum() + ") has started." << endl;
				}
			}
		}
	}

	if (masterKinect == NULL) {
		cout << "Master kinect has not found." << endl;
	}
	else {
		if (masterKinect->startCameras(K4A_WIRED_SYNC_MODE_MASTER)) {
			cout << "Master kinect(" + masterKinect->device.getSerialNum() + ") has started." << endl;
		}
	}

	//kinectA.camera.enableMouseInput();
	//if (!single) kinectB.camera.disableMouseInput();

	for (int i = 0; i < 5; i++) {
		polyline1.addVertex(glm::vec3());
		polyline2.addVertex(glm::vec3());
		polyline3.addVertex(glm::vec3());
	}

	poseEstimater.setup();


	//Setup fbo
	//ofEnableArbTex();
	//ofFboSettings fboSettings;
	//fboSettings.width = ofGetWidth();
	//fboSettings.height = ofGetHeight();
	//fboSettings.internalformat = GL_RGBA;
	//fboSettings.useDepth = true;
	//fboSettings.useStencil = false;
	//fboSettings.depthStencilAsTexture = true;
	//fboSettings.numSamples = 0; // depthStencilAsTextureとmultiSamplingは一緒に使えない！！
	//fboSettings.depthStencilInternalFormat = GL_DEPTH_COMPONENT;
	////fboSettings.textureTarget = GL_TEXTURE_2D;

	//fbo.allocate(fboSettings);
	//fbo.checkStatus();
	//fbo.checkGLSupport();
	//ofDisableArbTex();

	ofFbo::Settings s;
	s.width = ofGetWidth();
	s.height = ofGetHeight();
	s.useDepth = true;
	s.depthStencilAsTexture = true;
	fbo.allocate(s);
	fbo.begin();
	ofClear(0);
	fbo.end();

	visualizeColorShader.load("shaders/gl3/visualize_color");
	visualizeDepthShader.load("shaders/gl3/visualize_depth");

	if (numKinect >= 1) {
		compositeShader.load("shaders/gl3/composite_1");
	}
	if (numKinect >= 2) {
		compositeShader.load("shaders/gl3/composite_2");
	}
	if (numKinect >= 3) {
		compositeShader.load("shaders/gl3/composite");
	}
}

//--------------------------------------------------------------
void ofApp::exit()
{
	if (numKinect >= 1) kinect1.close();
	if (numKinect >= 2) kinect2.close();
	if (numKinect >= 3) kinect3.close();
}

//--------------------------------------------------------------
void ofApp::update()
{		
	{
#ifdef _DEBUG_MEASURE_PROCESS_TIME
		TS_SCOPE("kinects.update()");
#endif
		if (numKinect >= 1) kinect1.update();
		if (numKinect >= 2) kinect2.update();
		if (numKinect >= 3) kinect3.update();
	}

	{
#ifdef _DEBUG_MEASURE_PROCESS_TIME
		TS_SCOPE("calibration()");
#endif

		//Kinect1
		if (
			isCalibrating &&
			calibrationMode == Device2ToDevice1 ||
			calibrationMode == Device3ToDevice1 ||
			calibrationMode == Ground
			)
		{
			detectedMarker1 = false;

			const ofPixels& colorInDepthPix = kinect1.device.getColorInDepthPix();
			const size_t width = colorInDepthPix.getWidth();
			const size_t height = colorInDepthPix.getHeight();
			if (markerDetector1.findMarker(colorInDepthPix, width, height, tempPoints2d)) {
				int i = 0;
				for (const auto& p : tempPoints2d) {
					if (kinect1.device.depthToWorld(p.x, p.y, tempVec3)) {
						tempPoints3d[i] = tempVec3;
					}
					i++;
				}

				if (MarkerDetector::checkAngle(tempPoints3d)) {
					int i = 0;
					for (const auto& p : tempPoints3d) {
						markerPoints1[i] = p;
						i++;
					}

					detectedMarker1 = true;
				};
			}
		}

		//Kinect2
		if (
			isCalibrating &&
			calibrationMode == Device2ToDevice1
			)
		{
			detectedMarker2 = false;

			const ofPixels& colorInDepthPix = kinect2.device.getColorInDepthPix();
			const size_t width = colorInDepthPix.getWidth();
			const size_t height = colorInDepthPix.getHeight();
			if (markerDetector2.findMarker(colorInDepthPix, width, height, tempPoints2d)) {
				int i = 0;
				for (const auto& p : tempPoints2d) {
					if (kinect2.device.depthToWorld(p.x, p.y, tempVec3)) {
						tempPoints3d[i] = tempVec3;
					}
					i++;
				}

				if (MarkerDetector::checkAngle(tempPoints3d)) {
					int i = 0;
					for (const auto& p : tempPoints3d) {
						markerPoints2[i] = p;
						i++;
					}

					detectedMarker2 = true;
				};
			}
		}

		//Kinect3
		if (
			isCalibrating &&
			calibrationMode == Device3ToDevice1
			)
		{
			detectedMarker3 = false;

			const ofPixels& colorInDepthPix = kinect3.device.getColorInDepthPix();
			const size_t width = colorInDepthPix.getWidth();
			const size_t height = colorInDepthPix.getHeight();
			if (markerDetector3.findMarker(colorInDepthPix, width, height, tempPoints2d)) {
				int i = 0;
				for (const auto& p : tempPoints2d) {
					if (kinect3.device.depthToWorld(p.x, p.y, tempVec3)) {
						tempPoints3d[i] = tempVec3;
					}
					i++;
				}

				if (MarkerDetector::checkAngle(tempPoints3d)) {
					int i = 0;
					for (const auto& p : tempPoints3d) {
						markerPoints3[i] = p;
						i++;
					}

					detectedMarker3 = true;
				};
			}
		}









		//const vector<ofVec3f>& corrers = poseEstimater.corners12_1;
		//int i = 0;
		//float sum = 0;
		//int l = corrers.size();
		//for (int i = 0; i < l; i += 4) {
		//	ofVec3f p1 = corrers[i];
		//	ofVec3f p2 = corrers[i + 1];
		//	float diff = p1.distance(p2);
		//	sum += diff;
		//}
		//sum /= (float)l;
		//cout << "sum = " << sum << endl;



		//for (int i = 0; i < 4; i++) {
		//	const ofVec3f& p = markerPoints1[i];
		//	cout << ofToString(i) + " \n" << p << endl;
		//}

		if (calibrationMode != Ground) {
			if (
				isCalibrating &&
				calibrationMode == Device2ToDevice1
				) {
				if (detectedMarker1 && detectedMarker2) {
					for (auto p : markerPoints1) {
						poseEstimater.corners12_1.push_back(p);
					}
					for (auto p : markerPoints2) {
						poseEstimater.corners12_2.push_back(p);
					}

					//VBO
					{
						int l = poseEstimater.corners12_1.size();
						for (int i = 0; i < NUM_PARTICLES; i++) {
							if (i < l) {
								calibPoints1[i] = poseEstimater.corners12_1[i];
								calibPointsColor1[i].a = 1;
							}
							else {
								calibPointsColor1[i].a = 0;
							}
						}
						vbo1.updateVertexData(calibPoints1, NUM_PARTICLES);
						vbo1.updateColorData(calibPointsColor1, NUM_PARTICLES);
					}
					{
						int l = poseEstimater.corners12_2.size();
						for (int i = 0; i < NUM_PARTICLES; i++) {
							if (i < l) {
								calibPoints2[i] = poseEstimater.corners12_2[i];
								calibPointsColor2[i].a = 1;
							}
							else {
								calibPointsColor2[i].a = 0;
							}
						}
						vbo2.updateVertexData(calibPoints2, NUM_PARTICLES);
						vbo2.updateColorData(calibPointsColor2, NUM_PARTICLES);
					}

					if (poseEstimater.corners12_1.size() >= NUM_PARTICLES) {
						endCalibration();
					}
				}
			}
			else if (
				isCalibrating &&
				calibrationMode == Device3ToDevice1
				) {
				if (detectedMarker1 && detectedMarker3) {
					for (auto p : markerPoints1) {
						poseEstimater.corners13_1.push_back(p);
					}
					for (auto p : markerPoints3) {
						poseEstimater.corners13_3.push_back(p);
					}

					//VBO
					{
						int l = poseEstimater.corners13_1.size();
						for (int i = 0; i < NUM_PARTICLES; i++) {
							if (i < l) {
								calibPoints1[i] = poseEstimater.corners13_1[i];
								calibPointsColor1[i].a = 1;
							}
							else {
								calibPointsColor1[i].a = 0;
							}
						}
						vbo1.updateVertexData(calibPoints1, NUM_PARTICLES);
						vbo1.updateColorData(calibPointsColor1, NUM_PARTICLES);
					}
					{
						int l = poseEstimater.corners13_3.size();
						for (int i = 0; i < NUM_PARTICLES; i++) {
							if (i < l) {
								calibPoints3[i] = poseEstimater.corners13_3[i];
								calibPointsColor3[i].a = 1;
							}
							else {
								calibPointsColor3[i].a = 0;
							}
						}
						vbo3.updateVertexData(calibPoints3, NUM_PARTICLES);
						vbo3.updateColorData(calibPointsColor3, NUM_PARTICLES);
					}

					if (poseEstimater.corners13_1.size() >= NUM_PARTICLES) {
						endCalibration();
					}
				}
			}
			else if (
				isCalibrating &&
				calibrationMode == Ground
				) {
				if (detectedMarker1) {
					const ofVec3f& p1 = markerPoints1[0];
					const ofVec3f& p2 = markerPoints1[1];
					const ofVec3f& p3 = markerPoints1[2];
					const ofVec3f& p4 = markerPoints1[3];
					markerCenter = (p1 + p2 + p3 + p4) / 4.0f;
					markerAxisX = (p1 + p2) / 2.0f;
					markerAxisZ = (p2 + p3) / 2.0f;
					markerAxisY = markerCenter + ofxANATOMe::getNormal(p1, p3, p2) * 100;
				}


				//if (detectedMarker1) {
				//	for (auto p : groundMarkerPoints) {
				//		p.x += ofRandomf();
				//		p.y += ofRandomf();
				//		p.z += ofRandomf();
				//		poseEstimater.corners01_0.push_back(p);
				//	}
				//	for (auto p : markerPoints1) {
				//		poseEstimater.corners01_1.push_back(p);
				//	}

				//	if (poseEstimater.corners01_1.size() >= NUM_PARTICLES) {
				//		endCalibration();
				//	}
				//}
			}
		}

		//if (isCalibrating) {
		//	applyMatrix();
		//}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(128);

	//-------------------------------
	if (showPointCloud) {
		drawPointCloud();
	}

	if (showCalibrationPoints) {
		drawCalibrationPoints();
	}

	if (showColorImage) {
		drawColorImage();
	}

	if (isCalibrating) {
		drawMarkers();
	}


	if (calibrationMode == Ground) {
		kinect1.camera.begin();
		ofDisableDepthTest();

		const vec3& p1 = groundMarkerPoints[0];
		const vec3& p2 = groundMarkerPoints[1];
		const vec3& p3 = groundMarkerPoints[2];
		const vec3& p4 = groundMarkerPoints[3];

		ofPushStyle();
		ofSetColor(255, 0, 0, 255);
		//ofSetLineWidth(10);
		ofDrawLine(p1, p2);
		ofDrawLine(p2, p3);
		ofDrawLine(p3, p4);
		ofDrawLine(p4, p1);

		ofSetColor(255, 0, 0, 255);
		ofDrawSphere(p1, 8);
		ofSetColor(0, 255, 0, 255);
		ofDrawSphere(p2, 8);
		ofSetColor(0, 0, 255, 255);
		ofDrawSphere(p3, 8);
		ofSetColor(255, 0, 255, 255);
		ofDrawSphere(p4, 8);

		//Draw Axis
		ofSetColor(255, 0, 0, 255);
		ofDrawArrow(markerCenter, markerAxisX);
		ofSetColor(0, 255, 0, 255);
		ofDrawArrow(markerCenter, markerAxisY);
		ofSetColor(0, 0, 255, 255);
		ofDrawArrow(markerCenter, markerAxisZ);


		//Draw Ground Axis
		ofSetColor(255, 0, 0, 255);
		ofDrawArrow(groundCenter, groundAxisX);
		ofSetColor(0, 255, 0, 255);
		ofDrawArrow(groundCenter, groundAxisY);
		ofSetColor(0, 0, 255, 255);
		ofDrawArrow(groundCenter, groundAxisZ);

		ofPopStyle();

		kinect1.camera.end();
	}
	//-------------------------------

	if (ofGetKeyPressed('j')) {
		kinect1.drawPositionMap();
	}

	ofxSelflash::draw();

	if (showUI) {
		drawInfo();
	}
}

//--------------------------------------------------------------
void ofApp::drawInfo() {
	ofDrawBitmapStringHighlight("FPS : " + ofToString(ofGetFrameRate(), 2), 10, 20);
	ofDrawBitmapStringHighlight("Installed Count : " + ofToString(installedCount), 10, 40);
	ofDrawBitmapStringHighlight("Show Color Image : " + ofToString(showColorImage ? "True" : "False"), 10, 60);
	ofDrawBitmapStringHighlight("Show Point Cloud : " + ofToString(showPointCloud ? "True" : "False"), 10, 80);
	ofDrawBitmapStringHighlight("Show Calibration Points : " + ofToString(showCalibrationPoints ? "True" : "False"), 10, 100);

	int iy = 120;
	if (viewerMode == Device1AndDevice2)
	{
		ofDrawBitmapStringHighlight("Is Calibrating = " + ofToString(isCalibrating ? "True" : "False"), 10, iy + 20 * 0);
		ofDrawBitmapStringHighlight("Detected Maker On Kinect1 = " + ofToString(detectedMarker1 ? "True" : "False"), 10, iy + 20 * 1);
		ofDrawBitmapStringHighlight("Detected Maker On Kinect2 = " + ofToString(detectedMarker2 ? "True" : "False"), 10, iy + 20 * 2);
		const auto& corners1 = poseEstimater.corners12_1;
		ofDrawBitmapStringHighlight("corners12_1.size = " + ofToString(corners1.size()), 10, iy + 20 * 3);
		const auto& corners2 = poseEstimater.corners12_2;
		ofDrawBitmapStringHighlight("corners12_2.size = " + ofToString(corners2.size()), 10, iy + 20 * 4);
	}
	if (viewerMode == Device1AndDevice3)
	{
		ofDrawBitmapStringHighlight("Is Calibrating = " + ofToString(isCalibrating ? "True" : "False"), 10, iy + 20 * 0);
		ofDrawBitmapStringHighlight("Detected Maker On Kinect1 = " + ofToString(detectedMarker1 ? "True" : "False"), 10, iy + 20 * 1);
		ofDrawBitmapStringHighlight("Detected Maker On Kinect3 = " + ofToString(detectedMarker3 ? "True" : "False"), 10, iy + 20 * 2);
		const auto& corners1 = poseEstimater.corners13_1;
		ofDrawBitmapStringHighlight("corners13_1.size = " + ofToString(corners1.size()), 10, iy + 20 * 3);
		const auto& corners2 = poseEstimater.corners13_3;
		ofDrawBitmapStringHighlight("corners13_3.size = " + ofToString(corners2.size()), 10, iy + 20 * 4);
	}
	if (viewerMode == All)
	{
		ofDrawBitmapStringHighlight("Is Calibrating = " + ofToString(isCalibrating ? "True" : "False"), 10, iy + 20 * 0);
		ofDrawBitmapStringHighlight("Detected Maker On Kinect1 = " + ofToString(detectedMarker1 ? "True" : "False"), 10, iy + 20 * 1);
		//ofDrawBitmapStringHighlight("Detected Maker On Kinect3 = " + ofToString(detectedMarker3 ? "True" : "False"), 10, iy + 20 * 2);
		const auto& corners1 = poseEstimater.corners01_0;
		ofDrawBitmapStringHighlight("corners01_0.size = " + ofToString(corners1.size()), 10, iy + 20 * 3);
		const auto& corners2 = poseEstimater.corners01_1;
		ofDrawBitmapStringHighlight("corners01_1.size = " + ofToString(corners2.size()), 10, iy + 20 * 4);
	}
}

//--------------------------------------------------------------
void ofApp::drawColorImage() {
	//Draw Kinect1
	if (
		numKinect >= 1 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device1AndDevice3
		)
	{
		ofPushMatrix();
		ofScale(0.5, 0.5);
		kinect1.drawColorImage();
		ofPopMatrix();
	}

	//Draw Kinect2
	if (
		numKinect >= 2 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device2AndDevice3
		)
	{
		ofPushMatrix();
		ofScale(0.5, 0.5);
		ofTranslate(kinect1.colorWidth, 0);
		kinect2.drawColorImage();
		ofPopMatrix();
	}

	//Draw Kinect3
	if (
		numKinect >= 3 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice3 ||
		viewerMode == Device2AndDevice3
		)
	{
		ofPushMatrix();
		ofScale(0.5, 0.5);
		ofTranslate(kinect1.colorWidth + kinect2.colorWidth, 0);
		kinect3.drawColorImage();
		ofPopMatrix();
	}
	//-------------------------------
}

//--------------------------------------------------------------
void ofApp::drawPointCloud() {
	//fbo.begin();
	//ofClear(0);

	//-------------------------------
	//camera.begin();
	//ofEnableDepthTest();

	//ofSetColor(255, 0, 0);
	//ofIcoSpherePrimitive(400, 2).draw();
	////ofSetColor(0, 255, 0);
	////ofDrawIcoSphere(200, -200, 200, 50);



	//glPointSize(1);
	//int numVertices = pointCloudVbo.getNumVertices();
	//pointCloudVbo.draw(GL_POINTS, 0, numVertices);
	//Draw Kinect1
	if (
		numKinect >= 1 &&
		showKinect1 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device1AndDevice3
		)
	{
		kinect1.drawPointCloud();
	}

	//Draw Kinect2
	if (
		numKinect >= 2 &&
		showKinect2 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device2AndDevice3
		)
	{
		kinect2.drawPointCloud();
	}

	//Draw Kinect3
	if (
		numKinect >= 3 &&
		showKinect3 &&
		viewerMode == All ||
		viewerMode == Device1AndDevice3 ||
		viewerMode == Device2AndDevice3
		)
	{
		kinect3.drawPointCloud();
	}

	//ofDisableDepthTest();
	//camera.end();
	//-------------------------------

	//fbo.end();

	//if (ofGetKeyPressed('p')) {
	//	visualizeColorShader.begin();
	//	visualizeColorShader.setUniformTexture("tex0", kinect1.fbo.getTexture(), 1);
	//	kinect1.fbo.draw(0, 0);
	//	visualizeColorShader.end();
	//}
	//else if (ofGetKeyPressed('o')) {
	//	visualizeDepthShader.begin();
	//	visualizeDepthShader.setUniformTexture("tex0", kinect1.fbo.getDepthTexture(), 1);
	//	kinect1.fbo.draw(0, 0);
	//	visualizeDepthShader.end();
	//}
	//else
	{
		compositeShader.begin();
		if (numKinect >= 1) {
			compositeShader.setUniformTexture("colorTex1", kinect1.fbo.getTexture(), 1);
			compositeShader.setUniformTexture("depthTex1", kinect1.fbo.getDepthTexture(), 2);
		}
		if (numKinect >= 2) {
			compositeShader.setUniformTexture("colorTex2", kinect2.fbo.getTexture(), 3);
			compositeShader.setUniformTexture("depthTex2", kinect2.fbo.getDepthTexture(), 4);
		}
		if (numKinect >= 3) {
			compositeShader.setUniformTexture("colorTex3", kinect3.fbo.getTexture(), 5);
			compositeShader.setUniformTexture("depthTex3", kinect3.fbo.getDepthTexture(), 6);
		}
		fbo.draw(0, 0);
		compositeShader.end();

		//int w = ofGetWidth();
		//int h = ofGetHeight();

		//ofPushMatrix();
		//ofScale(0.5, 0.5);
		//ofTranslate(0, 0);
		//kinect1.fbo.draw(0, 0);

		//ofTranslate(w, 0);
		//kinect2.fbo.draw(0, 0);

		//ofTranslate(w * 2, 0);
		////kinect3.fbo.draw(0, 0);

		//ofPopMatrix();
	}

	//if (ofGetKeyPressed('v')) {
	//	depthBufferTexture = fbo.getDepthTexture();
	//	ofBufferObject buffer;
	//	buffer.allocate(ofGetWidth() * ofGetHeight() * 2, GL_STATIC_READ);
	//	depthBufferTexture.copyTo(buffer);
	//	unsigned char* f = buffer.map<unsigned char>(GL_READ_ONLY);

	//	ofPixels pixels;
	//	pixels.allocate(ofGetWidth(), ofGetHeight(), ofImageType::OF_IMAGE_COLOR_ALPHA);
	//	for (int i = 0; i < ofGetHeight(); i++) {
	//		for (int j = 0; j < ofGetWidth(); j++) {
	//			int idx = (i * ofGetWidth() + j) * 2;
	//			uint16_t ret;
	//			ret = f[idx];
	//			ret |= f[idx + 1] << 8;

	//			float v = (float)(ret) / 0xffff;

	//			pixels.setColor(j, i, ofFloatColor(v, v, v, 255));
	//		}
	//	}
	//	ofSaveImage(pixels, "bufferFloat.png");
	//}


	//depthBufferTexture = fbo.getDepthTexture();
	//ofBufferObject buffer;
	//buffer.allocate(ofGetWidth() * ofGetHeight() * 2, GL_STATIC_READ);
	//depthBufferTexture.copyTo(buffer);
	//unsigned char* f = buffer.map<unsigned char>(GL_READ_ONLY);

	//ofPixels pixels;
	//pixels.allocate(ofGetWidth(), ofGetHeight(), ofImageType::OF_IMAGE_COLOR_ALPHA);
	//for (int i = 0; i < ofGetHeight(); i++) {
	//	for (int j = 0; j < ofGetWidth(); j++) {
	//		int idx = (i * ofGetWidth() + j) * 2;
	//		uint16_t ret;
	//		ret = f[idx];
	//		ret |= f[idx + 1] << 8;

	//		float v = (float)(ret) / 0xffff;

	//		pixels.setColor(j, i, ofFloatColor(v, v, v, 255));
	//	}
	//}

	//depthTex.readToPixels(pixels);
	//depthTex.draw(0, 0);



	//if (ofGetKeyPressed('r')) {
	//	ofPixels pixels;
	//	fbo.readToPixels(pixels);
	//	ofSaveImage(pixels, "pixels.png");
	//}
	//if (ofGetKeyPressed('d')) {
	//	ofTexture texture = fbo.getDepthTexture();
	//	ofPixels pixels;
	//	texture.readToPixels(pixels);
	//	ofSaveImage(pixels, "depth.png");
	//}
	//if (ofGetKeyPressed('b')) {
	//	depthBufferTexture = fbo.getDepthTexture();
	//	ofBufferObject buffer;
	//	buffer.allocate(ofGetWidth() * ofGetHeight() * 4, GL_STATIC_READ);
	//	depthBufferTexture.copyTo(buffer);
	//	unsigned char* f = buffer.map<unsigned char>(GL_READ_ONLY);
	//	ofPixels pixels;
	//	pixels.setFromExternalPixels(f, ofGetWidth(), ofGetHeight(), 4);
	//	ofSaveImage(pixels, "buffer.png");
	//}
}

//--------------------------------------------------------------
void ofApp::drawMarkers() {
	auto drawMarker = [](DeviceWrapper& kinect, const vec3 markerPoints[4], const ofColor& color)->void {
		kinect.camera.begin();
		ofDisableDepthTest();

		const vec3& p1 = markerPoints[0];
		const vec3& p2 = markerPoints[1];
		const vec3& p3 = markerPoints[2];
		const vec3& p4 = markerPoints[3];

		ofPushStyle();
		ofSetColor(255, 0, 0, 255);
		//ofSetLineWidth(10);
		ofDrawLine(p1, p2);
		ofDrawLine(p2, p3);
		ofDrawLine(p3, p4);
		ofDrawLine(p4, p1);

		ofSetColor(255, 0, 0, 255);
		ofDrawSphere(p1, 8);
		ofSetColor(0, 255, 0, 255);
		ofDrawSphere(p2, 8);
		ofSetColor(0, 0, 255, 255);
		ofDrawSphere(p3, 8);
		ofSetColor(255, 0, 255, 255);
		ofDrawSphere(p4, 8);
		ofPopStyle();

		kinect.camera.end();
	};

	//KinectA
	if (
		numKinect >= 1 &&
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device1AndDevice3 ||
		calibrationMode == Ground &&
		detectedMarker1
		)
	{
		drawMarker(kinect1, markerPoints1, ofColor(255, 0, 0, 255));
	}

	//KinectB
	if (
		numKinect >= 2 &&
		viewerMode == Device1AndDevice2 &&
		detectedMarker2
		)
	{
		drawMarker(kinect2, markerPoints2, ofColor(255, 0, 0, 255));
	}

	//KinectC
	if (
		numKinect >= 3 &&
		viewerMode == Device1AndDevice3 &&
		detectedMarker3
		)
	{
		drawMarker(kinect3, markerPoints3, ofColor(255, 0, 0, 255));
	}
}

//--------------------------------------------------------------
void ofApp::drawCalibrationPoints() {
	//KinectA
	if (
		numKinect >= 1 &&
		viewerMode == Device1AndDevice2 ||
		viewerMode == Device1AndDevice3
		)
	{
		kinect1.camera.begin();
		ofDisableDepthTest();

		glPointSize(2.0);
		vbo1.draw(GL_POINTS, 0, NUM_PARTICLES);

		kinect1.camera.end();
	}

	//KinectB
	if (
		numKinect >= 2 &&
		viewerMode == Device1AndDevice2
		)
	{
		kinect2.camera.begin();
		ofDisableDepthTest();

		glPointSize(2.0);
		vbo2.draw(GL_POINTS, 0, NUM_PARTICLES);

		kinect2.camera.end();
	}

	//KinectC
	if (
		numKinect >= 3 &&
		viewerMode == Device1AndDevice3
		)
	{
		kinect3.camera.begin();
		ofDisableDepthTest();

		glPointSize(2.0);
		vbo3.draw(GL_POINTS, 0, NUM_PARTICLES);

		kinect3.camera.end();
	}
}

//--------------------------------------------------------------
//void ofApp::applyMatrix() {
//	if (viewerMode == Device1AndDevice2) {
//		if (numKinect >= 2) {
//			mat4x4 mat = poseEstimater.estimate2to1();
//			kinect2.setTransformMat(mat);
//
//			//for (int i = 0; i < NUM_PARTICLES; i++) {
//			//	vec3 p = calibPoints2[i];
//			//	calibPoints2[i] = vec3(mat * vec4(p, 1));
//			//}
//			//vbo2.updateVertexData(calibPoints2, NUM_PARTICLES);
//		}
//	}
//	else if (viewerMode == Device1AndDevice3) {
//		if (numKinect >= 3) {
//			mat4x4 mat = poseEstimater.estimate3to1();
//			kinect3.setTransformMat(mat);
//
//			//for (int i = 0; i < NUM_PARTICLES; i++) {
//			//	vec3 p = calibPoints3[i];
//			//	calibPoints3[i] = vec3(mat * vec4(p, 1));
//			//}
//			//vbo3.updateVertexData(calibPoints3, NUM_PARTICLES);
//		}
//	}
//}

//--------------------------------------------------------------
void ofApp::startCalibration() {
	if (isCalibrating) return;

	if (viewerMode == Device1AndDevice2) {
		if (numKinect >= 2) {
			poseEstimater.corners12_1.clear();
			poseEstimater.corners12_2.clear();

			for (int i = 0; i < NUM_PARTICLES; i++) {
				calibPoints1[i] = vec3(0, 0, 0);
				calibPointsColor1[i].a;
			}
			vbo1.updateVertexData(calibPoints1, NUM_PARTICLES);
			vbo1.updateColorData(calibPointsColor1, NUM_PARTICLES);

			for (int i = 0; i < NUM_PARTICLES; i++) {
				calibPoints2[i] = vec3(0, 0, 0);
				calibPointsColor2[i].a;
			}
			vbo2.updateVertexData(calibPoints2, NUM_PARTICLES);
			vbo2.updateColorData(calibPointsColor2, NUM_PARTICLES);

			calibrationMode = Device2ToDevice1;
			isCalibrating = true;
		}
	} else 	if (viewerMode == Device1AndDevice3) {
		if (numKinect >= 3) {
			poseEstimater.corners13_1.clear();
			poseEstimater.corners13_3.clear();

			for (int i = 0; i < NUM_PARTICLES; i++) {
				calibPoints1[i] = vec3(0, 0, 0);
				calibPointsColor1[i].a;
			}
			vbo1.updateVertexData(calibPoints1, NUM_PARTICLES);
			vbo1.updateColorData(calibPointsColor1, NUM_PARTICLES);

			for (int i = 0; i < NUM_PARTICLES; i++) {
				calibPoints3[i] = vec3(0, 0, 0);
				calibPointsColor3[i].a;
			}
			vbo3.updateVertexData(calibPoints3, NUM_PARTICLES);
			vbo3.updateColorData(calibPointsColor3, NUM_PARTICLES);

			calibrationMode = Device3ToDevice1;
			isCalibrating = true;
		}
	}
	else if (viewerMode == All) {
		poseEstimater.corners01_0.clear();
		poseEstimater.corners01_1.clear();

		calibrationMode = Ground;
		isCalibrating = true;
	}
}

//--------------------------------------------------------------
void ofApp::endCalibration() {
	if (!isCalibrating) return;

	if (calibrationMode == Device2ToDevice1) {
		if (numKinect >= 2) {
			mat4x4 mat = poseEstimater.estimate2to1();
			kinect2.setTransformMat(mat);
			poseEstimater.saveMatrix("matrixes/transMat1.txt", mat);

			for (int i = 0; i < NUM_PARTICLES; i++) {
				vec3 p = calibPoints2[i];
				calibPoints2[i] = vec3(mat * vec4(p, 1));
			}
			vbo2.updateVertexData(calibPoints2, NUM_PARTICLES);
		}
	}
	else if (calibrationMode == Device3ToDevice1) {
		if (numKinect >= 3) {
			mat4x4 mat = poseEstimater.estimate3to1();
			kinect3.setTransformMat(mat);
			poseEstimater.saveMatrix("matrixes/transMat3.txt", mat);

			for (int i = 0; i < NUM_PARTICLES; i++) {
				vec3 p = calibPoints3[i];
				calibPoints3[i] = vec3(mat * vec4(p, 1));
			}
			vbo3.updateVertexData(calibPoints3, NUM_PARTICLES);
		}
	}
	else if (calibrationMode == Ground) {
		////if (numKinect >= 3) {
		//mat4x4 mat = poseEstimater.estimate1to0();

		//{
		//	kinect1.setTransformMat(mat);
		//}
		//cout << "Hoge3" << endl;
		//	//{
		//	//	mat4x4 tempMat = kinect2.getTransformMat();
		//	//	tempMat = tempMat * mat;
		//	//	kinect2.setTransformMat(tempMat);
		//	//}
		//	//{
		//	//	mat4x4 tempMat = kinect3.getTransformMat();
		//	//	tempMat = tempMat * mat;
		//	//	kinect3.setTransformMat(tempMat);
		//	//}

		//	poseEstimater.saveMatrix("matrixes/mat1to0.txt", mat);
		//	//}
	}

	calibrationMode = None;
	isCalibrating = false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//if (key == '1') {
	//	kinectA.camera.enableMouseInput();
	//	if (!single)kinectB.camera.disableMouseInput();
	//}
	//if (key == '2') {
	//	kinectA.camera.disableMouseInput();
	//	if (!single)kinectB.camera.enableMouseInput();
	//}

	if (key == 'f') {
		ofToggleFullscreen();
	}

	if (key == '0') {
		viewerMode = All;
	}
	if (key == '1') {
		viewerMode = Device1AndDevice2;
		kinect3.fbo.begin();
		ofClear(0);
		kinect3.fbo.end();

	}
	if (key == '2') {
		viewerMode = Device1AndDevice3;
		kinect2.fbo.begin();
		ofClear(0);
		kinect2.fbo.end();
	}
	if (key == '3') {
		viewerMode = Device2AndDevice3;
		kinect1.fbo.begin();
		ofClear(0);
		kinect1.fbo.end();
	}

	if (key == '4') {
		showKinect1 = !showKinect1;
		if (!showKinect1) {
			kinect1.fbo.begin();
			ofClear(0);
			kinect1.fbo.end();
		}
	}
	if (key == '5') {
		showKinect2 = !showKinect2;
		if (!showKinect2) {
			kinect2.fbo.begin();
			ofClear(0);
			kinect2.fbo.end();
		}
	}
	if (key == '6') {
		showKinect3 = !showKinect3;
		if (!showKinect3) {
			kinect3.fbo.begin();
			ofClear(0);
			kinect3.fbo.end();
		}
	}


	if (key == 'q') {
		if (masterKinect->startCameras(K4A_WIRED_SYNC_MODE_MASTER)) {
			cout << "this kinect(" + masterKinect->device.getSerialNum() + ") is started." << endl;
		}
	}

	if (key == OF_KEY_UP)
	{
		if (numKinect >= 1) kinect1.pointSize += 1;
		if (numKinect >= 2) kinect2.pointSize += 1;
		if (numKinect >= 3) kinect3.pointSize += 1;
	}
	else if (key == OF_KEY_DOWN)
	{
		if (kinect1.pointSize > 1) {
			if (numKinect >= 1) kinect1.pointSize -= 1;
			if (numKinect >= 2) kinect2.pointSize -= 1;
			if (numKinect >= 3) kinect3.pointSize -= 1;
		}
	}
	else if (key == 'z')
	{
		showColorImage = !showColorImage;
	}
	else if (key == 'x')
	{
		showPointCloud = !showPointCloud;
	}
	else if (key == 'c')
	{
		showCalibrationPoints = !showCalibrationPoints;
	}

	if (key == OF_KEY_RETURN)
	{
		if (!isCalibrating) {
			startCalibration();
		}
		else if (isCalibrating) {
			endCalibration();
		}
	}
	if (key == 'l')
	{
		if (numKinect >= 1) {
			mat4x4 mat_1toWorld;
			poseEstimater.loadMatrix("matrixes/transMat1.txt", mat_1toWorld);
			kinect1.setTransformMat(mat_1toWorld);
		}
		if (numKinect >= 2) {
			mat4x4 mat_2toWorld;
			poseEstimater.loadMatrix("matrixes/transMat2.txt", mat_2toWorld);
			kinect2.setTransformMat(mat_2toWorld);
		}
		if (numKinect >= 3) {
			mat4x4 mat_3toWorld;
			poseEstimater.loadMatrix("matrixes/transMat3.txt", mat_3toWorld);
			kinect3.setTransformMat(mat_3toWorld);
		}
	}

	if (key == 'm') {
		//kinect1.clipEnabled = !kinect1.clipEnabled;
		//kinect2.clipEnabled = !kinect2.clipEnabled;
		//kinect3.clipEnabled = !kinect3.clipEnabled;

		if (kinect1.clipEnabled == 1.0) {
			kinect1.clipEnabled = 0.0;
			kinect2.clipEnabled = 0.0;
			kinect3.clipEnabled = 0.0;
		}
		else {
			kinect1.clipEnabled = 1.0;
			kinect2.clipEnabled = 1.0;
			kinect3.clipEnabled = 1.0;

		}
	}

	if (key == 'g') {
		if (detectedMarker1) {
			mat4x4 mat_1toWorld = poseEstimater.estimateTransformMatrix(
				markerCenter, markerAxisX, markerAxisY, markerAxisZ,
				groundCenter, groundAxisX, groundAxisY, groundAxisZ
			);

			kinect1.setTransformMat(mat_1toWorld);
			poseEstimater.saveMatrix("matrixes/transMat1.txt", mat_1toWorld);

			{
				ofMatrix4x4 currentMat = kinect2.getTransformMat();
				currentMat = currentMat * ofMatrix4x4(mat_1toWorld);
				mat4x4 mat_2toWorld = currentMat;
				kinect2.setTransformMat(mat_2toWorld);
				poseEstimater.saveMatrix("matrixes/transMat2.txt", mat_2toWorld);
			}
			{
				ofMatrix4x4 currentMat = kinect3.getTransformMat();
				currentMat = currentMat * ofMatrix4x4(mat_1toWorld);
				mat4x4 mat_3toWorld = currentMat;
				kinect3.setTransformMat(mat_3toWorld);
				poseEstimater.saveMatrix("matrixes/transMat3.txt", mat_3toWorld);
			}

			isCalibrating = false;
			calibrationMode = None;
		}
	}

	//if (key == 'd')
	//{
	//	//移動行列
	//	ofMatrix4x4 translationMat;
	//	translationMat.translate(100, 200, 300);
	//	cout << "\ntranslationMat.translate(100, 200, 300)\n" << translationMat << endl;

	//	//mat4x4 tra2 = glm::translate(glm::mat4(), glm::vec3(100, 200, 0));
	//	//cout << "tra2\n" << tra2 << endl;

	//	//拡大縮小行列
	//	ofMatrix4x4 scalingMat;
	//	scalingMat.scale(2, 3, 4);
	//	cout << "\nscalingMat.scale(2, 3, 4)\n" << scalingMat << endl;

	//	//回転行列
	//	ofMatrix4x4 rotationXMat;
	//	rotationXMat.rotateRad(float(PI) / 4, 1, 0, 0);
	//	cout << "\nrotationXMat.rotateRad(float(PI) / 4, 1, 0, 0)\n" << rotationXMat << endl;

	//	ofMatrix4x4 rotationYMat;
	//	rotationYMat.rotateRad(float(PI) / 4, 0, 1, 0);
	//	cout << "\nrotationYMat.rotateRad(float(PI) / 4, 0, 1, 0)\n" << rotationYMat << endl;

	//	ofMatrix4x4 rotationZMat;
	//	rotationZMat.rotateRad(float(PI) / 4, 0, 0, 1);
	//	cout << "\nrotationZMat.rotateRad(float(PI) / 4, 0, 0, 1)\n" << rotationZMat << endl;

	//	//mat4x4 rot2 = glm::rotate(glm::mat4(), float(PI) / 4, glm::vec3(0, 1, 0));
	//	//cout << "rot2\n" << rot2 << endl;


	//}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	ofVec2f mouse(x, y);
	ofQuaternion yRot((x - _lastMouse.x) * _dampen, vec3(0, 1, 0));
	ofQuaternion xRot((y - _lastMouse.y) * _dampen, vec3(1, 0, 0));
	_globalRotation *= yRot * xRot;
	_lastMouse = mouse;

	//kinect1.globalRotation = _globalRotation;
	//kinect2.globalRotation = _globalRotation;
	//kinect3.globalRotation = _globalRotation;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	_lastMouse = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}


//--------------------------------------------------------------
// EVENT HANDLER
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void ofApp::_eventHandler(flEvent& event) {
	cout << "[ofApp]_eventHandler(" << event.type() << ")" << endl;
	//    cout << "[ofApp]this          = " << this << "," << ((flDisplayObject*) this)->name() << endl;
	cout << "[ofApp]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*)event.currentTarget())->name() << endl;
	cout << "[ofApp]target        = " << event.target() << ", " << ((flDisplayObject*)event.target())->name() << endl;

	if (event.type() == flEvent::ADDED_TO_STAGE) {

	}

	if (event.type() == flFocusEvent::FOCUS_IN) {
		if (event.currentTarget() == ofxSelflash::stage()) {
			if (numKinect >= 1) {
				kinect1.camera.enableMouseInput();
			}
			else if (numKinect >= 2) {
				kinect2.camera.enableMouseInput();
			}
			else if (numKinect >= 3) {
				kinect3.camera.enableMouseInput();
			}
			//_transformableNode1.enabled(true);
			//_transformableNode2.enabled(true);
		}
	}
	else if (event.type() == flFocusEvent::FOCUS_OUT) {
		if (event.currentTarget() == ofxSelflash::stage()) {
			if (numKinect >= 1) {
				kinect1.camera.disableMouseInput();
			}
			else if (numKinect >= 2) {
				kinect2.camera.disableMouseInput();
			}
			else if (numKinect >= 3) {
				kinect3.camera.disableMouseInput();
			}

			//_transformableNode1.enabled(false);
			//_transformableNode2.enabled(false);
		}
	}
}
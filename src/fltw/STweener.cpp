#include "STweener.h"

namespace fltw {

    STweener* STweener::_instance = 0;

    //--------------------------------------------------------------
    //
    STweener* STweener::instance() {
        if (_instance == 0) _instance = new STweener();
        return _instance;
    }

    //--------------------------------------------------------------
    //
    STweener::STweener() {
        _bRender = false;
    };

    //--------------------------------------------------------------
    //
    STweener::~STweener() {

    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    const int STweener::numTweens() {
        if(!_instance) return 0;
        return _instance->_tweens.size();
    }

    //--------------------------------------------------------------
    //
    vector<STweenCore*>& STweener::getAllTweens() {
        vector<STweenCore*> dummy;
        if(!_instance) return dummy;
        return _instance->_tweens;
    }

    //--------------------------------------------------------------
    // TODO overwrite
    // TODO fromTo
    // TODO multi
    STweenCore* STweener::to(
                             float duration,
                             float* targetValue1, float toValue1,
                             string property1, float value1,
                             string property2, float value2,
                             string property3, float value3) {
        
        instance();
        
        //overwrite
        _instance->_overwriteCheck(targetValue1);
        
        STweenCore* tween = new STween(
                                       duration,
                                       targetValue1, toValue1,
                                       property1, value1,
                                       property2, value2,
                                       property3, value3
                                       );
        tween->start();
        _instance->_tweens.push_back(tween);
        _instance->_renderStart();
        
        return tween;
    }
    //--------------------------------------------------------------
    //
    STweenCore* STweener::to(
                             float duration,
                             float* targetValue1, float toValue1,
                             float* targetValue2, float toValue2,
                             string property1, float value1,
                             string property2, float value2,
                             string property3, float value3) {
        
        instance();
        
        //overwrite
        _instance->_overwriteCheck(targetValue1);
        _instance->_overwriteCheck(targetValue2);
        
        STweenCore* tween = new STween(
                                       duration,
                                       targetValue1, toValue1,
                                       targetValue2, toValue2,
                                       property1, value1,
                                       property2, value2,
                                       property3, value3
                                       );
        tween->start();
        _instance->_tweens.push_back(tween);
        _instance->_renderStart();
        
        return tween;
    }
    //--------------------------------------------------------------
    //
    STweenCore* STweener::to(
                             float duration,
                             float* targetValue1, float toValue1,
                             float* targetValue2, float toValue2,
                             float* targetValue3, float toValue3,
                             string property1, float value1,
                             string property2, float value2,
                             string property3, float value3) {
        
        instance();
        
        //overwrite
        _instance->_overwriteCheck(targetValue1);
        _instance->_overwriteCheck(targetValue2);
        _instance->_overwriteCheck(targetValue3);
        
        STweenCore* tween = new STween(
                                       duration,
                                       targetValue1, toValue1,
                                       targetValue2, toValue2,
                                       targetValue3, toValue3,
                                       property1, value1,
                                       property2, value2,
                                       property3, value3
                                       );
        tween->start();
        _instance->_tweens.push_back(tween);
        _instance->_renderStart();
        
        return tween;
    }
    //--------------------------------------------------------------
    //
    STweenCore* STweener::to(
                             float duration,
                             float* targetValue1, float toValue1,
                             float* targetValue2, float toValue2,
                             float* targetValue3, float toValue3,
                             float* targetValue4, float toValue4,
                             string property1, float value1,
                             string property2, float value2,
                             string property3, float value3) {
        
        instance();
        
        //overwrite
        _instance->_overwriteCheck(targetValue1);
        _instance->_overwriteCheck(targetValue2);
        _instance->_overwriteCheck(targetValue3);
        _instance->_overwriteCheck(targetValue4);
        
        STweenCore* tween = new STween(
                                       duration,
                                       targetValue1, toValue1,
                                       targetValue2, toValue2,
                                       targetValue3, toValue3,
                                       targetValue4, toValue4,
                                       property1, value1,
                                       property2, value2,
                                       property3, value3
                                       );
        tween->start();
        _instance->_tweens.push_back(tween);
        _instance->_renderStart();
        
        return tween;
    }
    //--------------------------------------------------------------
    //
    STweenCore* STweener::to(
                             float duration,
                             float* targetValue1, float toValue1,
                             float* targetValue2, float toValue2,
                             float* targetValue3, float toValue3,
                             float* targetValue4, float toValue4,
                             float* targetValue5, float toValue5,
                             string property1, float value1,
                             string property2, float value2,
                             string property3, float value3) {
        
        instance();
        
        //overwrite
        _instance->_overwriteCheck(targetValue1);
        _instance->_overwriteCheck(targetValue2);
        _instance->_overwriteCheck(targetValue3);
        _instance->_overwriteCheck(targetValue4);
        _instance->_overwriteCheck(targetValue5);
        
        STweenCore* tween = new STween(
                                       duration,
                                       targetValue1, toValue1,
                                       targetValue2, toValue2,
                                       targetValue3, toValue3,
                                       targetValue4, toValue4,
                                       targetValue5, toValue5,
                                       property1, value1,
                                       property2, value2,
                                       property3, value3
                                       );
        tween->start();
        _instance->_tweens.push_back(tween);
        _instance->_renderStart();
        
        return tween;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void STweener::_update() {
    //    cout << "[STweener]_update()" << endl;
        
        STweenCore::elapsedTimeMillis = (float)ofGetElapsedTimeMillis();

        int i; int l;
        //_tweens.size()の箇所はリファクタリングとかで外に出したらダメ
        for(i = 0; i < _tweens.size(); i++) {
    //    l = _tweens.size();
    //    for(i = 0; i < l; i++) {
            STweenCore* tween = _tweens[i];
            if(!tween) continue;
            tween->update();
            if(tween->__isCompleted) {
                tween->__onComplete(tween);
                delete tween;
                _tweens.erase(_tweens.begin() + i);
            }
        }
        
    //    cout << "[STweener]_update()" << "tweens.size == " << _tweens.size() << endl;
        if(_tweens.size() == 0) _renderStop();
    }

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void STweener::_renderStart() {
        if(_bRender) return;
        _bRender = true;
        
        ofAddListener(ofEvents().update, this, &STweener::update);
    }

    //--------------------------------------------------------------
    //
    void STweener::_renderStop() {
        if(!_bRender) return;
        _bRender = false;
        
        ofRemoveListener(ofEvents().update, this, &STweener::update);
    }

    //--------------------------------------------------------------
    //
    void STweener::_overwriteCheck(float* targetValue) {
        STween* tween;
        float overwrite;
        //--------------------------------
        //overwrite
        for(int i = 0; i < _instance->_tweens.size(); i++) {
            tween = (STween*)_instance->_tweens[i];
            overwrite = tween->__overwrite;
            
            for(int j = 0; j < tween->__targetValueList.size(); j++) {
                if(tween->__targetValueList[j] == targetValue) {
                    //すべて上書き。
                    //delayが設定してあってもトゥイーンするプロパティが違っていても、記述があった時点で上書きされる。
                    //とにかく書いた順に上書きされる。
                    if(overwrite == TW_ALL_IMMEDIATE) {
                        tween->__toValueList[targetValue] = numeric_limits<float>::quiet_NaN();
                    }
                    
                    //同じプロパティを上書きする。
                    //デフォルトの設定。
                    //[未実装]onCompleteはプロパティごとに実行される。
                    if(overwrite == TW_AUTO) {
                        tween->__toValueList[targetValue] = numeric_limits<float>::quiet_NaN();
                    }
                    
                    //動いていたらトゥイーンを上書き。
                    //delayを見て動いているトゥイーンを上書きする。
                    //プロパティごとの上書きではないので、違うプロパティでも上書きされる。
                    if(overwrite == TW_CONCURRENT) {
                        if(tween->isTweening()) tween->__toValueList[targetValue] = numeric_limits<float>::quiet_NaN();
                    }
                    
                    //優先的にトゥイーン。
                    //[未実装]同時にトゥイーンさせると、delayの値が一番小さく、かつ、その中で最後に記述されたトゥイーンが実行される。
                    //滅多に使わないとのこと。
                    if(overwrite == TW_ALL_ONSTART) {
                        tween->__toValueList[targetValue] = numeric_limits<float>::quiet_NaN();
                    }
                    
                    //[未実装]優先的にトゥイーン。ただし、overwrite=4とは違い、delayも反映される。
                    //overwrite=3との違いがイマイチ不明。
                    if(overwrite == TW_PREEXISTING) {
                        tween->__toValueList[targetValue] = numeric_limits<float>::quiet_NaN();
                    }
                }
            }
        }
        //--------------------------------
    }

}
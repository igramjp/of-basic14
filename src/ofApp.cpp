#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    sampleRate = 48000;
    bufferSize = 512;
    inputs = 1;
    outputs = 1;
    nBuffers = 2;
    
    /*
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numInputChannels = inputs;
    settings.numOutputChannels = outputs;
    settings.bufferSize = bufSize;
    soundStream.setup(settings);
    */
    
    /*
    ofSoundStreamSetup(outputs, inputs, sampleRate, bufferSize, nBuffers);
    */
    
    ofSoundStreamSettings settings;
    settings.setInListener (this);
    settings.setOutListener (this);
    settings.sampleRate        = sampleRate;
    settings.bufferSize        = bufferSize;
    settings.numInputChannels  = inputs;
    settings.numOutputChannels = outputs;
    settings.numBuffers        = nBuffers;
    soundStream.setup(settings);
     
    inputAudio = new float[bufferSize];
    outputAudio = new float[bufferSize];
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float audioHeight = ofGetHeight() / 2.0f;
    float phaseDiff = ofGetWidth() / float(bufferSize);
    
    ofSetColor(255, 0, 127);
    ofNoFill();
    ofSetLineWidth(1);
    
    ofBeginShape();
    for (int i=0; i<bufferSize; i++) {
        ofVertex(i * phaseDiff, audioHeight / 2 + inputAudio[i] * audioHeight);
    }
    ofEndShape();
    
    ofBeginShape();
    for (int i=0; i<bufferSize; i++) {
        ofVertex(i * phaseDiff, audioHeight / 2 * 3 + outputAudio[i] * audioHeight);
    }
    ofEndShape();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &input){
    const int frames = input.getNumFrames();
    const int channels = input.getNumChannels();
    
    for(int f=0; f<frames; f++){
        inputAudio[f * channels] = input[f * channels];
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output){
    const int frames = output.getNumFrames();
    const int channels = output.getNumChannels();
    
    for(int f=0; f<frames; f++){
        output[f * channels] = inputAudio[f * channels];
        outputAudio[f * channels] = inputAudio[f * channels];
    }
}

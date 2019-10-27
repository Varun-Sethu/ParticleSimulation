#include "cinder/app/App.h"
#include "cinder/app/AppBase.h"
#include "cinder/gl/gl.h"
#include "cinder/app/RendererGl.h"
#include "Particles/ParticleController.h"
#include <list>
#include <iostream>

using namespace cinder;


class PlayingApp : public app::App {
    public:
        PlayingApp();

        void setup();
        void update();
        void draw();
        void resize();
    

        void mouseDown(cinder::app::MouseEvent event);
        void mouseDrag(cinder::app::MouseEvent event);
        void mouseUp(cinder::app::MouseEvent event);
    private:
        ParticleController particleController;
};
void prepareSettings(PlayingApp::Settings *settings) {
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.0f);
}

PlayingApp::PlayingApp() {
    this->particleController = ParticleController();
}



// Core functions
void PlayingApp::setup() {
    this->particleController.addParticle(2);
}
void PlayingApp::update() {
    this->particleController.update();
}
void PlayingApp::draw() {
    cinder::gl::clear(Color(0, 0, 0), true);
    this->particleController.draw();
}
void PlayingApp::resize() {
    this->particleController.updateWindowDimensions(cinder::app::getWindowWidth(), cinder::app::getWindowHeight());
}








// Functions to deal with left and right clicks
// A left click results in the creation of 10 more particles    
void PlayingApp::mouseDown(cinder::app::MouseEvent event) {
    if (event.isLeft()) {
        // Get the current mouse position and move all particles towards that position
        cinder::vec2 pos = event.getPos();
        this->particleController.flockTowards(pos);
    } else if (event.isRightDown()) {
        this->particleController.addParticle(event.getPos(), 5);
    }
}

// Mouse drag is to create the "artificial" gravity
void PlayingApp::mouseDrag(cinder::app::MouseEvent event) {
    if (event.isLeftDown()) {
        // Get the current mouse position and move all particles towards that position
        cinder::vec2 pos = event.getPos();
        this->particleController.flockTowards(pos);
    }
}


// Mouse up just clears the acceleration of all the particles in the particle controller
void PlayingApp::mouseUp(cinder::app::MouseEvent event) {
    if (event.isLeft()) {
        this->particleController.clearAccelerations();
    }
}


CINDER_APP(PlayingApp, cinder::app::RendererGl, prepareSettings);
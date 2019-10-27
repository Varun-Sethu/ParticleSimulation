#include "Particles/ParticleController.h"
#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "Util/Util.h"





ParticleController::ParticleController() {
    this->windowHeight = cinder::app::getWindowHeight();
    this->windowWidth = cinder::app::getWindowWidth();
}







void ParticleController::update() {
    for (auto p = this->particles.begin(); p != this->particles.end(); p++) {
        p->update();
    }
}
void ParticleController::draw() {
    for (auto p = this->particles.begin(); p != this->particles.end(); p++) {
        p->draw();
    }
}






// Core functions
void ParticleController::addParticle(int amt) {
    for (int i = 0; i < amt; i++) {
        float x = cinder::randFloat(0.0f, cinder::app::getWindowWidth());
        float y = cinder::randFloat(0.0f, cinder::app::getWindowHeight());

        this->particles.push_back(Particle(cinder::vec2(x, y)));
    }
}

// Add particle method with an initializing point
void ParticleController::addParticle(cinder::vec2 init, int amt) {
    for (int i = 0; i < amt; i++) {
        cinder::vec2 unitvec = cinder::randVec2();
        cinder::vec2 newPosition = init + unitvec;

        while(nearBehindEdge(this->windowHeight, this->windowWidth, newPosition) != ScreenEdge::NONE) {
            unitvec = cinder::randVec2();
            newPosition = init + unitvec;
        }

        this->particles.push_back(Particle(newPosition));
    }
}







void ParticleController::removeParticles(int amt) {
    for (int i = 0; i < amt; i++) {
        this->particles.pop_back();
    }
}
void ParticleController::updateWindowDimensions(int x, int y) {
    for (auto p = this->particles.begin(); p != this->particles.end(); p++) {
        p->updateScreenDimensions(x, y);
    }
    this->windowHeight = y;
    this->windowWidth = x;
}
void ParticleController::clearAccelerations() {
    for (auto p = this->particles.begin(); p != this->particles.end(); p++) {
        p->acceleration = cinder::vec2(0, 0);
    }
}



// Flock towards moves all particles in the screen towards a specific position
void ParticleController::flockTowards(cinder::vec2 position) {
    for (auto p = this->particles.begin(); p != this->particles.end(); p++) {
        p->moveTowards(position);
    }
}
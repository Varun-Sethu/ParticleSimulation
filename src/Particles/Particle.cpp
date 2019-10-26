#include "Particles/Particle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "Util/Util.h"
#include "cinder/Rand.h"

Particle::Particle() {

}


Particle::Particle(cinder::vec2 position) {
    this->position = position;
    this->velocity = cinder::randVec2();
    this->velocity *= cinder::randFloat(4.0f, 6.0f);

    this->radius = cinder::randFloat(1.0f, 3.0f);
    // window stuff
    this->windowHeight = cinder::app::getWindowHeight();
    this->windowWidth = cinder::app::getWindowWidth();
}




// Time increment movement
void Particle::update() {
    ScreenEdge edge = nearBehindEdge(this->windowHeight, this->windowWidth, this->position);
    
    if (edge != ScreenEdge::NONE) {
        this->velocity *= -1;
    }

    this->position += this->velocity;
}
void Particle::draw() {
    cinder::gl::drawSolidCircle(this->position, this->radius);
}



void Particle::updateScreenDimensions(int x, int y) {
    this->windowHeight = y;
    this->windowWidth = x;
}
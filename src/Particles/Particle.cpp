#include "Particles/Particle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "Util/Util.h"
#include "cinder/Rand.h"
#include <cmath>

Particle::Particle() {

}


Particle::Particle(cinder::vec2 position) {
    this->position = position;
    this->velocity = cinder::randVec2();
    this->velocity *= cinder::randFloat(1.0f, 2.0f);

    this->radius = cinder::randFloat(3.0f, 4.5f);
    // window stuff
    #ifndef DEBUG
        this->windowHeight = cinder::app::getWindowHeight();
        this->windowWidth = cinder::app::getWindowWidth();
    #endif
}




// Time increment movement
void Particle::update() {
    bool collided = false;
    
    // Acceleration method for accelerating particles towards a source
    if (this->acceleration != cinder::vec2(0, 0)) {
        this->velocity += this->acceleration;
    }

    // Screen edge detection method
    ScreenEdge edge = nearBehindEdge(this->windowHeight, this->windowWidth, this->position, this->radius);
    if (edge != ScreenEdge::NONE) {
        collided = true;
        // Flip the velocity
        switch (edge) {
            case ScreenEdge::TOP:
            case ScreenEdge::BOTTOM:
                this->velocity.y *= -1;
                break;
            case ScreenEdge::LEFT:
            case ScreenEdge::RIGHT:
                this->velocity.x *= -1;
                break;
        }
    }

    this->position += this->velocity;
    // If the position is outside of the window for some reason then just reset the position
    if (this->position.x < 0.0f) this->position.x = 0.0f;
    if (this->position.x > windowWidth) this->position.x = windowWidth;
    if (this->position.y < 0.0f) this->position.y = 0.0f;
    if (this->position.y > windowHeight) this->position.y = windowHeight;

    if (collided) {
        // Redeuce the total energy of the particle by 10%
        cinder::vec2 newEnergy = this->getEnergy();
        newEnergy *= 0.9;
        this->setEnergy(newEnergy);
    }


}
void Particle::draw() {
    cinder::gl::drawSolidCircle(this->position, this->radius);
}
bool Particle::intersects(Particle* p) {
    return cinder::length(this->position - p->position) <= this->radius + p->radius;
} 








// Get energy returns the total energy of a specififc particle
cinder::vec2 Particle::getEnergy() {
    // x and y energies
    return cinder::vec2(0.5 * pow(this->velocity.x, 2), 0.5 * pow(this->velocity.y, 2));
}
// Set energy sets the kinetic energy of a specific particle
void Particle::setEnergy(cinder::vec2 energy) {
    cinder::vec2 velocityDirection = cinder::normalize(this->velocity);
    this->velocity = cinder::vec2(
        velocityDirection.x * (sqrt(2*energy.x)),
        velocityDirection.y * (sqrt(2*energy.y))
    );
}







void Particle::updateScreenDimensions(int x, int y) {
    this->windowHeight = y;
    this->windowWidth = x;
}

// Movetowards just moves the particle towards a specific locaiton with an arbitary acceleration
void Particle::moveTowards(cinder::vec2 position) {
    cinder::vec2 generalDir = position - this->position;
    float acclMag = 500.0f/pow(cinder::length(generalDir), 2);
    this->acceleration = cinder::normalize(generalDir) * acclMag;
}
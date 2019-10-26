#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cinder/Vector.h"

class Particle {
    public:
        Particle();
        Particle(cinder::vec2 position);

        // Core drawing methods
        void update();
        void draw();

        // Miscelenious methods
        void updateScreenDimensions(int x, int y);

    private:
        cinder::vec2 position;
        cinder::vec2 velocity; 

        // Determines if the particle has hit the edge of the screen
        float radius;

        // Screen dimensions
        float windowHeight;
        float windowWidth;


};

#endif
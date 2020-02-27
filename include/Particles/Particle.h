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
        void moveTowards(cinder::vec2 position);
        bool intersects(Particle* p);

        cinder::vec2 getEnergy();
        void setEnergy(cinder::vec2 energy);




        cinder::vec2 position;
        cinder::vec2 velocity;
        cinder::vec2 acceleration; 

    private:
        // Determines if the particle has hit the edge of the screen
        float radius;

        // Screen dimensions
        float windowHeight;
        float windowWidth;


};

#endif
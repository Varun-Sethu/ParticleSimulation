#ifndef __PARTICLE_CONTROLLER_H__
#define __PARTICLE_CONTROLLER_H__

#include "Particle.h"
#include "cinder/Vector.h"
#include <list>


class ParticleController {
    public:
        ParticleController();

        // Main drawing methods
        void update();
        void draw();

        // Utility methods
        void addParticle(int amt);
        void addParticle(cinder::vec2 init, int amt);

        void removeParticles(int amt);
        void updateWindowDimensions(int x, int y);

        // Misc methods
        void flockTowards(cinder::vec2 position);
        void clearAccelerations();

    private:
        std::list<Particle> particles;

        int windowHeight;
        int windowWidth;
};

#endif
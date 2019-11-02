#ifndef __COLLISION_ENGINE_H__
#define __COLLISION_ENGINE_H__

#include "cinder/Vector.h"
#include <vector>
#include "Particles/Particle.h"
#include "Particles/ParticleController.h"


class CollisionDetector {
    public:
        CollisionDetector(ParticleController& tracking);

        // Utility methods
        std::vector<Particle&> detectCollision();
        void resolveCollision(std::vector<Particle&> particles);

    private:
        ParticleController& tracking;
        
};

#endif
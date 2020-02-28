#ifndef __COLLISION_ENGINE_H__
#define __COLLISION_ENGINE_H__

#include "cinder/Vector.h"
#include <vector>
#include "Particles/Particle.h"
#include "Particles/ParticleController.h"
#include "QuadTree.h"
#include <exception>
#include <iostream>


class CollisionDetector {
public:
    CollisionDetector(ParticleController* tracking, float screenHeight, float screenWidth): __tracking(tracking), 
                                                                                            __screenHeight(screenHeight), __screenWidth(screenWidth) {}
    
    void detect() {
        // Build a quadtree and begin inserting the partciles into that quadtree
        QuadTree screenOrganiser(BoundingBox(
            cinder::vec2(0, 0), 
            __screenHeight, __screenWidth
        ));
        for (auto it = __tracking->particles.begin(); it != __tracking->particles.end(); it++) {
            screenOrganiser.insert(&(*it));
        }

        // Now for each particle that exists within the particle controller detect for any collisions wihthin its region
        for (auto it = __tracking->particles.begin(); it != __tracking->particles.end(); it++) {
            Particle* particle = &(*it);

            // Find the quadtree the particle belongs to, if for some reason it doesn't exist then just skip this
            QuadTree* screenPortion = screenOrganiser.search(particle);
            if (!screenPortion) continue;

            Particle** data = screenPortion->getData();

            // Iterate over every single particle within this screen porition
            for (int i = 0; i < 4; i++) {
                if (!data[i]) continue;
                if (data[i] == particle) continue;
                // Detect the actual collision
                if (data[i]->intersects(particle)) __tracking->handleCollision(data[i], particle);
            }
        }
    }



    void updateScreenDimensions(float screenWidth, float screenHeight) {
        this->__screenHeight = screenHeight;
        this->__screenWidth = screenWidth;
    }
    
private:
    ParticleController* __tracking;       
    float __screenHeight;
    float __screenWidth;
};

#endif
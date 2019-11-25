#include "Util/QuadTree.h"
#include "Particles/Particle.h"
#include <cstdlib>
#include "cinder/Rand.h"
#include "Config.h"
#include <vector>
#include <iostream>


// Screen dimensions
float x = 1920;
float y = 1080;


std::vector<Particle> generateParticles() {
    return {
        Particle(cinder::vec2(1000, 1000)),
        Particle(cinder::vec2(800, 1000)),
        Particle(cinder::vec2(900, 1000)),
        Particle(cinder::vec2(700, 1000)),
        Particle(cinder::vec2(600, 1000)),
        Particle(cinder::vec2(500, 1000)),
        Particle(cinder::vec2(400, 1000)),
        Particle(cinder::vec2(300, 1000)),
        Particle(cinder::vec2(200, 1000)),
        Particle(cinder::vec2(100, 1000)),
        Particle(cinder::vec2(1200, 1000)),
        Particle(cinder::vec2(1300, 1000)),
        Particle(cinder::vec2(1400, 1000)),
        Particle(cinder::vec2(1500, 1000)),
        Particle(cinder::vec2(1600, 1000)),
        Particle(cinder::vec2(1700, 1000)),
    };
}











int main(void) {
    // Guard
    #ifndef DEBUG
        return EXIT_FAILURE;
    #endif
    

    std::vector<Particle> particles = generateParticles();
    
    // Create a tree object to test
    Box region(cinder::vec2(0.0, 0.0), cinder::vec2(x, y));
    QuadTree quadtree(region);
    for (auto particle: particles) {
        quadtree.insert(&particle);
    }

    std::cout << quadtree.countElements() << "\n";

    




    return EXIT_SUCCESS;
}
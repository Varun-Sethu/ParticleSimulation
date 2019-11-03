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

int main(void) {
    // Guard
    #ifdef DEBUG
        std::cout << "Application must be in debug mode to execute testing files...";
        return EXIT_FAILURE;
    #endif
    

    std::vector<Particle> particles;
    // Generate a list of random particles
    for(int i = 0; i < 50; i++) {
        // Randomised position
        float xPos = cinder::randFloat(x);
        float yPos = cinder::randFloat(y);
        cinder::vec2 randPos = cinder::vec2(xPos, yPos);

        particles.push_back(Particle(randPos));
    }

    QuadTree gameBoard(Box(cinder::vec2(0, 0), cinder::vec2(x, y)), nullptr);
    for(Particle& p: particles) {
        Node data;
        data.particle = p;
        gameBoard.insert(data);
    }


    std::cout << gameBoard.printTree();



    return EXIT_SUCCESS;
}
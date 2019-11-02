#ifndef __QUAD_TREE_H__
#define __QUAD_TREE_H__

#include "cinder/Vector.h"
#include "Particles/Particle.h"
#include <vector>
#include <string>
#include <memory>
#include "Config.h"



class Box {
    public:
        Box(cinder::vec2 tr, cinder::vec2 bl):topRight(tr), bottomLeft(bl){}

        bool contains(cinder::vec2 point);

        cinder::vec2 topRight;
        cinder::vec2 bottomLeft;
};

union Node {
    Box region;
    Particle& particle;
};



class QuadTree {
    public:
        QuadTree(Box box, QuadTree* parent);
        QuadTree(Particle& particle, QuadTree* parent);

        // util methods
        void subdivide();
        bool insert(const Node& data);

        // Search function does what it says
        std::shared_ptr<QuadTree> region_search(Particle& particle);

        // more util
        bool isRegion() { return this->isRegion; }
        // Function to determine if the current node is a entirely a parent of leaf nodes
        bool parentingLeaves();
        bool isFull();



        // Debug functions
        #ifdef DEBUG
            // Prints the entire tree
            std::string printTree();
        #endif


        Node data;
        QuadTree* parent = nullptr;


    private:
        std::vector<std::shared_ptr<QuadTree>> children{nullptr, nullptr, nullptr, nullptr};
        bool full = false;
};


#endif 
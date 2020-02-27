#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include "Particles/Particle.h"
#include "cinder/Vector.h"


// BB is defined by these values because it might make subdivision easier?
struct BoundingBox {
    // Boxes are defined by their top right corner, their height and width
    BoundingBox(cinder::vec2 topRight, float height, float width): topRight(topRight), height(height), width(width) {}

    bool within(cinder::vec2 positionVector) {
        cinder::vec2 relativePosition = positionVector - topRight;

        return between(relativePosition.x, 0, width) &&
               between(relativePosition.y, 0, height);
    }

    bool between(float n, float a, float b) {
        return n >= a && n <= b;
    }


    cinder::vec2 topRight;
    float height;
    float width;
    
};


// Simple quadtree implementation
class QuadTree {
public:
    QuadTree(BoundingBox bb): __bb(bb) {
        __capacity = 4;
    }
    ~QuadTree() {
        if (!__ne) delete __ne;
        if (!__nw) delete __nw;
        if (!__se) delete __se;
        if (!__sw) delete __sw;
    }


    // Insertion function inserts a particle into the quadtree
    bool insert(Particle* p) {
        if (__capacity > 0) {
            if (!__bb.within(p->position)) return false;

            data[4 - __capacity] = p;
            this->__capacity -= 1;
            return true;
        }
        // Not a leaf node so pass onto children
        if (!__isLeaf) {
            if (__ne->__bb.within(p->position)) return __ne->insert(p);
            if (__nw->__bb.within(p->position)) return __nw->insert(p);
            if (__se->__bb.within(p->position)) return __se->insert(p);
            if (__sw->__bb.within(p->position)) return __sw->insert(p);
        }

        // If this area is reached then the tree must be subdivided
        subdivide();
        return insert(p);
    }


    // HMM yes, subdivides the qquadtree into a tree with 4 leaf nodes
    bool subdivide() {
        __isLeaf = false;
        
        // Define the new regions
        // TODO: make it cleaner :(
        float newHeight = __bb.height / 2.0f;
        float newWidth  = __bb.width / 2.0f;
        __nw = new QuadTree(BoundingBox(__bb.topRight, newHeight, newWidth));
        __ne = new QuadTree(BoundingBox(__bb.topRight + cinder::vec2(newWidth, 0), newHeight, newWidth));
        __sw = new QuadTree(BoundingBox(__bb.topRight + cinder::vec2(0, newHeight), newHeight, newWidth));
        __se = new QuadTree(BoundingBox(__bb.topRight + cinder::vec2(newWidth, newHeight), newHeight, newWidth));

        // Very ugly :(
        bool couldInsert  = true;
        for (int i = 0; i < 4; i++) {
            couldInsert &= (
                __ne->insert(data[i]) || __nw->insert(data[i]) || __se->insert(data[i]) || __sw->insert(data[i])
            );
        }

        return couldInsert;
    }

    // This has to be the weirdest thing ive written lmao
    QuadTree* search(Particle* p) const {
        if (!__isLeaf) {
            if (QuadTree* value = __ne->search(p)) return value;
            if (QuadTree* value = __nw->search(p)) return value;
            if (QuadTree* value = __se->search(p)) return value;
            if (QuadTree* value = __sw->search(p)) return value;
        }
        // This appears to be a leaf node so if this node contains p then return the address of this node
        for (int i = 0; i < 4; i++) {
            if (data[i] == p) return const_cast<QuadTree*>(this);
        }
        return nullptr;
    }



    // Getters
    Particle** getData() {
        return data;
    }

private:
    BoundingBox __bb;
    QuadTree* __ne;
    QuadTree* __nw;
    QuadTree* __se;
    QuadTree* __sw;

    int __capacity = 4;
    bool __isLeaf = true; // Every quadtree is a leaf of the tress to begin with

    Particle* data[4] = {};
};


#endif
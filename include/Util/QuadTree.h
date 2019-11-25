#ifndef __QUAD_TREE_H__
#define __QUAD_TREE_H__

#include <vector>
#include <type_traits>
#include <algorithm>
#include <memory>
#include <variant>
#include <iostream>

#include "Config.h"
#include "Particles/Particle.h"
#include "Util/Box.h"





class Node {
    public:
        Node(Box region) {
            __data = std::variant<Box, Particle*>{region};
        }
        Node(Particle* particle) {
            __data = std::variant<Box, Particle*>{particle};
        }


        // General utility functions
        bool isRegion() {
            return std::get_if<Box>(&__data);
        }
        // Does this specific node have this value
        bool hasValue(Particle* val) {
            if(isRegion()) return false;

            return std::get<Particle*>(__data) == val;
        }
        // Getter methods converts and attains the data
        const Particle* getParticleData() {
            return std::get<Particle*>(__data);
        }
        Box getContainer() {
            return std::get<Box>(__data);
        }

    private:
        std::variant<Box, Particle*> __data{nullptr};
};









// Quadtree class for spatial division
class QuadTree {
    public:
        QuadTree(Particle* data, QuadTree* parent = nullptr) : __data(data), __parent(parent){}
        QuadTree(Box region, QuadTree* parent = nullptr): __data(region), __parent(parent) {}
        ~QuadTree() {
            for(QuadTree* child: __children) {
                if (child) delete child;
            }
        }






        bool insert(Particle* data) {
            if (__mustBeSubdivided()) subdivide();

            // object is full so get the child nodes to handle insertion
            if (__capacity == 0) {
                for (QuadTree* child: __children) {
                    if (child->insert(data)) return true;
                }
                return false;
            }
            
            // The tree's children are not filled and therefore new children nodes may be inserted
            // Construct a new tree obj on the heap
            if (__data.getContainer().contains(data->position)) {
                QuadTree* newChild = new QuadTree(data);
                __children[4 - __capacity] = newChild;
                __capacity -= 1;
                return true;
            }

            return false;
        }








        // The subdivide splits a tree into four new region nodes all based off the construction of the intial node
        void subdivide() {
            if (!__mustBeSubdivided()) return;

            std::vector<Box> subBoxes = __data.getContainer().divide();
            std::vector<QuadTree*> childCopy(__children.begin(), __children.end());

            // For every single sub box allocate a new quadtree on the heap and insert the data
            for (int i = 0; i < 4; i++) {
                Box* box = &subBoxes[i];
                QuadTree* newChild = new QuadTree(*box, this);

                // Iterate over child in the child copy vector, reassigning any data points that belong to the new child
                for (auto child = childCopy.begin(); child != childCopy.end(); child++) {
                    QuadTree* childMember = *child;
                    // If current node is a nullptr then just skip this iteration
                    if (!childMember) continue;

                    if (box->contains(childMember->__data.getParticleData()->position)) {
                        newChild->__children[4 - newChild->__capacity] = childMember;
                        newChild->__capacity -= 1;
                        childCopy.erase(child);
                    }
                }

                // Add this newly generated child to the updated children set
                __children[i] = newChild;
            }

            return;
        }



        // This function generate a string representation of this current tree
        std::string printTree() {
            if (!__data.isRegion()) return "n";


            std::string activeCopy = "{";
            for(QuadTree* child: __children) {
                if (child) activeCopy.append(child->printTree() + ",");
            }
            return activeCopy + "}";
        }


        int countElements() {
            if (!__data.isRegion()) return 1;

            int count = 0;
            for(auto* node: __children) {
                if (node) count += node->countElements();
            }

            return count;
        }




    private:
        Node __data;
        unsigned int __capacity = 4;
        QuadTree* __parent = nullptr;

        // Children nodes
        std::vector<QuadTree*> __children{nullptr, nullptr, nullptr, nullptr};


        // Must be subdivided alterts us to whether the current tree has to be subdivided
        bool __mustBeSubdivided() {
            return __capacity == 0 && !(__children[0]->__data.isRegion());
        }


};














#endif 
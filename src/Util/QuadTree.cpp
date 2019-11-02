#include "Util/QuadTree.h"
#include "cinder/Vector.h"
#include <algorithm>


// Box methods
// This is a mess :)
bool Box::contains(cinder::vec2 point) {
    bool withinY = point.y <= this->topRight.y && point.y >= this->bottomLeft.y;
    bool withinX = point.x >= this->topRight.x && point.x <= this->bottomLeft.x;

    return withinX && withinY;
}





// Quadtree methods
QuadTree::QuadTree(Box box, QuadTree* parent) {
    this->data.region = box;
    this->isRegion = true;
}
QuadTree::QuadTree(Particle& particle, QuadTree* parent) {
    this->data.particle = particle;
}






// Utility methods
bool QuadTree::parentingLeaves() {
    return !(std::count_if(this->children.begin(), this->children.end(), [](QuadTree* tree){
        return tree->isRegion();
    }) == 4);
}
// Determine if a tree node is full
bool QuadTree::isFull() {
    return !(std::count(this->children.begin(), this->children.end(), nullptr)) == 4;
}





// Debug utility functions
#ifdef DEBUG
    // Function to print the entire tree
    std::string QuadTree::printTree() {
        if (!(this->isRegion())) {
            return std::string(this->children.size(), '#');
        }

        
        // Attain all the strings for this dude's children
        std::string childString = "";
        for(auto child: this->children) {
            childString += " " + child->printTree();
        }

        return "o\n" + childString;
    }
#endif






// The subidivde takes a full tree and splits it up and inserts its children into the rest of the tree
void QuadTree::subdivide() {
    if (!this->isRegion) {
        return;
    }

    // General stuff
    Box regionBounds = this->data.region;
    auto tr = regionBounds.topRight;
    auto br = regionBounds.bottomLeft;
    
    // Generate a new region subdivisions given the current region
    std::vector<std::shared_ptr<QuadTree>> newRegions{
        std::make_shared<QuadTree>(tr, cinder::vec2(br.x / 2, br.y / 2), this),
        std::make_shared<QuadTree>(cinder::vec2(br.x / 2, tr.y), cinder::vec2(br.x, br.y / 2), this),
        std::make_shared<QuadTree>(cinder::vec2(tr.x, br.y /2), cinder::vec2(tr.x / 2, br.y), this),
        std::make_shared<QuadTree>(cinder::vec2(br.x / 2, br.y /2), br, this)
    };


    auto childrenCopy = this->children;
    std::copy(newRegions.begin(), newRegions.end(), this->children.begin());
    for (auto entry: childrenCopy) {
        this->insert((*entry).data);
        // Let go of region in memory being held up 
        entry.reset();
    }

    return;
}










// Insert method 
bool QuadTree::insert(const Node& data) {
    
    // If this node is full then subdivide the current node and proceeed with the rest of the insert method
    if (this->isFull()) {
        this->subdivide();
    }


    // Determine if the tree is full or not and if it is full then get the trees children to handle if
    if (this->parentingLeaves()) {
        for(auto tree: this->children) {
            if(tree->insert(data)) {
                return true;
            }
        }
    // As long as this node is not full insert an extra peice of data
    } else {
        // Enter it into the first empty value we find :)
        auto tree = std::find(this->children.begin(), this->children.end(), nullptr);
        (*tree) = std::make_shared<QuadTree>(data, this);  
        return true;
    }

    return false;
}







// The search method iterates through a quadtree to find the 
std::shared_ptr<QuadTree> QuadTree::region_search(Particle& particle) {
    if (this->isFull()) {
        for(auto node: this->children) {
            if (&(node->data.particle) == &particle) {
                return node;
            }
        }
    } else {
        // Search all of this dudes children
        for(auto node: this->children) {
            std::shared_ptr<QuadTree> childOccurance = node->region_search(particle);
            if (childOccurance != nullptr) {
                return childOccurance;
            }
        }
    }
    
    return nullptr;
}
#include "Util/Util.h"
#include "cinder/Vector.h"


ScreenEdge nearBehindEdge(int height, int width, cinder::vec2 position, float buffer){
    // determine if they are left or right
    if(position.x - buffer < 0) {
        return ScreenEdge::LEFT;
    } else if (position.x + buffer > width) {
        return ScreenEdge::RIGHT;
    }

    // determine if they are left or right
    if(position.y - buffer < 0) {
        return ScreenEdge::TOP;
    } else if (position.y + buffer > height) {
        return ScreenEdge::BOTTOM;
    }

    return ScreenEdge::NONE;
}
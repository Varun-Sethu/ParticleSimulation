#include "Util/Util.h"
#include "cinder/Vector.h"


ScreenEdge nearBehindEdge(int height, int width, cinder::vec2 position){
    // determine if they are left or right
    if(position.x < 0) {
        return ScreenEdge::LEFT;
    } else if (position.x > width) {
        return ScreenEdge::RIGHT;
    }

    // determine if they are left or right
    if(position.y < 0) {
        return ScreenEdge::TOP;
    } else if (position.y > height) {
        return ScreenEdge::BOTTOM;
    }

    return ScreenEdge::NONE;
}
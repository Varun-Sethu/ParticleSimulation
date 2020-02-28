#ifndef __UTIL_H__
#define __UTIL_H__

#include "cinder/Vector.h"

enum class ScreenEdge {
    RIGHT, LEFT, TOP, BOTTOM, NONE
};


ScreenEdge nearBehindEdge(int height, int width, cinder::vec2 position, float buffer);

#endif
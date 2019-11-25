#ifndef __BOX_H__
#define __BOX_H__

#include "cinder/Vector.h"



class Box {
    public:
        Box(cinder::vec2 tl, cinder::vec2 br): __topLeft(tl), __bottomRight(br){}

        // Determines if a point falls within a box
        bool contains(cinder::vec2 p) {
            bool withinY = (p.y >= __topLeft.y && p.y <= __bottomRight.y);
            bool withinX = (p.x >= __topLeft.x && p.x <= __bottomRight.x);

            return withinX && withinY;
        }


        

        // Splits a box into four
        std::vector<Box> divide() {
            // These vectors just simplify and clean up calculations
            auto xIncrement = cinder::vec2(__bottomRight.x / 2, 0);
            auto yIncrement = cinder::vec2(0, __bottomRight.y / 2);
    
            return {
                Box(__topLeft, __topLeft + xIncrement + yIncrement),
                Box(__topLeft + xIncrement, __bottomRight - yIncrement),
                Box(__topLeft + yIncrement, __bottomRight - xIncrement),
                Box(__topLeft + yIncrement + xIncrement, __bottomRight)
            };
        }

        cinder::vec2 __topLeft;
        cinder::vec2 __bottomRight;
};
    

#endif